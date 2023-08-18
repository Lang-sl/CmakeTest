#include "QGraphicsItemBasic.h"
#include <QVector>
#include <QDebug>
#include <QMenu>
#include <QSpinBox>
#include <QWidgetAction>

QGraphicsItemBasic::QGraphicsItemBasic(QPointF center, QPointF edge, QList<QPointF> edges, ItemType type)
    : m_center(center), m_edge(edge), m_edges(edges), m_type(type)
{
    m_pen_noSelected.setColor(QColor(220, 220, 220));
    m_pen_noSelected.setWidth(2);
    m_pen_isSelected.setColor(QColor(255, 160, 0));
    m_pen_isSelected.setWidth(2);


    m_itemPosInScene = this->pos();
    /*m_innercolor = QColor(Qt::gray);
    m_innercolor_copy = m_innercolor;*/

    this->setPen(m_pen_noSelected);
    this->setFlags(QGraphicsItem::ItemIsSelectable |
        QGraphicsItem::ItemIsMovable |
        QGraphicsItem::ItemIsFocusable);
}

//QVariant QGraphicsItemBasic::itemChange(GraphicsItemChange change, const QVariant& value)
//{
//    if (change == QGraphicsItem::ItemPositionChange) {
//        QPointF newPos = value.toPointF();
//        m_itemPosInScene = this->pos();
//        return newPos;
//    }
//
//    // 对于其他属性的变化，使用默认的处理方式
//    return QGraphicsItem::itemChange(change, value);
//}

int QGraphicsItemBasic::getEdgeIndex(BPointItem* pointItem) const
{
    for (int i = 0; i < m_edges.size(); i++) {
        if (m_pointList[i]->m_point == pointItem->m_point) {
            return i;
        }
    }
    return -1;
}

void QGraphicsItemBasic::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    m_itemPosInScene = this->pos();
    m_itemedgePosInScene += (event->pos()- event->lastScenePos());
    emit isFocusIn(this);
    QAbstractGraphicsShapeItem::mouseMoveEvent(event);
}

void QGraphicsItemBasic::focusInEvent(QFocusEvent* event)
{
    Q_UNUSED(event);
    this->setPen(m_pen_isSelected);
    //m_innercolor = m_innercolor.lighter(130);
    emit isFocusIn(this);
}

void QGraphicsItemBasic::focusOutEvent(QFocusEvent* event)
{
    Q_UNUSED(event);
    this->setPen(m_pen_noSelected);
    //m_innercolor = m_innercolor_copy;
    emit isFocusOut(this);
}

void QGraphicsItemBasic::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
    if (event->mimeData()->hasColor()) {
        event->setAccepted(true);
        m_dragOver = true;
        update();
    }
    else {
        event->setAccepted(false);
    }
}

void QGraphicsItemBasic::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
    Q_UNUSED(event);
    m_dragOver = false;
    update();
}

void QGraphicsItemBasic::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    m_dragOver = false;
    /*if (event->mimeData()->hasColor())
        setColor(qvariant_cast<QColor>(event->mimeData()->colorData()));*/
    update();
}

//------------------------------------------------------------------------------

BEllipse::BEllipse(qreal x, qreal y, qreal width, qreal height, ItemType type)
    : QGraphicsItemBasic(QPointF(x, y), QPointF(x + width / 2, y + height / 2), QList<QPointF>{QPointF(x + width / 2, y), QPointF(x, y + height / 2), QPointF(x, y - height / 2), QPointF(x - width / 2, y)}, type)
{   // 注意m_edges初始化要使得相对的点下标和为3，否则在setEdges()时会出错
    m_semiMajorAxis = width / 2;
    m_semiMinorAxis = height / 2;
    for each (QPointF var in m_edges)
    {
        BPointItem* point = new BPointItem(this, var, BPointItem::PointType::Edge);
        point->setParentItem(this);
        m_pointList.append(point);
        m_itemedgePosInScene.append(point->pos());
    }
    m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    setAcceptDrops(true);
}

