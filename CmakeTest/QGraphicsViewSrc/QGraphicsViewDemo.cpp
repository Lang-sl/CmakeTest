#include "QGraphicsViewDemo.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

QGraphicsViewDemo::QGraphicsViewDemo(QWidget* parent)
    : QMainWindow(parent)
{
    //ui->setupUi(this);
    setWindowTitle(tr("二维画板"));
    //setFixedSize(1024, 768);

    m_showColorItem = true;
    m_view = new QGraphicsViewBasic(this);
    setCentralWidget(m_view);

    leftNavigationDock = new QDockWidget(tr("工具栏"), this);
    leftNavigationDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::LeftDockWidgetArea, leftNavigationDock);

    rightNavigationDock = new QDockWidget(tr("参数"), this);
    rightNavigationDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    rightNavigationDock->hide();
    addDockWidget(Qt::RightDockWidgetArea, rightNavigationDock);

    QSpacerItem* spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QLabel* typeLabel = new QLabel("Type: ", rightNavigationDock);
    type = new QLabel("type", rightNavigationDock);
    type->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    QLabel* centerLabel = new QLabel("CenterPoint: ", rightNavigationDock);
    center_x = new QLineEdit;
    center_y = new QLineEdit;
    center_x->setMaximumWidth(50);
    center_y->setMaximumWidth(50);
    QLabel* edgeLabel = new QLabel("EdgePoint_1: ", rightNavigationDock);
    edge_x = new QLineEdit;
    edge_y = new QLineEdit;
    edge_x->setMaximumWidth(50);
    edge_y->setMaximumWidth(50);

    QGridLayout* configlayout = new QGridLayout(rightNavigationDock);

    configlayout->addItem(spacer, 0, 0);
    configlayout->addWidget(typeLabel, 1, 0);
    configlayout->addWidget(type, 1, 1);
    configlayout->addWidget(centerLabel, 2, 0);
    configlayout->addWidget(center_x, 2, 1);
    configlayout->addWidget(center_y, 2, 2);
    configlayout->addWidget(edgeLabel, 3, 0);
    configlayout->addWidget(edge_x, 3, 1);
    configlayout->addWidget(edge_y, 3, 2);
    configlayout->addItem(spacer, 4, 0);

    QWidget* rightDockWidget = new QWidget(leftNavigationDock);
    rightDockWidget->setLayout(configlayout);
    rightNavigationDock->setWidget(rightDockWidget);
    //m_view.show();
    //ui->graphicsView->setScene(&m_scene);

    //QPushButton* showColorBtn = new QPushButton(tr("颜色显示"), leftNavigationDock);
    //circleBtn = new QPushButton(tr("圆"), leftNavigationDock);
    //ellipseBtn = new QPushButton(tr("椭圆"), leftNavigationDock);
    pieBtn = new QPushButton(tr("圆弧"), leftNavigationDock);
    //squareBtn = new QPushButton(tr("正方形"), leftNavigationDock);
    //rectangleBtn = new QPushButton(tr("矩形"), leftNavigationDock);
    //lineBtn = new QPushButton(tr("直线"), leftNavigationDock);
    //pointBtn = new QPushButton(tr("点"), leftNavigationDock);
    polygonBtn = new QPushButton(tr("多边形"), leftNavigationDock);
    mixArcLineItemsBtn = new QPushButton(tr("混合直线圆弧"), leftNavigationDock);
    clearBtn = new QPushButton(tr("清空"), leftNavigationDock);

    QVBoxLayout* btnlayout = new QVBoxLayout(leftNavigationDock);

    btnlayout->addItem(spacer);
    //btnlayout->addWidget(showColorBtn);
    //btnlayout->addWidget(circleBtn);
    //btnlayout->addWidget(ellipseBtn);
    btnlayout->addWidget(pieBtn);
    //btnlayout->addWidget(squareBtn);
    //btnlayout->addWidget(rectangleBtn);
    //btnlayout->addWidget(lineBtn);
    //btnlayout->addWidget(pointBtn);
    btnlayout->addWidget(polygonBtn);
    btnlayout->addWidget(mixArcLineItemsBtn);
    btnlayout->addWidget(clearBtn);
    btnlayout->addItem(spacer);

    QWidget* leftDockWidget = new QWidget(leftNavigationDock);
    leftDockWidget->setLayout(btnlayout);
    leftNavigationDock->setWidget(leftDockWidget);

    //connect(showColorBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_showColorItem_clicked);
    //connect(circleBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_circleBtn_clicked);
    //connect(ellipseBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_ellipseBtn_clicked);
    //connect(squareBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_squareBtn_clicked);
    //connect(rectangleBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_rectangleBtn_clicked);
    connect(clearBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_clearBtn_clicked);
    //connect(lineBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_lineBtn_clicked);
    //connect(pointBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_pointBtn_clicked);
    connect(pieBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_pieBtn_clicked);
    connect(polygonBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_polygonBtn_clicked);
    connect(mixArcLineItemsBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_mixArcLineItemsBtn_clicked);

    connect(m_view, &QGraphicsViewBasic::ItemFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_view, &QGraphicsViewBasic::ItemFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);
}

