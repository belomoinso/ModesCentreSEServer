#ifndef RESTAPICLIENT_H
#define RESTAPICLIENT_H

#include "modescentremodel.h"
#include <QNetworkAccessManager>
#include <QObject>

const QString httpPrefix(QStringLiteral("http://"));

class RestApiClient : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(ModesCentreModel* model READ model WRITE setModel NOTIFY modelChanged FINAL)
    ModesCentreModel* model() { return m_model; }
    void setModel(ModesCentreModel* model);

    Q_PROPERTY(QString ipaddr READ ipaddr WRITE setIpaddr NOTIFY ipaddrChanged)
    QString ipaddr() const { return m_ipaddr; }
    void setIpaddr(const QString& val);

    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    int port() const { return m_port; }
    void setPort(int val);

    explicit RestApiClient(QObject* parent = nullptr);
    Q_INVOKABLE void sendValues();

signals:
    void modelChanged();
    void ipaddrChanged();
    void portChanged();

private:
    void onFinished(QNetworkReply* reply);
    void updateURL();

private:
    std::unique_ptr<QNetworkAccessManager> m_manager = nullptr;
    QUrl m_url;
    QString m_ipaddr = "127.0.0.1";
    int m_port = 8080;
    ModesCentreModel* m_model;
};

#endif // RESTAPICLIENT_H