void BEllipse::setEdges(QList<QPointF> p , int i)
{
    if (p.size() == 4) {
        m_edges = p;
        // 更新椭圆的两个顶点坐标
        QPointF base = QPointF(m_edges[3 - i].x(), m_edges[3 - i].y()); //注意构造函数初始化列表m_edges初始化的顺序，对应的点下标和为3
        QPointF newpoint = QPointF(m_edges[i].x(), m_edges[i].y());
        m_center = (base + newpoint) / 2;

        
        //qreal edgeX = qAbs(bottomRight.x() - topLeft.x()) / 2;
        //qreal edgeY = qAbs(bottomRight.y() - topLeft.y()) / 2;
        //m_edge = QPointF(edgeX, edgeY);
        // 重新计算椭圆的绘图方式
        update();
    }
}


QRectF BEllipse::boundingRect() const
{
    return QRectF(m_center.x() - abs(m_edge.x()) - SELECTOFFSET, m_center.y() - abs(m_edge.y()) - SELECTOFFSET, (abs(m_edge.x()) + SELECTOFFSET) * 2, (abs(m_edge.y()) + SELECTOFFSET) * 2);
}

QPainterPath BEllipse::shape() const
{
    QPainterPath m_path;
    m_path.addEllipse(QRectF(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2));

    QPainterPathStroker stroker;
    stroker.setWidth(SELECTWIDTH); // 设置线框宽度
    return stroker.createStroke(m_path);
}

void BEllipse::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    //painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    QRectF ret(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2);

    painter->fillPath(shape(), QBrush(QColor(99, 184, 255)));

    painter->drawEllipse(ret);
}

void BEllipse::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    if (!this->isSelected())
        return;

    QMenu* menu = new QMenu();
    menu->setStyleSheet("QMenu { background-color: rgb(220, 220, 220); border: 1px solid rgb(150, 150, 150); border-radius: 5px; }"
        "QMenu::item { padding: 8px 20px; }"
        "QMenu::item:selected { background-color: rgb(100, 180, 255); color: white; }");

    QSpinBox* width_spinBox = new QSpinBox(menu);
    width_spinBox->setStyleSheet("QSpinBox { width: 100px; height: 30px; font-size: 14px; font-weight: normal; border-radius: 5px; background-color: rgb(240, 240, 240); border: 1px solid rgb(150, 150, 150); color: rgb(70, 70, 70); }"
        "QSpinBox::up-button, QSpinBox::down-button { width: 30px; height: 15px; }"
        "QSpinBox::up-button { subcontrol-origin: border; subcontrol-position: top right; }"
        "QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right; }"
        "QSpinBox::up-button:pressed, QSpinBox::down-button:pressed { background-color: rgb(180, 180, 180); }");
    width_spinBox->setRange(0, 1000);
    width_spinBox->setPrefix("w: ");
    width_spinBox->setSuffix(" mm");
    width_spinBox->setSingleStep(1);
    width_spinBox->setValue(2 * abs(m_edge.x()));
    connect(width_spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int v) {
        if (m_edge.x() < 0) {
            m_edge.setX((-1) * v / 2);
        }
        else {
            m_edge.setX(v / 2);
        }
        m_pointList.at(0)->setPoint(m_edge);
        this->hide();
        this->update();
        this->show();
        });

    QSpinBox* height__spinBox = new QSpinBox(menu);
    height__spinBox->setStyleSheet("QSpinBox { width: 100px; height: 30px; font-size: 14px; font-weight: normal; border-radius: 5px; background-color: rgb(240, 240, 240); border: 1px solid rgb(150, 150, 150); color: rgb(70, 70, 70); }"
        "QSpinBox::up-button, QSpinBox::down-button { width: 30px; height: 15px; }"
        "QSpinBox::up-button { subcontrol-origin: border; subcontrol-position: top right; }"
        "QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right; }"
        "QSpinBox::up-button:pressed, QSpinBox::down-button:pressed { background-color: rgb(180, 180, 180); }");
    height__spinBox->setRange(0, 1000);
    height__spinBox->setPrefix("h: ");
    height__spinBox->setSuffix(" mm");
    height__spinBox->setSingleStep(1);
    height__spinBox->setValue(2 * abs(m_edge.y()));
    connect(height__spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int v) {
        if (m_edge.y() < 0) {
            m_edge.setY((-1) * v / 2);
        }
        else {
            m_edge.setY(v / 2);
        }
        m_pointList.at(0)->setPoint(m_edge);
        this->hide();
        this->update();
        this->show();
        });

    QWidgetAction* width_widgetAction = new QWidgetAction(menu);
    width_widgetAction->setDefaultWidget(width_spinBox);
    menu->addAction(width_widgetAction);

    QWidgetAction* height_widgetAction = new QWidgetAction(menu);
    height_widgetAction->setDefaultWidget(height__spinBox);
    menu->addAction(height_widgetAction);

    menu->exec(QCursor::pos());
    delete menu;

    QGraphicsItem::contextMenuEvent(event);
}