QGraphicsViewDemo::~QGraphicsViewDemo()
{
    //this->deleteLater();
}

void QGraphicsViewDemo::on_circleBtn_clicked()
{
    BCircle* m_circle = new BCircle(0, 0, 50, QGraphicsItemBasic::ItemType::Circle);
    m_view->addItem(QGraphicsItemBasic::ItemType::Circle);
    connect(m_circle, &QGraphicsItemBasic::isFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_circle, &QGraphicsItemBasic::isFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);
}

void QGraphicsViewDemo::on_ellipseBtn_clicked()
{
    BEllipse* m_ellipse = new BEllipse(0, 0, 120, 80, QGraphicsItemBasic::ItemType::Ellipse);
    m_view->addItem(QGraphicsItemBasic::ItemType::Ellipse);
    connect(m_ellipse, &QGraphicsItemBasic::isFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_ellipse, &QGraphicsItemBasic::isFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);
}

void QGraphicsViewDemo::on_pieBtn_clicked()
{
    BArc* m_pie = new BArc(0, 0, 80, -30, 30, QGraphicsItemBasic::ItemType::Arc);
    m_view->addItem(QGraphicsItemBasic::ItemType::Arc);
    connect(m_pie, &BArc::isFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_pie, &BArc::isFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);
}

void QGraphicsViewDemo::on_squareBtn_clicked()
{
    BSquare* m_square = new BSquare(0, 0, 60, QGraphicsItemBasic::ItemType::Square);
    m_view->addItem(QGraphicsItemBasic::ItemType::Square);
    connect(m_square, &QGraphicsItemBasic::isFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_square, &QGraphicsItemBasic::isFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);
}

void QGraphicsViewDemo::on_rectangleBtn_clicked()
{
    BRectangle* m_rectangle = new BRectangle(0, 0, 80, 60, QGraphicsItemBasic::ItemType::Rectangle);
    m_view->addItem(QGraphicsItemBasic::ItemType::Rectangle);
    connect(m_rectangle, &QGraphicsItemBasic::isFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_rectangle, &QGraphicsItemBasic::isFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);
}

void QGraphicsViewDemo::on_clearBtn_clicked()
{
    m_view->clear();
}

void QGraphicsViewDemo::on_lineBtn_clicked()
{
    BLine* m_line = new BLine( QPointF(0,0), QPointF(100,100), QGraphicsItemBasic::ItemType::Line);
    m_view->addItem(QGraphicsItemBasic::ItemType::Line);
    connect(m_line, &QGraphicsItemBasic::isFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_line, &QGraphicsItemBasic::isFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);
}

