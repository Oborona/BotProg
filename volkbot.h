#ifndef VOLKBOT_H
#define VOLKBOT_H

#include <QObject>

#include "mainwindow.h"
#include "connectionmanager.h"

class VolkBot : public QObject
{
    Q_OBJECT
public:
    explicit VolkBot(QObject *parent = 0);

    MainWindow* win;
    ConnectionManager* manager;

signals:

public slots:
};

#endif // VOLKBOT_H
