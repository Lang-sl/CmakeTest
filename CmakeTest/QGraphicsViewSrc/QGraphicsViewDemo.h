#pragma once
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QDockWidget>
#include <QPushButton>
#include "QGraphicsItemBasic.h"
#include "QGraphicsSceneBasic.h"
#include "QGraphicsViewBasic.h"
#include "ui_QGraphicsViewDemo.h"

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

    void on_pieBtn_clicked();

    void on_squareBtn_clicked();

    void on_rectangleBtn_clicked();

    void on_clearBtn_clicked();

    void on_lineBtn_clicked();

    void on_pointBtn_clicked();

    void on_polygonBtn_clicked();

    void on_mixArcLineItemsBtn_clicked();

    //void on_showColorItem_clicked();

    void on_itemFocusIn(QGraphicsItemBasic* i);

    void on_itemFocusOut(QGraphicsItemBasic* i);

    void setBtnEnabled(bool enable);

private:
    void updateConfig(QGraphicsItemBasic* i);
    
    Ui::QGraphicsViewDemo ui;

    QGraphicsSceneBasic* m_scene;
    QGraphicsViewBasic* m_view;

    QDockWidget* leftNavigationDock;
    QDockWidget* rightNavigationDock;

    QPushButton* circleBtn;
    QPushButton* ellipseBtn;
    QPushButton* pieBtn;
    QPushButton* squareBtn;
    QPushButton* rectangleBtn;
    QPushButton* lineBtn;
    QPushButton* pointBtn;
    QPushButton* polygonBtn;
    QPushButton* mixArcLineItemsBtn;
    QPushButton* clearBtn;

    bool m_showColorItem;

    QLabel* type;

    QLineEdit* center_x;
    QLineEdit* center_y;

    QLineEdit* edge_x;
    QLineEdit* edge_y;
};