void QGraphicsViewDemo::on_pointBtn_clicked()
{
    BPoint* m_point = new BPoint(QPointF(0, 0), QGraphicsItemBasic::ItemType::Point);
    m_view->addItem(QGraphicsItemBasic::ItemType::Point);
    connect(m_point, &QGraphicsItemBasic::isFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_point, &QGraphicsItemBasic::isFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);
}

void QGraphicsViewDemo::on_polygonBtn_clicked()
{
    /*m_view->startCreateBPolygon();
    setBtnEnabled(false);
    BPolygon* m_polygon = new BPolygon(QGraphicsItemBasic::ItemType::Polygon);
    m_view->addItem(m_polygon);

    connect(m_polygon, &BPolygon::isFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_polygon, &BPolygon::isFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);

    connect(m_scene, SIGNAL(updatePoint(QPointF, QList<QPointF>, bool)), m_polygon, SLOT(pushPoint(QPointF, QList<QPointF>, bool)));*/
}

void QGraphicsViewDemo::on_mixArcLineItemsBtn_clicked()
{
    //setBtnEnabled(false);
    m_view->addItem(QGraphicsItemBasic::ItemType::MixArcLineItems);

    /*connect(m_mixArcLineItems, &BMixArcLineItems::isFocusIn, this, &QGraphicsViewDemo::on_itemFocusIn);
    connect(m_mixArcLineItems, &BMixArcLineItems::isFocusOut, this, &QGraphicsViewDemo::on_itemFocusOut);*/
}

//void QGraphicsViewDemo::on_showColorItem_clicked()
//{
//    m_showColorItem = !m_showColorItem;
//    m_scene->isShowColorItem(m_showColorItem);
//}

void QGraphicsViewDemo::on_itemFocusIn(QAbstractGraphicsShapeItem* i)
{
    // 参数
    center_x->disconnect();
    center_y->disconnect();
    edge_x->disconnect();
    edge_y->disconnect();
    QGraphicsItemBasic* item = dynamic_cast<QGraphicsItemBasic*>(i);
    if (item != nullptr)
    {
        QGraphicsItemBasic::ItemType itemType = item->getType();
        switch (itemType) {
        case QGraphicsItemBasic::ItemType::Ellipse: {
            BEllipse* ellipse = dynamic_cast<BEllipse*>(item);
            updateConfig(ellipse);
        } break;
        case QGraphicsItemBasic::ItemType::Circle: {
            BCircle* circle = dynamic_cast<BCircle*>(item);
            updateConfig(circle);
        } break;
        case QGraphicsItemBasic::ItemType::Arc: {
            BArc* pie = dynamic_cast<BArc*>(item);
            updateConfig(pie);
            connect(center_x, &QLineEdit::editingFinished, [=]()
                    {
                        pie->moveBy(center_x->text().toDouble() - pie->mapToScene(pie->getCenter()).x(), 0);
                        updateConfig(pie);
                    });
            connect(center_y, &QLineEdit::editingFinished, [=]()
                    {
                        pie->moveBy(0, center_y->text().toDouble() - pie->mapToScene(pie->getCenter()).y());
                        updateConfig(pie);
                    });
            connect(edge_x, &QLineEdit::editingFinished, [=]()
                    {
                        QPointF origin = pie->mapToScene(pie->getPointFList()[0]);
                        QPointF end = QPointF(edge_x->text().toDouble(), origin.y());
                        //pie->updatePolygon(polygon->getPointList()[0], polygon->mapFromScene(end));
                        updateConfig(pie);
                    });
            connect(edge_y, &QLineEdit::editingFinished, [=]()
                    {
                        QPointF origin = pie->mapToScene(pie->getPointFList()[0]);
                        QPointF end = QPointF(origin.x(), edge_y->text().toDouble());
                        //polygon->updatePolygon(polygon->getPointList()[0], polygon->mapFromScene(end));
                        updateConfig(pie);
                    });
        } break;
        case QGraphicsItemBasic::ItemType::Rectangle: {
            BRectangle* rectangle = dynamic_cast<BRectangle*>(item);
            updateConfig(rectangle);
        } break;
        case QGraphicsItemBasic::ItemType::Square: {
            BSquare* square = dynamic_cast<BSquare*>(item);
            updateConfig(square);
        } break;
        case QGraphicsItemBasic::ItemType::Line: {
            BLine* line = dynamic_cast<BLine*>(item);
            updateConfig(line);
        } break;
        case QGraphicsItemBasic::ItemType::Point: {
            BPoint* point = dynamic_cast<BPoint*>(item);
            updateConfig(point);
        } break;
        case QGraphicsItemBasic::ItemType::Polygon: {
            BPolygon* polygon = dynamic_cast<BPolygon*>(item);
            updateConfig(polygon);
            connect(center_x, &QLineEdit::editingFinished, [=]()
                    {
                        polygon->moveBy(center_x->text().toDouble() - polygon->mapToScene(polygon->getCenter()).x(), 0);
                        updateConfig(polygon);
                    });
            connect(center_y, &QLineEdit::editingFinished, [=]()
                    {
                        polygon->moveBy(0, center_y->text().toDouble() - polygon->mapToScene(polygon->getCenter()).y());
                        updateConfig(polygon);
                    });
            connect(edge_x, &QLineEdit::editingFinished, [=]()
                    {
                        QPointF origin = polygon->mapToScene(polygon->getPointFList()[0]);
                        QPointF end = QPointF(edge_x->text().toDouble(), origin.y());
                        polygon->updatePolygon(polygon->getPointFList()[0], polygon->mapFromScene(end));
                        updateConfig(polygon);
                    });
            connect(edge_y, &QLineEdit::editingFinished, [=]()
                    {
                        QPointF origin = polygon->mapToScene(polygon->getPointFList()[0]);
                        QPointF end = QPointF(origin.x(), edge_y->text().toDouble());
                        polygon->updatePolygon(polygon->getPointFList()[0], polygon->mapFromScene(end));
                        updateConfig(polygon);
                    });
        } break;
        default: break;
        }
    }
    BPointItem* pointItem = dynamic_cast<BPointItem*>(i);
    if (pointItem != nullptr)
    {
        type->setText("顶点");
        center_x->setText(QString::number(pointItem->getPoint().x()));
        center_y->setText(QString::number(pointItem->getPoint().y()));
        qDebug() << "选中顶点";
        qDebug() << pointItem->getPoint();
    }
    rightNavigationDock->show();
}

