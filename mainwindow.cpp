#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    webWin = new QWebView();
    webWin->setToolTip("Akno");
    connect(webWin, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
//    wv->hide();

    actionWin = new ActionWindow();

    layout = new QGridLayout();
        layout->addWidget(actionWin);
    this->setLayout(layout);
}

QString MainWindow::findToken(QString str)
{
    QString toFind = "#access_token=";
    str.remove(0, str.indexOf(toFind) + toFind.length());
    toFind = "&expires";
    str.remove(str.indexOf(toFind), str.length() - str.indexOf(toFind));
    return str;
}

void MainWindow::tokenIsInvalid()
{
    layout->removeWidget(actionWin);
    layout->addWidget(webWin);
//    this->setLayout(wvLayout);
    webWin->setUrl(QUrl("https://oauth.vk.com/authorize?client_id=3682744%20&scope=offline,messages,wall&v=5.40&redirect_uri=https://oauth.vk.com/blank.html&response_type=token"));
}

void MainWindow::urlChanged(QUrl url)
{
    qDebug() << url;
    QString urlStr = url.toString();
    if (urlStr.contains("access_token"))
    {
        emit newToken(findToken(urlStr));
        layout->removeWidget(webWin);
        layout->addWidget(actionWin);
   }
}