//------------------------------------------------------------------------------

BCircle::BCircle(qreal x, qreal y, qreal radius, ItemType type)
    : QGraphicsItemBasic(QPointF(x, y), QPointF(x + radius * sqrt(2) / 2, y + radius * sqrt(2) / 2), QList<QPointF>{QPointF(x + radius, y), QPointF(x - radius, y), QPointF(x, y + radius), QPointF(x, y - radius)}, type)
{
    for each (QPointF var in m_edges)
    {
        BPointItem* point = new BPointItem(this, var, BPointItem::PointType::Edge);
        point->setParentItem(this);
        m_pointList.append(point);
        m_itemedgePosInScene.append(point->pos());
    }
    m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    setAcceptDrops(true);
    updateRadius();
}

void BCircle::updateRadius()
{
    m_radius = sqrt(pow(m_center.x() - m_edge.x(), 2) + pow(m_center.y() - m_edge.y(), 2));
}

QRectF BCircle::boundingRect() const
{
    return QRectF(m_center.x() - m_radius - SELECTOFFSET, m_center.y() - m_radius - SELECTOFFSET, (m_radius + SELECTOFFSET) * 2, (m_radius + SELECTOFFSET) * 2);
}

QPainterPath BCircle::shape() const
{
    QPainterPath m_path;
    m_path.addEllipse(QRectF(m_center.x() - m_radius, m_center.y() - m_radius, m_radius * 2, m_radius * 2));

    QPainterPathStroker stroker;
    stroker.setWidth(SELECTWIDTH); // 设置线框宽度
    return stroker.createStroke(m_path);
}

void BCircle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    //painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    QRectF ret(m_center.x() - m_radius, m_center.y() - m_radius, m_radius * 2, m_radius * 2);

    painter->fillPath(shape(), QBrush(QColor(99, 184, 255)));

    painter->drawEllipse(ret);
}

void BCircle::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    if (!this->isSelected())
        return;

    QMenu* menu = new QMenu();
    menu->setStyleSheet("QMenu { background-color: rgb(220, 220, 220); border: 1px solid rgb(150, 150, 150); border-radius: 5px; }"
        "QMenu::item { padding: 8px 20px; }"
        "QMenu::item:selected { background-color: rgb(100, 180, 255); color: white; }");

    QSpinBox* radius_spinBox = new QSpinBox(menu);
    radius_spinBox->setStyleSheet("QSpinBox { width: 100px; height: 30px; font-size: 14px; font-weight: normal; border-radius: 5px; background-color: rgb(240, 240, 240); border: 1px solid rgb(150, 150, 150); color: rgb(70, 70, 70); }"
        "QSpinBox::up-button, QSpinBox::down-button { width: 30px; height: 15px; }"
        "QSpinBox::up-button { subcontrol-origin: border; subcontrol-position: top right; }"
        "QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right; }"
        "QSpinBox::up-button:pressed, QSpinBox::down-button:pressed { background-color: rgb(180, 180, 180); }");
    radius_spinBox->setRange(0, 1000);
    radius_spinBox->setPrefix("r: ");
    radius_spinBox->setSuffix(" mm");
    radius_spinBox->setSingleStep(1);
    radius_spinBox->setValue(m_radius);
    connect(radius_spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int v) {
        m_radius = v;

        if (m_edge.x() < 0) {
            m_edge.setX(m_center.x() - m_radius * sqrt(2) / 2);
        }
        else {
            m_edge.setX(m_center.x() + m_radius * sqrt(2) / 2);
        }

        if (m_edge.y() < 0) {
            m_edge.setY(m_center.y() - m_radius * sqrt(2) / 2);
        }
        else {
            m_edge.setY(m_center.y() + m_radius * sqrt(2) / 2);
        }

        m_pointList.at(0)->setPoint(m_edge);
        this->hide();
        this->update();
        this->show();
        });

    QWidgetAction* radius_widgetAction = new QWidgetAction(menu);
    radius_widgetAction->setDefaultWidget(radius_spinBox);
    menu->addAction(radius_widgetAction);

    menu->exec(QCursor::pos());
    delete menu;

    QGraphicsItem::contextMenuEvent(event);
}