void QGraphicsViewDemo::on_itemFocusOut(QAbstractGraphicsShapeItem* i)
{
    bool isFocus = false;
    QList<QWidget*> childWidgets = rightNavigationDock->findChildren<QWidget*>();
    for each(QWidget * childWidget in childWidgets) {
        if (childWidget->hasFocus()) {
            isFocus = true;
        }
    }
    if (rightNavigationDock->hasFocus() || isFocus)
    {
        //i->focusInEvent(nullptr);
    }
    else
    {
        rightNavigationDock->hide();
    }
}


void QGraphicsViewDemo::setBtnEnabled(bool enable)
{
    /*circleBtn->setEnabled(enable);
    ellipseBtn->setEnabled(enable);*/
    pieBtn->setEnabled(enable);
    /*squareBtn->setEnabled(enable);
    rectangleBtn->setEnabled(enable);
    lineBtn->setEnabled(enable);
    pointBtn->setEnabled(enable);*/
    clearBtn->setEnabled(enable);
}

void QGraphicsViewDemo::updateConfig(QGraphicsItemBasic* i)
{
    QGraphicsItemBasic* item = static_cast<QGraphicsItemBasic*>(i);
    QGraphicsItemBasic::ItemType itemType = item->getType();
    switch (itemType) {
    case QGraphicsItemBasic::ItemType::Ellipse: {
        BEllipse* ellipse = dynamic_cast<BEllipse*>(item);
        type->setText("椭圆");
        //center_x->setText(QString("(x: %1,y: %2)").arg(QString::number(ellipse->getCenter().x())).arg(QString::number(ellipse->getCenter().y())));
        center_x->setText(QString::number(ellipse->mapToScene(ellipse->getCenter()).x()));
        center_y->setText(QString::number(ellipse->mapToScene(ellipse->getCenter()).y()));
        //edge_x->setText(QString::number(ellipse->getItemedgePosInScene().x()));
        //edge_y->setText(QString::number(ellipse->getItemedgePosInScene().y()));
    } break;
    case QGraphicsItemBasic::ItemType::Circle: {
        BCircle* circle = dynamic_cast<BCircle*>(item);
        type->setText("圆");
        //center_x->setText(QString::number(circle->getItemPosInScene().x()));
        //center_y->setText(QString::number(circle->getItemPosInScene().y()));
        //edge_x->setText(QString::number(circle->getItemedgePosInScene().x()));
        //edge_y->setText(QString::number(circle->getItemedgePosInScene().y()));
    } break;
    case QGraphicsItemBasic::ItemType::Arc: {
        BArc* pie = dynamic_cast<BArc*>(item);
        type->setText("圆弧");
        /*center_x->setText(QString::number(pie->mapToScene(pie->getCenter()).x()));
        center_y->setText(QString::number(pie->mapToScene(pie->getCenter()).y()));
        edge_x->setText(QString::number(pie->mapToScene(pie->getPointList()[0]).x()));
        edge_y->setText(QString::number(pie->mapToScene(pie->getPointList()[0]).y()));*/
    } break;
    case QGraphicsItemBasic::ItemType::Rectangle: {
        BRectangle* rectangle = dynamic_cast<BRectangle*>(item);
        type->setText("矩形");
        //center_x->setText(QString::number(rectangle->getItemPosInScene().x()));
        //center_y->setText(QString::number(rectangle->getItemPosInScene().y()));
        //edge_x->setText(QString::number(rectangle->getItemedgePosInScene().x()));
        //edge_y->setText(QString::number(rectangle->getItemedgePosInScene().y()));
    } break;
    case QGraphicsItemBasic::ItemType::Square: {
        BSquare* square = dynamic_cast<BSquare*>(item);
        type->setText("正方形");
        //center_x->setText(QString::number(square->getItemPosInScene().x()));
        //center_y->setText(QString::number(square->getItemPosInScene().y()));
        //edge_x->setText(QString::number(square->getItemedgePosInScene().x()));
        //edge_y->setText(QString::number(square->getItemedgePosInScene().y()));
    } break;
    case QGraphicsItemBasic::ItemType::Line: {
        BLine* line = dynamic_cast<BLine*>(item);
        type->setText("直线");
        //center_x->setText(QString::number(line->getItemPosInScene().x()));
        //center_y->setText(QString::number(line->getItemPosInScene().y()));
        //edge_x->setText(QString::number(line->getItemedgePosInScene().x()));
        //edge_y->setText(QString::number(line->getItemedgePosInScene().y()));
    } break;
    case QGraphicsItemBasic::ItemType::Point: {
        BPoint* point = dynamic_cast<BPoint*>(item);
        type->setText("点");
        //center_x->setText(QString::number(point->getItemPosInScene().x()));
        //center_y->setText(QString::number(point->getItemPosInScene().y()));
        //edge_x->setText(QString::number(point->getItemedgePosInScene().x()));
        //edge_y->setText(QString::number(point->getItemedgePosInScene().y()));
    } break;
    case QGraphicsItemBasic::ItemType::Polygon: {
        BPolygon* polygon = dynamic_cast<BPolygon*>(item);
        type->setText("多边形");
        center_x->setText(QString::number(polygon->mapToScene(polygon->getCenter()).x()));
        center_y->setText(QString::number(polygon->mapToScene(polygon->getCenter()).y()));
        edge_x->setText(QString::number(polygon->mapToScene(polygon->getPointFList()[0]).x()));
        edge_y->setText(QString::number(polygon->mapToScene(polygon->getPointFList()[0]).y()));
    } break;
    default: break;
    }
}
