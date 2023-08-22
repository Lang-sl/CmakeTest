#include "QPointItem.h"
#include "QGraphicsItemBasic.h"

BPointItem::BPointItem(QAbstractGraphicsShapeItem* parent, QPointF p, PointType type)
    : QAbstractGraphicsShapeItem(parent)
    , m_point(p)
    , m_type(type)
{
    this->setPos(m_point);
    this->setFlags(QGraphicsItem::ItemIsSelectable |
        QGraphicsItem::ItemIsMovable |
        QGraphicsItem::ItemIsFocusable);

    switch (type) {
    case PointType::Center:
        this->setCursor(Qt::OpenHandCursor);
        break;
    case PointType::Edge:
        this->setCursor(Qt::PointingHandCursor);
        break;
    default: break;
    }
}

QRectF BPointItem::boundingRect() const
{
    return QRectF(-4, -4, 8, 8);
}

void BPointItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    this->setPos(m_point);

    switch (m_type) {
    case PointType::Center:
        painter->drawEllipse(-4, -4, 8, 8);
        break;
    case PointType::Edge:
        painter->drawRect(QRectF(-4, -4, 8, 8));
        break;
    default: break;
    }
}

void BPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton) {
        qreal dx = event->scenePos().x() - event->lastScenePos().x();
        qreal dy = event->scenePos().y() - event->lastScenePos().y();

        QGraphicsItemBasic* item = static_cast<QGraphicsItemBasic*>(this->parentItem());
        QGraphicsItemBasic::ItemType itemType = item->getType();

        switch (m_type) {
        case PointType::Center: {
            item->moveBy(dx, dy);
            this->scene()->update();
            item->focusInEvent(nullptr);
        } break;
        case PointType::Edge: {
            m_point = this->mapToParent(event->pos());
            this->setPos(m_point);
            this->scene()->update();
            item->focusInEvent(nullptr);
            switch (itemType) {
            case QGraphicsItemBasic::ItemType::Ellipse: {
                BEllipse* ellipse = dynamic_cast<BEllipse*>(item);
                QList<QPointF> newEdges = ellipse->getEdges();
                int index = ellipse->getEdgeIndex(this);
                if (index != -1) {
                    newEdges[index] = m_point;
                    ellipse->setEdges(newEdges, index);
                }
            } break;
            case QGraphicsItemBasic::ItemType::Circle: {
                BCircle* circle = dynamic_cast<BCircle*>(item);
                //circle->setEdges(m_point);
                circle->updateRadius();
            } break;
            case QGraphicsItemBasic::ItemType::Pie: {
                BPie* pie = dynamic_cast<BPie*>(item);

                QLineF line(pie->getCenter(), m_point);
                line.setLength(pie->m_radius);
                QPointF intersectPoint = line.p2();

                m_point.setX(intersectPoint.x());
                m_point.setY(intersectPoint.y());
                pie->updateRadius(QPointF(event->lastScenePos().x(), event->lastScenePos().y()), QPointF(event->scenePos().x(), event->scenePos().y()));
                pie->updateAngle(QPointF(event->lastScenePos().x(), event->lastScenePos().y()), m_point);
            } break;
            case QGraphicsItemBasic::ItemType::Rectangle: {
                BRectangle* rectangle = dynamic_cast<BRectangle*>(item);
                //rectangle->setEdges(m_point);
            } break;
            case QGraphicsItemBasic::ItemType::Square: {
                BSquare* square = dynamic_cast<BSquare*>(item);
                qreal ret = m_point.x() > m_point.y() ? m_point.x() : m_point.y();
                m_point.setX(ret);
                m_point.setY(ret);
                //square->setEdges(m_point);
            } break;
            case QGraphicsItemBasic::ItemType::Line: {
                BLine* line = dynamic_cast<BLine*>(item);
                //line->setEdges(m_point);
            } break;
            case QGraphicsItemBasic::ItemType::Polygon: {
                BPolygon* polygon = dynamic_cast<BPolygon*>(item);
                polygon->updatePolygon(QPointF(event->lastScenePos().x(), event->lastScenePos().y()), QPointF(event->scenePos().x(), event->scenePos().y()));
            } break;
            default: break;
            }
        } break;
        default: break;
        }
    }
}

void BPointItem::focusInEvent(QFocusEvent* event)
{
    QGraphicsItemBasic* item = static_cast<QGraphicsItemBasic*>(this->parentItem());
    item->focusInEvent(nullptr);
}

void BPointItem::focusOutEvent(QFocusEvent* event)
{
    QGraphicsItemBasic* item = static_cast<QGraphicsItemBasic*>(this->parentItem());
    item->focusOutEvent(nullptr);
}

//------------------------------------------------------------------------------

void BPointItemList::setRandColor()
{
    this->setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
}

void BPointItemList::setColor(const QColor color)
{
    for (auto& temp : *this)
    {
        temp->setBrush(QBrush(color));
    }
}

void BPointItemList::setVisible(bool visible)
{
    for (auto& temp : *this)
    {
        temp->setVisible(visible);
    }
}

QList<QPointF> BPointItemList::getQPointFList()
{
    QList<QPointF> list;
    for (auto& temp : *this) {
        list.append(temp->getPoint());
    }
    return list;
}

