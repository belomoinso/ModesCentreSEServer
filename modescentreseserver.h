#ifndef MODESCENTRESESERVER_H
#define MODESCENTRESESERVER_H

#include <QObject>

#include "modescentremodel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>

class ModesCentreSEServer : public QTcpServer
{
    Q_OBJECT
public:
    ModesCentreSEServer(QObject* parent = nullptr);

    Q_PROPERTY(ModesCentreModel* model READ model CONSTANT)
    ModesCentreModel* model() { return m_model.get(); }

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QJsonArray getValues(const QString& code, int type, QDateTime& date);

private:
    QByteArray m_requestData;
    std::unique_ptr<ModesCentreModel> m_model = nullptr;
};

#endif // MODESCENTRESESERVER_H