//------------------------------------------------------------------------------

BPie::BPie(qreal x, qreal y, qreal radius, qreal startangle, qreal endangle, ItemType type)
    : QGraphicsItemBasic(QPointF(x, y), QPointF(x + radius * sqrt(2) / 2, y + radius * sqrt(2) / 2), QList<QPointF>{}, type), m_startAngle(startangle), m_endAngle(endangle)
{

    QPointF p = QPointF((m_center.x() + radius * cos(startangle / 180 * M_PI)), (m_center.y() + radius * sin(startangle / 180 * M_PI) * (-1)));
    BPointItem* point = new BPointItem(this, p, BPointItem::PointType::Edge);
    point->setParentItem(this);
    m_pointList.append(point);
    m_itemedgePosInScene.append(point->pos());

    p = QPointF((m_center.x() + radius * cos(m_endAngle / 180 * M_PI)), (m_center.y() + radius * sin(m_endAngle / 180 * M_PI) * (-1)));
    point = new BPointItem(this, p, BPointItem::PointType::Edge);
    point->setParentItem(this);
    m_pointList.append(point);
    m_itemedgePosInScene.append(point->pos()); 
    
    m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    m_radius = radius;
}

void BPie::updateAngle()
{
    qreal dx = m_edge.x() - m_center.x();
    qreal dy = m_edge.y() - m_center.y();

    if (dx >= 0 && dy < 0)
    {
        m_endAngle = atan2((-1) * (dy), dx) * 180 / M_PI;
    }
    else if (dx < 0 && dy < 0)
    {
        m_endAngle = atan2((-1) * dy, dx) * 180 / M_PI;
    }
    else if (dx < 0 && dy >= 0)
    {
        m_endAngle = 360 + atan2((-1) * dy, dx) * 180 / M_PI;
    }
    else if (dx >= 0 && dy >= 0)
    {
        m_endAngle = 360 - atan2(dy, dx) * 180 / M_PI;
    }
}

QRectF BPie::boundingRect() const
{
    return QRectF(m_center.x() - m_radius - SELECTOFFSET, m_center.y() - m_radius - SELECTOFFSET, (m_radius + SELECTOFFSET) * 2, (m_radius + SELECTOFFSET) * 2);
}

QPainterPath BPie::shape() const
{
    QPainterPath m_path;
    m_path.moveTo(m_center);
    m_path.arcTo(QRectF(m_center.x() - m_radius, m_center.y() - m_radius, m_radius * 2, m_radius * 2), m_startAngle, m_endAngle);
    m_path.lineTo(m_center);

    QPainterPathStroker stroker;
    stroker.setWidth(SELECTWIDTH); // 设置线框宽度
    return stroker.createStroke(m_path);
}

void BPie::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    //painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    QRectF ret(m_center.x() - m_radius, m_center.y() - m_radius, m_radius * 2, m_radius * 2);

    painter->fillPath(shape(), QBrush(QColor(99, 184, 255)));
    
    painter->drawPie(ret, 16 * (m_startAngle), 16 * (m_endAngle));
}

//------------------------------------------------------------------------------

BRectangle::BRectangle(qreal x, qreal y, qreal width, qreal height, ItemType type)
    : QGraphicsItemBasic(QPointF(x, y), QPointF(width / 2, height / 2), QList<QPointF>{QPointF(width / 2, height / 2), QPointF(width / 2, - height / 2), QPointF(- width / 2, height / 2), QPointF(- width / 2, - height / 2)}, type)
{
    for each (QPointF var in m_edges)
    {
        BPointItem* point = new BPointItem(this, var, BPointItem::PointType::Edge);
        point->setParentItem(this);
        m_pointList.append(point);
        m_itemedgePosInScene.append(point->pos());
    }
    m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    setAcceptDrops(true);
}

