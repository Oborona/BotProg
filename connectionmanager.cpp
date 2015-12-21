#include "connectionmanager.h"

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent)
{
    token = "66ba63fe69142ada1257daea8d79f0a3480eeb17552cf8480d0ae2ac5e3fcfafae45b6db4933e03926481";
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkFinished(QNetworkReply*)));
    connect(manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(getErrors(QNetworkReply*,QList<QSslError>)));

    QString getUrl;
    getUrl += "https://api.vk.com/method/users.get?user_id=5282&v=5.40&access_token=";
    getUrl += token;
    QNetworkRequest request;
    request.setUrl(getUrl);
    manager->get(request);

    //xmlReader = new QXmlReader();

}

void ConnectionManager::getNewToken(QString newToken)
{
    token = newToken;
}

void ConnectionManager::networkFinished(QNetworkReply* reply)
{
    QString replyString = reply->readAll();
    if (replyString.contains("could not get application"))
        emit tokenIsInvalid();
    // предположим что это даст инфу о том что это результат запроса
    // списка контактов
    if (replyString.contains("count"))
    {
          QXmlInputSource source;
          source.setData(replyString);
//          xmlReader->
//        QStringList response = replyString.split("{");
//        for (auto i = 0; i < response.size(); i++)
//        {
//            qDebug() << response.at(i);
//            qDebug() << "____________";
//        }
    }
    qDebug() << replyString.toUtf8();

}

void ConnectionManager::getErrors(QNetworkReply *, QList<QSslError> errors)
{
    qDebug() << errors;
}

void ConnectionManager::processNewRequest(QString str)
{
    qDebug() << str;
    QStringList requestList = str.split("/./");
    QString url;
    if (requestList.at(0) == "send")
    {
      url += "https://api.vk.com/method/messages.send?&v=5.40&access_token=";
      url += token;
      if (requestList.at(1) == "user")
          url += "&user_id";
      if (requestList.at(1) == "chat")
          url += "&chat_id=";
      url += requestList.at(2);
      url += "&message=";
      url += requestList.at(3);
    }
    if (requestList.at(0) == "refresh")
    {
        url += "https://api.vk.com/method/messages.getDialogs?&v=5.40&access_token=";
        url += token;
    }
    QNetworkRequest request;
    qDebug() << url;
    request.setUrl(url);
    manager->get(request);
}
