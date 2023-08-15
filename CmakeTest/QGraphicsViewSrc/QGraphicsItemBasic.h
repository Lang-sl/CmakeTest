#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include <QAbstractGraphicsShapeItem>
#include <QPointF>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QCursor>
#include <QKeyEvent>
#include <QList>
#include <QtWidgets>
//#include "bpointitem.h"

#define PI 3.1415926

// 自定义图元 - 基础类
class QGraphicsItemBasic : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:
    enum class ItemType {
        Circle = 0,         // 圆
        Ellipse,            // 椭圆
        Rectangle,          // 矩形
        Square,             // 正方形
        Polygon,            // 多边形
        Line                // 直线
    };

    QPointF getCenter() { return m_center; }
    void setCenter(QPointF p) { m_center = p; }

    QPointF getEdge() { return m_edge; }
    void setEdge(QPointF p) { m_edge = p; }

    ItemType getType() { return m_type; }

protected:
    QGraphicsItemBasic(QPointF center, QPointF edge, ItemType type);

    virtual void focusInEvent(QFocusEvent* event) override;
    virtual void focusOutEvent(QFocusEvent* event) override;

public:
    QPointF m_center;
    QPointF m_edge;
    ItemType m_type;
    //BPointItemList m_pointList;

    QPen m_pen_isSelected;
    QPen m_pen_noSelected;
};

//------------------------------------------------------------------------------

// 椭圆
class BEllipse : public QGraphicsItemBasic
{
    Q_OBJECT

public:
    BEllipse(qreal x, qreal y, qreal width, qreal height, ItemType type);

protected:
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;

    void setColor(QColor tempColor) { color = tempColor; }
    QColor getColor() { return color; }
    void setDragOver(bool tempDragOver) { dragOver = tempDragOver; }
    bool getDragOver() { return dragOver; }

private:
    QColor color;
    bool dragOver;
};

//------------------------------------------------------------------------------

// 圆
class BCircle : public BEllipse
{
public:
    BCircle(qreal x, qreal y, qreal radius, ItemType type);

    void updateRadius();

protected:
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

public:
    qreal m_radius;
};

//------------------------------------------------------------------------------

// 矩形
class BRectangle : public QGraphicsItemBasic
{
public:
    BRectangle(qreal x, qreal y, qreal width, qreal height, ItemType type);

protected:
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;

private:
    QColor color;
    bool dragOver;
};

//------------------------------------------------------------------------------

// 正方形
class BSquare : public BRectangle
{
public:
    BSquare(qreal x, qreal y, qreal width, ItemType type);

protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

};

//------------------------------------------------------------------------------

// 多边形
class BPolygon : public QGraphicsItemBasic
{
    Q_OBJECT

public:
    BPolygon(ItemType type);

    QPointF getCentroid(QList<QPointF> list);
    void getMaxLength();
    void updatePolygon(QPointF origin, QPointF end);

public slots:
    void pushPoint(QPointF p, QList<QPointF> list, bool isCenter);

protected:
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

public:
    qreal m_radius;
    bool is_create_finished;
};

//------------------------------------------------------------------------------

//class BLine : public QGraphicsItemBasic
//{
//    Q_OBJECT
//
//public:
//    BLine(qreal x, qreal y, qreal width, qreal height, ItemType type);
//
//protected:
//    virtual QRectF boundingRect() const override;
//
//    virtual void paint(QPainter* painter,
//        const QStyleOptionGraphicsItem* option,
//        QWidget* widget) override;
//
//    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
//};