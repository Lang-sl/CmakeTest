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
        m_mixArcLineItems = new BMixArcLineItems(QGraphicsItemBasic::ItemType::MixArcLineItems);
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
    m_mixArcLineItems = nullptr;
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

void QGraphicsViewBasic::contextMenuEvent(QContextMenuEvent* event)
{
    QPoint globalPos = event->globalPos();
    QPointF scenePos = mapToScene(event->pos());

    QGraphicsItem* item = scene()->itemAt(scenePos, transform());
    BMixArcLineItems* basicItem = dynamic_cast<BMixArcLineItems*>(item);
    if (basicItem) {
        // 在 Item 范围上显示右键菜单
        QMenu menu(this);

        QAction* itemAction1 = menu.addAction(tr("Create Point"));
        QAction* itemAction2 = menu.addAction(tr("Delete Curve"));
        QAction* itemAction3 = menu.addAction(tr("Fit"));
        QAction* itemAction4 = menu.addAction(tr("Reset"));

        QAction* selectedItem = menu.exec(globalPos);

        // 处理选中的菜单项
        if (selectedItem == itemAction1) {
            // 执行 Item 菜单项1 的操作
        }
        else if (selectedItem == itemAction2) {
            // 执行 Item 菜单项2 的操作
        }
        else if (selectedItem == itemAction3) {
            // 执行 Item 菜单项3 的操作
        }
        else if (selectedItem == itemAction4) {
            // 执行 Item 菜单项4 的操作
        }
    }
    else {
        // 在空白处显示右键菜单
        QMenu menu(this);

        QAction* createPointAction = menu.addAction(tr("Create Point"));
        QAction* fitAction = menu.addAction(tr("Fit"));
        QAction* resetAction = menu.addAction(tr("Reset"));

        QAction* selectedEmptyItem = menu.exec(globalPos);

        // 处理选中的菜单项
        if (selectedEmptyItem == createPointAction) {
            if (!m_mixArcLineItems)
            {
                addItem(QGraphicsItemBasic::ItemType::MixArcLineItems);
            }
            m_mixArcLineItems->pushPoint(mapToScene(event->pos()), BMixArcLineItems::PointType::LineEdgeEnd);
        }
        else if (selectedEmptyItem == fitAction) {
            if (!m_mixArcLineItems)
            {
                addItem(QGraphicsItemBasic::ItemType::MixArcLineItems);
            }
            m_mixArcLineItems->fitByCenter();
            QTimer::singleShot(10000, [=]() {
                this->update();
            });
        }
        else if (selectedEmptyItem == resetAction) {
            // 执行空白菜单项3 的操作
        }
    }
}
