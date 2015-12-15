#include "volkbot.h"

VolkBot::VolkBot(QObject *parent) : QObject(parent)
{
    win = new MainWindow();
    win->show();
    manager = new ConnectionManager();
    connect(manager, SIGNAL(tokenIsInvalid()), win, SLOT(tokenIsInvalid()));
    connect(win, SIGNAL(newToken(QString)), manager, SLOT(getNewToken(QString)));
    connect(win->actionWin, SIGNAL(newRequest(QString)), manager, SLOT(processNewRequest(QString)));
}

