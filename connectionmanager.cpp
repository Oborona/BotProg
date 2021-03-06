#include "connectionmanager.h"

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent)
{
    token = "0";
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkFinished(QNetworkReply*)));
    connect(manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(getErrors(QNetworkReply*,QList<QSslError>)));

    QString getUrl;
    getUrl += "https://api.vk.com/method/users.get?user_id=5282&v=5.40&access_token=";
    getUrl += token;
    QNetworkRequest request;
    request.setUrl(getUrl);
    manager->get(request);


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
    // ����������� ��� ��� ���� ���� � ��� ��� ��� ��������� �������
    // ������ ���������
    if (replyString.contains("count"))
    {
        QJsonDocument response = QJsonDocument::fromJson(replyString.toUtf8());
        QJsonObject object = response.object();
        if (object.isEmpty())
        {
            qDebug() << "Response is empty!";
        }
        else
        {
            // ��������� ������ ���������
            QJsonValue responseValue = object.value("response");

            // ������ ��� ��������
            QJsonObject response = responseValue.toObject();

            // �������� ������ �������
            QJsonArray items = response["items"].toArray();

            // �������� �� ������� ����
            for(int i = 0; i < items.size(); i++)
            {
                // �������� ����� �� �������
                QJsonObject item = items.at(i).toObject();

                // �������� ����� ��������� �� ������
                QJsonValue messageValue = item.value("message");

                // ������� ������ ���������
                QJsonObject message = messageValue.toObject();

                // �������� ����� � ���� �� ���������
                QString str = message.value("title").toString();
                str += QString("/./%1/./%2").arg(message.value("user_id").toInt()).arg(message.value("chat_id").toInt());

                //qDebug() << str;
                emit sendDialogInfo(str);
            }

        }
//        QStringList response = replyString.split("{");
//        for (auto i = 0; i < response.size(); i++)
//        {
//            qDebug() << response.at(i);
//            qDebug() << "____________";
//        }
    }
    //qDebug() << replyString.toUtf8();

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
