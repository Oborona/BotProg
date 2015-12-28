#include "actionwindow.h"

ActionWindow::ActionWindow(QWidget *parent) : QWidget(parent)
{
    sendButton = new QPushButton("Send");
    connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(sendButtonClicked(bool)));
    sendString = new QTextEdit("text");

    refreshButton = new QPushButton("Refresh Dialogs");
    connect(refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshButtonClicked(bool)));

//    toUser = new QRadioButton(this);
//    toChat = new QRadioButton(this);
//    toChat->setChecked(true);
//    idString = new QLineEdit("83");
    contactsBox = new QComboBox(this);
    contactsBox->setFixedWidth(300);


    actionLayout = new QGridLayout(this);
//        actionLayout->addWidget(toUser, 0, 0, 1, 1);
//        actionLayout->addWidget(toChat, 0, 1, 1, 1);
//        actionLayout->addWidget(idString, 1, 0, 1, 2);
        actionLayout->addWidget(contactsBox, 0, 0, 1, 1);
        actionLayout->addWidget(sendButton, 1, 0, 1, 1);
        actionLayout->addWidget(sendString, 0, 1, -1, 1);
        actionLayout->addWidget(refreshButton, 0, 2, -1, 1);
    this->setLayout(actionLayout);
}

void ActionWindow::sendButtonClicked(bool)
{
    QString requestString;
    // send: "send" + chat or user + id + text
    requestString += QString("send/./");
    if (toUser->isChecked())
        requestString += "user/./";
    else
        requestString += "chat/./";
    requestString += idString->text() + "/./";
    requestString += sendString->toPlainText();
    emit newRequest(requestString);
}

void ActionWindow::refreshButtonClicked(bool)
{
    emit newRequest("refresh");
}

void ActionWindow::catchDialogInfo(QString dialogInfo)
{
    // 0 — title
    // 1 — user id
    // 2 — chat id
    QStringList infoList = dialogInfo.split("/./");
    QString userId = infoList.at(1);

    qDebug() << dialogInfo;
    bool ok;
    bool found = false;
    for (int i = 0; i < contactsBox->model()->rowCount(); i++)
    {
        if (contactsBox->itemData(i) != NULL && contactsBox->itemData(i) == infoList.at(1))
        {
            found = true;
        }
    }
    if (found == false)
    {
        if (infoList.at(0) == " ... ")
            contactsBox->addItem(infoList.at(1), userId.toInt(&ok, 10));
        else
            contactsBox->addItem(infoList.at(0), userId.toInt(&ok, 10));
    }

//    if (!contactsBox-.contains(infoList.at(1)))
//    {
//        //contacts.insert(infoList.at(1), infoList.at(0));
//        contactsBox->addItem();
//    }
}
