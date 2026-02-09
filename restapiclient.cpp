#include "restapiclient.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QUrlQuery>
#include <stdexcept>

const QString OBJ_ID(QStringLiteral("objId"));
const QString POINTS(QStringLiteral("points"));
const QString TIME(QStringLiteral("time"));
const QString POWER(QStringLiteral("p"));

RestApiClient::RestApiClient(QObject* parent) :
    QObject(parent)
{
    updateURL();
    m_manager = std::make_unique<QNetworkAccessManager>();
}

void RestApiClient::setModel(ModesCentreModel* model)
{
    if (m_model == model)
        return;
    m_model = model;
    emit modelChanged();
    if (m_model)
        connect(m_manager.get(), &QNetworkAccessManager::finished, this, &RestApiClient::onFinished);
}

void RestApiClient::setIpaddr(const QString& val)
{
    if (m_ipaddr == val)
        return;
    m_ipaddr = val;
    emit ipaddrChanged();
    updateURL();
}

void RestApiClient::setPort(int val)
{
    if (m_port == val)
        return;
    m_port = val;
    emit portChanged();
    updateURL();
}

void RestApiClient::updateURL()
{
    m_url = QUrl(QString("%1%2:%3/update_pbr").arg(httpPrefix, m_ipaddr).arg(m_port));
}

void RestApiClient::sendValues()
{
    QDateTime yesterday = QDateTime::currentDateTime().addDays(-1);
    yesterday.setTime(QTime(0, 0));

    // QJsonObject result;
    // QJsonArray array;

    const auto fillDay = [this](const QVector<double>& values, const QDateTime& date) {
        QJsonObject result;
        QJsonArray array;
        for (int hour = 0; hour < 24; hour++)
        {
            QJsonObject item;
            const auto time = date.addSecs(3600 * hour);
            item[TIME] = QString("%1Z").arg(time.toString(Qt::ISODateWithMs));
            item[POWER] = values.at(hour);
            array.append(item);
        }
        result[OBJ_ID] = 777;
        result[POINTS] = array;

        QNetworkRequest request(m_url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        const QByteArray jsonData = QJsonDocument(result).toJson();
        m_manager->post(request, jsonData);
    };

    fillDay(m_model->yesterdayValuesRef(), yesterday);
    fillDay(m_model->todayValuesRef(), yesterday.addDays(1));
    fillDay(m_model->tomorrowValuesRef(), yesterday.addDays(2));
}

void RestApiClient::onFinished(QNetworkReply* reply)
{
    try
    {
        if (reply->error() != QNetworkReply::NoError)
            throw std::runtime_error(QString("Ошибка при запросе к серверу. Код ошибки %1").arg(reply->error()).toStdString());

        const QByteArray response = reply->readAll();
        QJsonParseError parseError;
        const QJsonDocument doc = QJsonDocument::fromJson(response, &parseError);

        if (parseError.error != QJsonParseError::NoError)
            throw std::runtime_error(QString("Ошибка разбора JSON: %1").arg(parseError.error).toStdString());

        reply->deleteLater();
    }
    catch (const std::exception& ex)
    {
        qWarning() << ex.what();
        reply->deleteLater();
    }
}
