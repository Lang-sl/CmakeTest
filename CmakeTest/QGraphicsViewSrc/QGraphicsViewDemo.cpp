#include "QGraphicsViewDemo.h"
#include "ui_QGraphicsViewDemo.h"

#include <QGridLayout>
#include <QVBoxLayout>

QGraphicsViewDemo::QGraphicsViewDemo(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QGraphicsViewDemo)
{
    ui->setupUi(this);
    setWindowTitle(tr("二维画板"));
    setFixedSize(1024, 768);

    m_scene.setBackgroundBrush(QBrush("#F8F8FF"));
    m_view.setScene(&m_scene);
    setCentralWidget(&m_view);

    QDockWidget *navigationDock = new QDockWidget(tr("工具栏"), this);
    addDockWidget(Qt::LeftDockWidgetArea, navigationDock);
    //m_view.show();
    //ui->graphicsView->setScene(&m_scene);

    QPushButton* circleBtn = new QPushButton(tr("圆"), this);
    QPushButton* ellipseBtn = new QPushButton(tr("椭圆"), this);
    QPushButton* squareBtn = new QPushButton(tr("正方形"), this);
    QPushButton* rectangleBtn = new QPushButton(tr("矩形"), this);
    QPushButton* clearBtn = new QPushButton(tr("清空"), this);
    //QPushButton* polygonBtn = new QPushButton(tr("多边形"), this);

    QVBoxLayout* btnlayout = new QVBoxLayout;

    btnlayout->addWidget(circleBtn);
    btnlayout->addWidget(ellipseBtn);
    btnlayout->addWidget(squareBtn);
    btnlayout->addWidget(rectangleBtn);
    btnlayout->addWidget(clearBtn);

    QWidget* widget = new QWidget(this);
    widget->setLayout(btnlayout);
    navigationDock->setWidget(widget);

    connect(circleBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_circleBtn_clicked);
    connect(ellipseBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_ellipseBtn_clicked);
    connect(squareBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_squareBtn_clicked);
    connect(rectangleBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_rectangleBtn_clicked);
    connect(clearBtn, &QPushButton::clicked, this, &QGraphicsViewDemo::on_clearBtn_clicked);
}

QGraphicsViewDemo::~QGraphicsViewDemo()
{
    delete ui;
}

void QGraphicsViewDemo::on_circleBtn_clicked()
{
    BCircle* m_circle = new BCircle(0, 0, 50, QGraphicsItemBasic::ItemType::Circle);
    m_scene.addItem(m_circle);
}

void QGraphicsViewDemo::on_ellipseBtn_clicked()
{
    BEllipse* m_ellipse = new BEllipse(0, 0, 120, 80, QGraphicsItemBasic::ItemType::Ellipse);
    m_scene.addItem(m_ellipse);
}

void QGraphicsViewDemo::on_squareBtn_clicked()
{
    BSquare* m_square = new BSquare(0, 0, 60, QGraphicsItemBasic::ItemType::Square);
    m_scene.addItem(m_square);
}

void QGraphicsViewDemo::on_rectangleBtn_clicked()
{
    BRectangle* m_rectangle = new BRectangle(0, 0, 80, 60, QGraphicsItemBasic::ItemType::Rectangle);
    m_scene.addItem(m_rectangle);
}

void QGraphicsViewDemo::on_polygonBtn_clicked()
{
    m_scene.startCreate();
    //setBtnEnabled(false);
    BPolygon* m_polygon = new BPolygon(QGraphicsItemBasic::ItemType::Polygon);
    m_scene.addItem(m_polygon);

    connect(&m_scene, SIGNAL(updatePoint(QPointF, QList<QPointF>, bool)), m_polygon, SLOT(pushPoint(QPointF, QList<QPointF>, bool)));
    //connect(&m_scene, &QGraphicsSceneBasic::createFinished, [=]() { setBtnEnabled(true); });
}

void QGraphicsViewDemo::on_clearBtn_clicked()
{
    m_scene.clear();
    m_scene.update();
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
