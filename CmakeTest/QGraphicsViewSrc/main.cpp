#include "QGraphicsViewDemo.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QGraphicsViewDemo w;
    w.show();
    return a.exec();
}
