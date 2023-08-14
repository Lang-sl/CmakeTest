#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QGraphicsViewDemo; }
QT_END_NAMESPACE

class QGraphicsViewDemo : public QMainWindow
{
    Q_OBJECT

public:
    QGraphicsViewDemo(QWidget* parent = nullptr);
    ~QGraphicsViewDemo();

private:
    Ui::QGraphicsViewDemo* ui;
};
