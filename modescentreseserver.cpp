#include "modescentreseserver.h"
#include <QJsonArray>
ModesCentreSEServer::ModesCentreSEServer(QObject* parent) :
    QTcpServer(parent)
{
    m_model = std::make_unique<ModesCentreModel>();
    listen(QHostAddress::Any, 8080);
}

QJsonArray ModesCentreSEServer::getValues(const QString& code, int type, QDateTime& date)
{
    QJsonArray responseArray;

    const QDate today = QDate::currentDate();
    const QVector<double>& values = (date.date() == today) ? m_model->todayValuesRef() : m_model->tomorrowValuesRef();

    for (int i = 0; i < 24; ++i)
    {
        date.setTime(QTime(i, 0));

        QJsonObject item;
        item["objCode"] = code;
        item["objType"] = type;
        item["paramName"] = "p";
        item["dt"] = date.toString(Qt::ISODateWithMs);
        item["value"] = values.at(i);
        responseArray.append(item);
    }
    return responseArray;
}

void ModesCentreSEServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, [socket, this]() {
        m_requestData.append(socket->readAll());
        int headerEndIndex = m_requestData.indexOf("\r\n\r\n");
        if (headerEndIndex == -1)
        {
            // Неверный запрос
            QByteArray response = "HTTP/1.1 400 Bad Request\r\n";
            socket->write(response);
            socket->flush();
            m_requestData.clear();
            return;
        }

        QByteArray body = m_requestData.mid(headerEndIndex + 4);
        QJsonParseError parseError;
        QJsonDocument incomingDoc = QJsonDocument::fromJson(body, &parseError);

        if (parseError.error != QJsonParseError::NoError)
            return;

        QJsonObject jsonObj = incomingDoc.object();

        const auto day = jsonObj.find("day")->toString();
        const auto objInfo = jsonObj.find("objInfos")->toArray().first().toObject();
        const auto objCode = objInfo.find("objCode")->toString();
        const auto objType = objInfo.find("objType")->toInt();

        qInfo() << QString("Получен запрос:  day(%1) objCode %2 objType %3")
                   .arg(day)
                   .arg(objCode)
                   .arg(objType);

        QDateTime date = QDateTime::fromString(day, Qt::ISODateWithMs);
        QJsonArray responseArray(getValues(objCode, objType, date));
        QJsonDocument doc(responseArray);
        QByteArray responseBody = doc.toJson();

        QByteArray response = "HTTP/1.1 200 OK\r\n"
                              "Content-Type: application/json\r\n"
                              "Content-Length: "
        + QByteArray::number(responseBody.size()) + "\r\n"
                                                    "\r\n"
        + responseBody;

        socket->write(response);
        socket->flush();
        m_requestData.clear();
    });
    socket->setSocketDescriptor(socketDescriptor);
}
