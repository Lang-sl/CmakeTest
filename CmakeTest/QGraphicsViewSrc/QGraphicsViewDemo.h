#pragma once
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QDockWidget>
#include <QPushButton>
#include "QGraphicsItemBasic.h"
#include "QGraphicsSceneBasic.h"
#include "QGraphicsViewBasic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QGraphicsViewDemo; }
QT_END_NAMESPACE

class QGraphicsViewDemo : public QMainWindow
{
    Q_OBJECT

public:
    QGraphicsViewDemo(QWidget* parent = nullptr);
    ~QGraphicsViewDemo();

    //void setBtnEnabled(bool enable);

private slots:
    void on_circleBtn_clicked();

    void on_ellipseBtn_clicked();

    void on_squareBtn_clicked();

    void on_rectangleBtn_clicked();

    void on_polygonBtn_clicked();

    void on_clearBtn_clicked();

private:
    Ui::QGraphicsViewDemo* ui;


    QGraphicsSceneBasic m_scene;
    QGraphicsViewBasic m_view;
};