QRectF BRectangle::boundingRect() const
{
    return QRectF(m_center.x() - abs(m_edge.x()) - SELECTOFFSET, m_center.y() - abs(m_edge.y()) - SELECTOFFSET, (abs(m_edge.x()) + SELECTOFFSET) * 2, (abs(m_edge.y()) + SELECTOFFSET) * 2);
}

QPainterPath BRectangle::shape() const
{
    QPainterPath m_path;
    m_path.moveTo(m_center);
    m_path.addRect(QRectF(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2));

    QPainterPathStroker stroker;
    stroker.setWidth(SELECTWIDTH); // 设置线框宽度
    return stroker.createStroke(m_path);
}

void BRectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    //painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    QRectF ret(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2);
    painter->fillPath(shape(), QBrush(QColor(99, 184, 255)));
    painter->drawRect(ret);
}

void BRectangle::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    if (!this->isSelected())
        return;

    QMenu* menu = new QMenu();
    menu->setStyleSheet("QMenu { background-color: rgb(220, 220, 220); border: 1px solid rgb(150, 150, 150); border-radius: 5px; }"
        "QMenu::item { padding: 8px 20px; }"
        "QMenu::item:selected { background-color: rgb(100, 180, 255); color: white; }");

    QSpinBox* width_spinBox = new QSpinBox(menu);
    width_spinBox->setStyleSheet("QSpinBox { width: 100px; height: 30px; font-size: 14px; font-weight: normal; border-radius: 5px; background-color: rgb(240, 240, 240); border: 1px solid rgb(150, 150, 150); color: rgb(70, 70, 70); }"
        "QSpinBox::up-button, QSpinBox::down-button { width: 30px; height: 15px; }"
        "QSpinBox::up-button { subcontrol-origin: border; subcontrol-position: top right; }"
        "QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right; }"
        "QSpinBox::up-button:pressed, QSpinBox::down-button:pressed { background-color: rgb(180, 180, 180); }");
    width_spinBox->setRange(0, 1000);
    width_spinBox->setPrefix("w: ");
    width_spinBox->setSuffix(" mm");
    width_spinBox->setSingleStep(1);
    width_spinBox->setValue(2 * abs(m_edge.x()));
    connect(width_spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int v) {
        if (m_edge.x() < 0) {
            m_edge.setX((-1) * v / 2);
        }
        else {
            m_edge.setX(v / 2);
        }
        m_pointList.at(0)->setPoint(m_edge);
        this->hide();
        this->update();
        this->show();
        });

    QSpinBox* height__spinBox = new QSpinBox(menu);
    height__spinBox->setStyleSheet("QSpinBox { width: 100px; height: 30px; font-size: 14px; font-weight: normal; border-radius: 5px; background-color: rgb(240, 240, 240); border: 1px solid rgb(150, 150, 150); color: rgb(70, 70, 70); }"
        "QSpinBox::up-button, QSpinBox::down-button { width: 30px; height: 15px; }"
        "QSpinBox::up-button { subcontrol-origin: border; subcontrol-position: top right; }"
        "QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right; }"
        "QSpinBox::up-button:pressed, QSpinBox::down-button:pressed { background-color: rgb(180, 180, 180); }");
    height__spinBox->setRange(0, 1000);
    height__spinBox->setPrefix("h: ");
    height__spinBox->setSuffix(" mm");
    height__spinBox->setSingleStep(1);
    height__spinBox->setValue(2 * abs(m_edge.y()));
    connect(height__spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int v) {
        if (m_edge.y() < 0) {
            m_edge.setY((-1) * v / 2);
        }
        else {
            m_edge.setY(v / 2);
        }
        m_pointList.at(0)->setPoint(m_edge);
        this->hide();
        this->update();
        this->show();
        });

    QWidgetAction* width_widgetAction = new QWidgetAction(menu);
    width_widgetAction->setDefaultWidget(width_spinBox);
    menu->addAction(width_widgetAction);

    QWidgetAction* height_widgetAction = new QWidgetAction(menu);
    height_widgetAction->setDefaultWidget(height__spinBox);
    menu->addAction(height_widgetAction);

    menu->exec(QCursor::pos());
    delete menu;

    QGraphicsItem::contextMenuEvent(event);
}

//------------------------------------------------------------------------------

BSquare::BSquare(qreal x, qreal y, qreal width, ItemType type)
    : BRectangle(x, y, width, width, type) {}

