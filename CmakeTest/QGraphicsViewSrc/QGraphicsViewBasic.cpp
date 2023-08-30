#include "QGraphicsViewBasic.h"

QGraphicsViewBasic::QGraphicsViewBasic(QWidget* parent) : QGraphicsView(parent)
{
    // ����ˮƽ/��ֱ������
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // ���ó�����Χ
    setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);

    // �����
    setRenderHints(QPainter::Antialiasing);

    // �����������¼�
    setMouseTracking(true); // �������׷�٣�ȷ�����Բ����������¼�

    // ��GraphicsView���¼��������к����������¼�
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
            // �ź�δ���ӣ����а�
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
        event->ignore(); // �����������¼�
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
        // �� Item ��Χ����ʾ�Ҽ��˵�
        QMenu menu(this);

        QAction* itemAction1 = menu.addAction(tr("Create Point"));
        QAction* itemAction2 = menu.addAction(tr("Delete Curve"));
        QAction* itemAction3 = menu.addAction(tr("Fit"));
        QAction* itemAction4 = menu.addAction(tr("Reset"));

        QAction* selectedItem = menu.exec(globalPos);

        // ����ѡ�еĲ˵���
        if (selectedItem == itemAction1) {
            // ִ�� Item �˵���1 �Ĳ���
        }
        else if (selectedItem == itemAction2) {
            // ִ�� Item �˵���2 �Ĳ���
        }
        else if (selectedItem == itemAction3) {
            // ִ�� Item �˵���3 �Ĳ���
        }
        else if (selectedItem == itemAction4) {
            // ִ�� Item �˵���4 �Ĳ���
        }
    }
    else {
        // �ڿհ״���ʾ�Ҽ��˵�
        QMenu menu(this);

        QAction* createPointAction = menu.addAction(tr("Create Point"));
        QAction* fitAction = menu.addAction(tr("Fit"));
        QAction* resetAction = menu.addAction(tr("Reset"));

        QAction* selectedEmptyItem = menu.exec(globalPos);

        // ����ѡ�еĲ˵���
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
            // ִ�пհײ˵���3 �Ĳ���
        }
    }
}
