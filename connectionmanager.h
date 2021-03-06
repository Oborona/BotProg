#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMessageBox>
#include <QQueue>

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionManager(QObject *parent = 0);
    QNetworkAccessManager* manager;
    QString token;

    QQueue<QString>* queue;

signals:
    void tokenIsInvalid();
    void sendDialogInfo(QString dialog);

public slots:
    void getNewToken(QString newToken);
    void networkFinished(QNetworkReply* reply);
    void getErrors(QNetworkReply*, QList<QSslError> errors);

    void processNewRequest(QString str);
};

#endif // CONNECTIONMANAGER_H
