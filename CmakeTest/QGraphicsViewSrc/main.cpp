#include "QGraphicsViewDemo.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QGraphicsViewDemo w;
    w.show();
    return a.exec();
}
