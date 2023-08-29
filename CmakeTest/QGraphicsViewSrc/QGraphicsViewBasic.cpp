#include "QGraphicsViewBasic.h"

QGraphicsViewBasic::QGraphicsViewBasic(QWidget* parent) : QGraphicsView(parent)
{
    // 隐藏水平/竖直滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 设置场景范围
    setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);

    // 反锯齿
    setRenderHints(QPainter::Antialiasing);

    // 忽略鼠标滚轮事件
    setMouseTracking(true); // 开启鼠标追踪，确保可以捕获鼠标滚轮事件

    // 在GraphicsView的事件过滤器中忽略鼠标滚轮事件
    installEventFilter(this);

    m_scene = new QGraphicsSceneBasic(this);
    m_scene->setBackgroundBrush(QBrush("#F8F8FF"));
    this->setScene(m_scene);
}

void QGraphicsViewBasic::addItem(QGraphicsItemBasic::ItemType itemType)
{
    if (itemType == QGraphicsItemBasic::ItemType::MixArcLineItems)
    {
        BMixArcLineItems* m_mixArcLineItems = new BMixArcLineItems(QGraphicsItemBasic::ItemType::MixArcLineItems);
        m_scene->startCreateBMixArcLineItems();
        m_scene->addItem(m_mixArcLineItems->getItemsGroup());
        m_scene->addItem(m_mixArcLineItems);
        connect(m_scene, SIGNAL(updatePoint(QPointF, QList<QPointF>, BMixArcLineItems::PointType)), m_mixArcLineItems, SLOT(pushPoint(QPointF, QList<QPointF>, BMixArcLineItems::PointType)));
    }
    //m_scene->addItem(item);
}

void QGraphicsViewBasic::clear()
{
    m_scene->clear();
    m_scene->addCoordinateSystem();
}

void QGraphicsViewBasic::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
}

bool QGraphicsViewBasic::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Wheel)
    {
        event->ignore(); // 忽略鼠标滚轮事件
        return true;
    }

    return QObject::eventFilter(obj, event);
}
