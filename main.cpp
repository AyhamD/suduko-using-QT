#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QApplication>

#include "interface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    interface *interfac = new interface();
    interfac->show();

    return a.exec();
}