void BSquare::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    if (!this->isSelected())
        return;

    QMenu* menu = new QMenu();
    menu->setStyleSheet("QMenu { background-color: rgb(220, 220, 220); border: 1px solid rgb(150, 150, 150); border-radius: 5px; }"
        "QMenu::item { padding: 8px 20px; }"
        "QMenu::item:selected { background-color: rgb(100, 180, 255); color: white; }");

    QSpinBox* distance_spinBox = new QSpinBox(menu);
    distance_spinBox->setStyleSheet("QSpinBox { width: 100px; height: 30px; font-size: 14px; font-weight: normal; border-radius: 5px; background-color: rgb(240, 240, 240); border: 1px solid rgb(150, 150, 150); color: rgb(70, 70, 70); }"
        "QSpinBox::up-button, QSpinBox::down-button { width: 30px; height: 15px; }"
        "QSpinBox::up-button { subcontrol-origin: border; subcontrol-position: top right; }"
        "QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right; }"
        "QSpinBox::up-button:pressed, QSpinBox::down-button:pressed { background-color: rgb(180, 180, 180); }");
    distance_spinBox->setRange(0, 1000);
    distance_spinBox->setPrefix("d: ");
    distance_spinBox->setSuffix(" mm");
    distance_spinBox->setSingleStep(1);
    distance_spinBox->setValue(2 * abs(m_edge.x()));
    connect(distance_spinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int v) {
        if (m_edge.x() < 0) {
            m_edge.setX((-1) * v / 2);
            m_edge.setY((-1) * v / 2);
        }
        else {
            m_edge.setX(v / 2);
            m_edge.setY(v / 2);
        }
        m_pointList.at(0)->setPoint(m_edge);
        this->hide();
        this->update();
        this->show();
        });

    QWidgetAction* distance_widgetAction = new QWidgetAction(menu);
    distance_widgetAction->setDefaultWidget(distance_spinBox);
    menu->addAction(distance_widgetAction);

    menu->exec(QCursor::pos());
    delete menu;

    QGraphicsItem::contextMenuEvent(event);
}

//------------------------------------------------------------------------------

BLine::BLine(QPointF startPoint, QPointF endPoint, ItemType type)
    : QGraphicsItemBasic(startPoint, endPoint, QList<QPointF>{startPoint, endPoint}, type)
{
    for each (QPointF var in m_edges)
    {
        BPointItem* point = new BPointItem(this, var, BPointItem::PointType::Edge);
        point->setParentItem(this);
        m_pointList.append(point);
        m_itemedgePosInScene.append(point->pos());
    }
    //m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    setAcceptDrops(true);
}

QRectF BLine::boundingRect() const
{
    qreal minX = qMin(m_center.x(), m_edge.x());
    qreal minY = qMin(m_center.y(), m_edge.y());
    qreal width = qAbs(m_center.x() - m_edge.x());
    qreal height = qAbs(m_center.y() - m_edge.y());

    return QRectF(minX - SELECTOFFSET, minY - SELECTOFFSET, width + SELECTOFFSET * 2, height + SELECTOFFSET * 2);
}

QPainterPath BLine::shape() const
{
    QPainterPath m_path;
    m_path.moveTo(m_center);
    m_path.lineTo(m_edge);

    QPainterPathStroker stroker;
    stroker.setWidth(SELECTWIDTH); // 设置线框宽度
    return stroker.createStroke(m_path);
}

void BLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(this->pen());
    //painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    painter->fillPath(shape(), QBrush(QColor(99, 184, 255)));
    painter->drawLine(m_center, m_edge);
}

//------------------------------------------------------------------------------

BPoint::BPoint(QPointF position, ItemType type)
    : QGraphicsItemBasic(position, position, QList<QPointF>{position}, type), m_position(position)
{
    m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    setAcceptDrops(true);
}

QRectF BPoint::boundingRect() const
{
    qreal size = 10.0; // 设置点的大小

    return QRectF(m_position.x() - size - SELECTOFFSET, m_position.y() - size - SELECTOFFSET, (size + SELECTOFFSET) * 2, (size + SELECTOFFSET) * 2);
}

void BPoint::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(this->pen());
    //painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    qreal size = 3.0; // 设置点的大小
    painter->drawEllipse(m_position, size, size);
}