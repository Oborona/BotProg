#ifndef ACTIONWINDOW_H
#define ACTIONWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QDebug>


class ActionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ActionWindow(QWidget *parent = 0);

    QRadioButton* toUser;
    QRadioButton* toChat;
    QLineEdit* idString;
    QGridLayout* actionLayout;
    QPushButton* sendButton;
    QTextEdit* sendString;
    QPushButton* refreshButton;

signals:
    void newRequest(QString request);

public slots:
    void sendButtonClicked(bool);
    void refreshButtonClicked(bool);
};

#endif // ACTIONWINDOW_H
