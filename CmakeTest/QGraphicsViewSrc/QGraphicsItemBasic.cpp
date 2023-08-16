#include "QGraphicsItemBasic.h"
#include <QVector>
#include <QDebug>
#include <QMenu>
#include <QSpinBox>
#include <QWidgetAction>

QGraphicsItemBasic::QGraphicsItemBasic(QPointF center, QPointF edge, ItemType type)
    : m_center(center), m_edge(edge), m_type(type)
{
    m_pen_noSelected.setColor(QColor(220, 220, 220));
    m_pen_noSelected.setWidth(2);
    m_pen_isSelected.setColor(QColor(255, 215, 0));
    m_pen_isSelected.setWidth(2);

    m_innercolor = QColor(Qt::gray);
    m_innercolor_copy = m_innercolor;

    this->setPen(m_pen_noSelected);
    this->setFlags(QGraphicsItem::ItemIsSelectable |
        QGraphicsItem::ItemIsMovable |
        QGraphicsItem::ItemIsFocusable);
}

void QGraphicsItemBasic::focusInEvent(QFocusEvent* event)
{
    Q_UNUSED(event);
    this->setPen(m_pen_isSelected);
    m_innercolor = m_innercolor.lighter(130);
}

void QGraphicsItemBasic::focusOutEvent(QFocusEvent* event)
{
    Q_UNUSED(event);
    this->setPen(m_pen_noSelected);
    m_innercolor = m_innercolor_copy;
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
    if (event->mimeData()->hasColor())
        setColor(qvariant_cast<QColor>(event->mimeData()->colorData()));
    update();
}

//------------------------------------------------------------------------------

BEllipse::BEllipse(qreal x, qreal y, qreal width, qreal height, ItemType type)
    : QGraphicsItemBasic(QPointF(x, y), QPointF(x + width / 2, y + height / 2), type)
{
    BPointItem* point = new BPointItem(this, m_edge, BPointItem::PointType::Edge);
    point->setParentItem(this);
    m_pointList.append(point);
    m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    setAcceptDrops(true);
}

QRectF BEllipse::boundingRect() const
{
    return QRectF(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2);
}

void BEllipse::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    QRectF ret(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2);
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
    : BEllipse(x, y, radius* sqrt(2), radius* sqrt(2), type)
{
    setAcceptDrops(true);
    updateRadius();
}

void BCircle::updateRadius()
{
    m_radius = sqrt(pow(m_center.x() - m_edge.x(), 2) + pow(m_center.y() - m_edge.y(), 2));
}

QRectF BCircle::boundingRect() const
{
    return QRectF(m_center.x() - m_radius, m_center.y() - m_radius, m_radius * 2, m_radius * 2);
}

void BCircle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    QRectF ret(m_center.x() - m_radius, m_center.y() - m_radius, m_radius * 2, m_radius * 2);
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

BPie::BPie(qreal x, qreal y, qreal radius, qreal angle, ItemType type)
    : BCircle(x, y, radius, type), m_angle(angle)
{
    if ((angle >= 0 && angle < 90) || (angle >= 270 && angle < 360))
    {
        m_edge.setX(m_center.x() + radius * cos(angle / 180 * PI));
        m_edge.setY(m_center.y() + radius * sin(angle / 180 * PI) * (-1));
    }
    else if ((angle >= 90 && angle < 270))
    {
        m_edge.setY(m_center.y() + radius * sin(angle / 180 * PI) * (-1));
        m_edge.setX(m_center.x() + radius * cos(angle / 180 * PI));
    }

    m_pointList.at(0)->setPoint(m_edge);
    m_radius = radius;
}

void BPie::updateAngle()
{
    qreal dx = m_edge.x() - m_center.x();
    qreal dy = m_edge.y() - m_center.y();

    if (dx >= 0 && dy < 0)
    {
        m_angle = atan2((-1) * (dy), dx) * 180 / PI;
    }
    else if (dx < 0 && dy < 0)
    {
        m_angle = atan2((-1) * dy, dx) * 180 / PI;
    }
    else if (dx < 0 && dy >= 0)
    {
        m_angle = 360 + atan2((-1) * dy, dx) * 180 / PI;
    }
    else if (dx >= 0 && dy >= 0)
    {
        m_angle = 360 - atan2(dy, dx) * 180 / PI;
    }
}

void BPie::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    QRectF ret(m_center.x() - m_radius, m_center.y() - m_radius, m_radius * 2, m_radius * 2);
    painter->drawPie(ret, 16 * 0, 16 * (m_angle));
}

//------------------------------------------------------------------------------

BRectangle::BRectangle(qreal x, qreal y, qreal width, qreal height, ItemType type)
    : QGraphicsItemBasic(QPointF(x, y), QPointF(width / 2, height / 2), type)
{
    BPointItem* point = new BPointItem(this, m_edge, BPointItem::PointType::Edge);
    point->setParentItem(this);
    m_pointList.append(point);
    m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    setAcceptDrops(true);
}

QRectF BRectangle::boundingRect() const
{
    return QRectF(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2);
}

void BRectangle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    QRectF ret(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2);
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
    : QGraphicsItemBasic(startPoint, endPoint, type)
{
    BPointItem* point = new BPointItem(this, m_edge, BPointItem::PointType::Edge);
    point->setParentItem(this);
    m_pointList.append(point);
    m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    setAcceptDrops(true);
}

QRectF BLine::boundingRect() const
{
    qreal minX = qMin(m_center.x(), m_edge.x());
    qreal minY = qMin(m_center.y(), m_edge.y());
    qreal width = qAbs(m_center.x() - m_edge.x());
    qreal height = qAbs(m_center.y() - m_edge.y());

    return QRectF(minX, minY, width, height);
}

void BLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(this->pen());
    painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    painter->drawLine(m_center, m_edge);
}

//------------------------------------------------------------------------------

BPoint::BPoint(QPointF position, ItemType type)
    : QGraphicsItemBasic(position, position, type), m_position(position)
{
    m_pointList.append(new BPointItem(this, m_center, BPointItem::PointType::Center));
    m_pointList.setRandColor();
    setAcceptDrops(true);
}

QRectF BPoint::boundingRect() const
{
    qreal size = 10.0; // 设置点的大小

    return QRectF(m_position.x() - size, m_position.y() - size, size * 2, size * 2);
}

void BPoint::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(this->pen());
    painter->setBrush(getDragOver() ? getColor().lighter(130) : getColor());

    qreal size = 3.0; // 设置点的大小
    painter->drawEllipse(m_position, size, size);
}