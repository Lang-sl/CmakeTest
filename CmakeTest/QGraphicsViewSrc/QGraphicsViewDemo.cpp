#include "QGraphicsViewDemo.h"
#include "ui_QGraphicsViewDemo.h"

QGraphicsViewDemo::QGraphicsViewDemo(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QGraphicsViewDemo)
{
    ui->setupUi(this);
}

QGraphicsViewDemo::~QGraphicsViewDemo()
{
    delete ui;
}

