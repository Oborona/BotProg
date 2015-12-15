#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QWebView>

#include "actionwindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    QWebView* webWin;
    QGridLayout* layout;
    ActionWindow* actionWin;

    QString findToken(QString str);

signals:
    void newToken(QString str);

public slots:
    void tokenIsInvalid();
    void urlChanged(QUrl url);
};

#endif // MAINWINDOW_H
