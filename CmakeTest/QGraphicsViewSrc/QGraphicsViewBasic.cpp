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
        event->ignore(); // �����������¼�
        return true;
    }

    return QObject::eventFilter(obj, event);
}
