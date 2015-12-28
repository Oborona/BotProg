#ifndef ACTIONWINDOW_H
#define ACTIONWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QDebug>
#include <QComboBox>


class ActionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ActionWindow(QWidget *parent = 0);

    QRadioButton* toUser;
    QRadioButton* toChat;
    QLineEdit* idString;
    QComboBox* contactsBox;
    //QMap<QString, QString> contacts;
    QGridLayout* actionLayout;
    QPushButton* sendButton;
    QTextEdit* sendString;
    QPushButton* refreshButton;

signals:
    void newRequest(QString request);

public slots:
    void sendButtonClicked(bool);
    void refreshButtonClicked(bool);
    void catchDialogInfo(QString dialogInfo);
};

#endif // ACTIONWINDOW_H
