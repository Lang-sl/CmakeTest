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
        m_scene->addItem(m_mixArcLineItems->getStartEndGroup());
        m_scene->addItem(m_mixArcLineItems);
        connect(m_mixArcLineItems, &BMixArcLineItems::groupChanged, this, &QGraphicsViewBasic::bindItemFocus);
        connect(m_mixArcLineItems->getPointList(), &BPointItemList::itemAppended, this, &QGraphicsViewBasic::bindPointFocus);
        connect(m_scene, &QGraphicsSceneBasic::updatePoint, m_mixArcLineItems, &BMixArcLineItems::pushPoint);
    }
    //m_scene->addItem(item);
}

void QGraphicsViewBasic::bindItemFocus(QGraphicsItemGroup* group)
{
    QList<QGraphicsItem*> items = group->childItems();
    for (QGraphicsItem* item : items) {
        QGraphicsItemBasic* customItem = dynamic_cast<QGraphicsItemBasic*>(item);
        if (!customItem->getConnectFocus())
        {
            // 信号未连接，进行绑定
            connect(customItem, &QGraphicsItemBasic::isFocusIn, this, &QGraphicsViewBasic::itemIsFocusIn);
            connect(customItem, &QGraphicsItemBasic::isFocusOut, this, &QGraphicsViewBasic::itemIsFocusOut);
            customItem->setConnectFocus(true);
        }
    }
}

void QGraphicsViewBasic::clear()
{
    m_scene->clear();
    m_scene->addCoordinateSystem();
}

void QGraphicsViewBasic::bindPointFocus(BPointItem* item)
{
    //qDebug() << "bind point";
    connect(item, &BPointItem::isFocusIn, this, &QGraphicsViewBasic::itemIsFocusIn);
    connect(item, &BPointItem::isFocusOut, this, &QGraphicsViewBasic::itemIsFocusOut);
}

void QGraphicsViewBasic::itemIsFocusIn(QAbstractGraphicsShapeItem* i)
{
    //qDebug() << "view Focus In";
    emit ItemFocusIn(i);
}

void QGraphicsViewBasic::itemIsFocusOut(QAbstractGraphicsShapeItem* i)
{
    //qDebug() << "view Focus Out";
    emit ItemFocusOut(i);
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
