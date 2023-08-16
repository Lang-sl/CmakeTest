#include "QGraphicsViewDemo.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

QGraphicsViewDemo::QGraphicsViewDemo(QWidget* parent)
    : QMainWindow(parent)
{
    //ui->setupUi(this);
    setWindowTitle(tr("二维画板"));
    setFixedSize(1024, 768);

    m_showColorItem = true;
    m_scene = new QGraphicsSceneBasic(this);
    m_view = new QGraphicsViewBasic(this);
    m_scene->setBackgroundBrush(QBrush("#F8F8FF"));
    m_view->setScene(m_scene);
    setCentralWidget(m_view);

    QDockWidget *navigationDock = new QDockWidget(tr("工具栏"), this);
    addDockWidget(Qt::LeftDockWidgetArea, navigationDock);
    //m_view.show();
    //ui->graphicsView->setScene(&m_scene);

    QPushButton* showColorBtn = new QPushButton(tr("颜色显示"), navigationDock);
    QPushButton* circleBtn = new QPushButton(tr("圆"), navigationDock);
    QPushButton* ellipseBtn = new QPushButton(tr("椭圆"), navigationDock);
    QPushButton* pieBtn = new QPushButton(tr("圆弧"), navigationDock);
    QPushButton* squareBtn = new QPushButton(tr("正方形"), navigationDock);
    QPushButton* rectangleBtn = new QPushButton(tr("矩形"), navigationDock);
    QPushButton* lineBtn = new QPushButton(tr("直线"), navigationDock);
    QPushButton* pointBtn = new QPushButton(tr("点"), navigationDock);
    QPushButton* clearBtn = new QPushButton(tr("清空"), navigationDock);

    QVBoxLayout* btnlayout = new QVBoxLayout(navigationDock);

    QSpacerItem* spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);

    btnlayout->addItem(spacer);
    btnlayout->addWidget(showColorBtn);
    btnlayout->addWidget(circleBtn);
    btnlayout->addWidget(ellipseBtn);
    btnlayout->addWidget(pieBtn);
    btnlayout->addWidget(squareBtn);
    btnlayout->addWidget(rectangleBtn);
    btnlayout->addWidget(lineBtn);
    btnlayout->addWidget(pointBtn);
    btnlayout->addWidget(clearBtn);
    btnlayout->addItem(spacer);

    QWidget* widget = new QWidget(navigationDock);
    widget->setLayout(btnlayout);
    navigationDock->setWidget(widget);

    connect(showColorBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_showColorItem_clicked);
    connect(circleBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_circleBtn_clicked);
    connect(ellipseBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_ellipseBtn_clicked);
    connect(squareBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_squareBtn_clicked);
    connect(rectangleBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_rectangleBtn_clicked);
    connect(clearBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_clearBtn_clicked);
    connect(lineBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_lineBtn_clicked);
    connect(pointBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_pointBtn_clicked);
    connect(pieBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_pieBtn_clicked);
}

QGraphicsViewDemo::~QGraphicsViewDemo()
{
    //this->deleteLater();
}

void QGraphicsViewDemo::on_circleBtn_clicked()
{
    BCircle* m_circle = new BCircle(0, 0, 50, QGraphicsItemBasic::ItemType::Circle);
    m_scene->addItem(m_circle);
}

void QGraphicsViewDemo::on_ellipseBtn_clicked()
{
    BEllipse* m_ellipse = new BEllipse(0, 0, 120, 80, QGraphicsItemBasic::ItemType::Ellipse);
    m_scene->addItem(m_ellipse);
}

void QGraphicsViewDemo::on_pieBtn_clicked()
{
    BPie* m_pie = new BPie(0, 0, 80, 30, QGraphicsItemBasic::ItemType::Pie);
    m_scene->addItem(m_pie);
}

void QGraphicsViewDemo::on_squareBtn_clicked()
{
    BSquare* m_square = new BSquare(0, 0, 60, QGraphicsItemBasic::ItemType::Square);
    m_scene->addItem(m_square);
}

void QGraphicsViewDemo::on_rectangleBtn_clicked()
{
    BRectangle* m_rectangle = new BRectangle(0, 0, 80, 60, QGraphicsItemBasic::ItemType::Rectangle);
    m_scene->addItem(m_rectangle);
}

void QGraphicsViewDemo::on_clearBtn_clicked()
{
    m_scene->clear();
    m_scene->addColorItem();
    m_scene->isShowColorItem(m_showColorItem);
}

void QGraphicsViewDemo::on_lineBtn_clicked()
{
    BLine* m_line = new BLine( QPointF(0,0), QPointF(100,100), QGraphicsItemBasic::ItemType::Line);
    m_scene->addItem(m_line);
}

void QGraphicsViewDemo::on_pointBtn_clicked()
{
    BPoint* m_point = new BPoint(QPointF(0, 0), QGraphicsItemBasic::ItemType::Point);
    m_scene->addItem(m_point);
}

void QGraphicsViewDemo::on_showColorItem_clicked()
{
    m_showColorItem = !m_showColorItem;
    m_scene->isShowColorItem(m_showColorItem);
}


//void QGraphicsViewDemo::setBtnEnabled(bool enable)
//{
//    ui->circleBtn->setEnabled(enable);
//    ui->ellipseBtn->setEnabled(enable);
//    ui->conCircleBtn->setEnabled(enable);
//    ui->pieBtn->setEnabled(enable);
//    ui->chordBtn->setEnabled(enable);
//    ui->squareBtn->setEnabled(enable);
//    ui->rectangleBtn->setEnabled(enable);
//    ui->roundRecBtn->setEnabled(enable);
//    ui->rnRecBtn->setEnabled(enable);
//    ui->clearBtn->setEnabled(enable);
//    ui->saveBtn->setEnabled(enable);
//    ui->loadBtn->setEnabled(enable);
//}
