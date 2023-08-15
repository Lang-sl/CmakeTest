#include "QGraphicsItemBasic.h"
#include <QVector>
#include <QDebug>
#include <QMenu>
#include <QSpinBox>
#include <QWidgetAction>

QGraphicsItemBasic::QGraphicsItemBasic(QPointF center, QPointF edge, ItemType type)
    : m_center(center), m_edge(edge), m_type(type)
{
    m_pen_noSelected.setColor(QColor(248, 248, 255));
    m_pen_noSelected.setWidth(2);
    m_pen_isSelected.setColor(QColor(255, 0, 255));
    m_pen_isSelected.setWidth(2);

    this->setPen(m_pen_noSelected);
    this->setFlags(QGraphicsItem::ItemIsSelectable |
        QGraphicsItem::ItemIsMovable |
        QGraphicsItem::ItemIsFocusable);
}

void QGraphicsItemBasic::focusInEvent(QFocusEvent* event)
{
    Q_UNUSED(event);
    this->setPen(m_pen_isSelected);
}

void QGraphicsItemBasic::focusOutEvent(QFocusEvent* event)
{
    Q_UNUSED(event);
    this->setPen(m_pen_noSelected);
}

//------------------------------------------------------------------------------

BEllipse::BEllipse(qreal x, qreal y, qreal width, qreal height, ItemType type)
    : QGraphicsItemBasic(QPointF(x, y), QPointF(x + width / 2, y + height / 2), type)
{
    /*BPointItem* point = new BPointItem(this, m_edge, BPointItem::Edge);
    point->setParentItem(this);
    m_pointList.append(point);
    m_pointList.append(new BPointItem(this, m_center, BPointItem::Center));
    m_pointList.setRandColor();*/

    setAcceptDrops(true);
    color = Qt::gray;
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
    painter->setBrush(dragOver ? color.lighter(130) : color);

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
        //m_pointList.at(0)->setPoint(m_edge);
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
        //m_pointList.at(0)->setPoint(m_edge);
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

void BEllipse::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
    if (event->mimeData()->hasColor()) {
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else {
        event->setAccepted(false);
    }
}

void BEllipse::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
    Q_UNUSED(event);
    dragOver = false;
    update();
}

void BEllipse::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    dragOver = false;
    if (event->mimeData()->hasColor())
        color = qvariant_cast<QColor>(event->mimeData()->colorData());
    update();
}

//------------------------------------------------------------------------------

BCircle::BCircle(qreal x, qreal y, qreal radius, ItemType type)
    : BEllipse(x, y, radius* sqrt(2), radius* sqrt(2), type)
{
    setAcceptDrops(true);
    setColor(Qt::gray);
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

        //m_pointList.at(0)->setPoint(m_edge);
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

BRectangle::BRectangle(qreal x, qreal y, qreal width, qreal height, ItemType type)
    : QGraphicsItemBasic(QPointF(x, y), QPointF(width / 2, height / 2), type)
{
    /*BPointItem* point = new BPointItem(this, m_edge, BPointItem::Edge);
    point->setParentItem(this);
    m_pointList.append(point);
    m_pointList.append(new BPointItem(this, m_center, BPointItem::Center));
    m_pointList.setRandColor();*/
    setAcceptDrops(true);
    color = Qt::gray;
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
    painter->setBrush(dragOver ? color.lighter(130) : color);

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
        //m_pointList.at(0)->setPoint(m_edge);
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
        //m_pointList.at(0)->setPoint(m_edge);
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

void BRectangle::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
    if (event->mimeData()->hasColor()) {
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else {
        event->setAccepted(false);
    }
}

void BRectangle::dragLeaveEvent(QGraphicsSceneDragDropEvent* event)
{
    Q_UNUSED(event);
    dragOver = false;
    update();
}

void BRectangle::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    dragOver = false;
    if (event->mimeData()->hasColor())
        color = qvariant_cast<QColor>(event->mimeData()->colorData());
    update();
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
        //m_pointList.at(0)->setPoint(m_edge);
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

BPolygon::BPolygon(ItemType type)
    : QGraphicsItemBasic(QPointF(0, 0), QPointF(0, 0), type)
{
    is_create_finished = false;
}

void BPolygon::pushPoint(QPointF p, QList<QPointF> list, bool isCenter)
{
    if (!is_create_finished) {
        m_center = getCentroid(list);
        getMaxLength();

        if (isCenter) {
            //m_pointList.append(new BPointItem(this, m_center, BPointItem::Center));
            //m_pointList.setRandColor();
            is_create_finished = true;
        }
        else {
            /*BPointItem* point = new BPointItem(this, p, BPointItem::Edge);
            point->setParentItem(this);
            m_pointList.append(point);
            m_pointList.setColor(QColor(0, 255, 0));*/
        }

        this->update();
    }
}

QPointF BPolygon::getCentroid(QList<QPointF> list)
{
    qreal x = 0;
    qreal y = 0;
    for (auto& temp : list)
    {
        x += temp.x();
        y += temp.y();
    }
    x = x / list.size();
    y = y / list.size();
    return QPointF(x, y);
}

void BPolygon::getMaxLength()
{
    /*QVector<qreal> vec;
    for (auto& temp : m_pointList)
    {
        qreal dis = sqrt(pow(m_center.x() - temp->x(), 2) + pow(m_center.y() - temp->y(), 2));
        vec.append(dis);
    }

    qreal ret = 0;
    for (auto& temp : vec)
    {
        if (temp > ret) {
            ret = temp;
        }
    }
    m_radius = ret;*/
}

void BPolygon::updatePolygon(QPointF origin, QPointF end)
{
    /*QList<QPointF> list;

    for (auto& temp : m_pointList) {
        if (temp->getPoint() == origin) {
            temp->setPoint(end);
        }
        list.append(temp->getPoint());
    }

    m_center = getCentroid(list);
    m_pointList.at(m_pointList.size() - 1)->setPoint(m_center);

    getMaxLength();*/
}

QRectF BPolygon::boundingRect() const
{
    return QRectF(m_center.x() - m_radius, m_center.y() - m_radius, m_radius * 2, m_radius * 2);
}

void BPolygon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    /*Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());

    if (is_create_finished) {
        for (int i = 1; i < m_pointList.size() - 1; i++)
        {
            painter->drawLine(m_pointList.at(i - 1)->getPoint(), m_pointList.at(i)->getPoint());
        }

        painter->drawLine(m_pointList.at(m_pointList.size() - 2)->getPoint(), m_pointList.at(0)->getPoint());
    }
    else {
        for (int i = 1; i < m_pointList.size(); i++)
        {
            painter->drawLine(m_pointList.at(i - 1)->getPoint(), m_pointList.at(i)->getPoint());
        }
    }*/
}

//------------------------------------------------------------------------------

//BLine::BLine(qreal x, qreal y, qreal width, qreal height, ItemType type)
//    : QGraphicsItemBasic(QPointF(x, y), QPointF(x + width / 2, y + height / 2), type)
//{
//    
//}
//
//QRectF BLine::boundingRect() const
//{
//    return QRectF(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2);
//}
//
//void BLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
//{
//    Q_UNUSED(option);
//    Q_UNUSED(widget);
//    painter->setPen(this->pen());
//    painter->setBrush(this->brush());
//
//    QRectF ret(m_center.x() - abs(m_edge.x()), m_center.y() - abs(m_edge.y()), abs(m_edge.x()) * 2, abs(m_edge.y()) * 2);
//    painter->drawEllipse(ret);
//}
//
//void BLine::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
//{
//}