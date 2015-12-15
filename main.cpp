#include <QGuiApplication>
#include <QApplication>
#include "volkbot.h"

int main(int ac, char** av)
{
    QApplication* vb = new QApplication(ac, av);

    VolkBot* volk = new VolkBot();

    return vb->exec();
}
