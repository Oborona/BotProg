#include "actionwindow.h"

ActionWindow::ActionWindow(QWidget *parent) : QWidget(parent)
{
    sendButton = new QPushButton("Send");
    connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(sendButtonClicked(bool)));
    sendString = new QTextEdit("text");

    refreshButton = new QPushButton("Refresh Dialogs");
    connect(refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshButtonClicked(bool)));

    toUser = new QRadioButton(this);
    toChat = new QRadioButton(this);
    toChat->setChecked(true);
    idString = new QLineEdit("83");

    actionLayout = new QGridLayout(this);
        actionLayout->addWidget(toUser, 0, 0, 1, 1);
        actionLayout->addWidget(toChat, 0, 1, 1, 1);
        actionLayout->addWidget(idString, 1, 0, 1, 2);
        actionLayout->addWidget(sendButton, 2, 0, 1, 2);
        actionLayout->addWidget(sendString, 0, 2, -1, 1);
        actionLayout->addWidget(refreshButton, 0, 3, 1, 1);
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
