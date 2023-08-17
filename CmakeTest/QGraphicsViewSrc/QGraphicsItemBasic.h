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

#include "QPointItem.h"

#define PI 3.1415926

#define SELECTOFFSET 5 
#define SELECTWIDTH 10 // 选中线框的宽度

// 自定义图元 - 基础类
class QGraphicsItemBasic : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:
    friend class BPointItem;

    enum class ItemType {
        Circle = 0,         // 圆
        Ellipse,            // 椭圆
        Pie,                // 圆弧
        Rectangle,          // 矩形
        Square,             // 正方形
        Line,               // 直线
        Point               // 点
    };

    QGraphicsItemBasic() { ; }

    QPointF getCenter() { return m_center; }
    void setCenter(QPointF p) { m_center = p; }

    QPointF getEdge() { return m_edge; }
    void setEdge(QPointF p) { m_edge = p; }

    QPointF getItemPosInScene() { return m_itemPosInScene; }
    void setItemPosInScene(QPointF p) { m_itemPosInScene = p; }

    QPointF getItemedgePosInScene() { return m_itemedgePosInScene; }
    void setItemedgePosInScene(QPointF p) { m_itemedgePosInScene = p;}

    ItemType getType() { return m_type; }

    /*QColor getColor() { return m_innercolor; }
    void setColor(QColor c) { m_innercolor = c; m_innercolor_copy = c; }*/

    bool getDragOver() { return m_dragOver; }

Q_SIGNALS:
    void isFocusIn(QGraphicsItemBasic* i);
    void isFocusOut();

protected:
    QGraphicsItemBasic(QPointF center, QPointF edge, ItemType type);

    //QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;

    virtual void focusInEvent(QFocusEvent* event) override;
    virtual void focusOutEvent(QFocusEvent* event) override;

    QPointF m_itemPosInScene;
    QPointF m_itemedgePosInScene;

    BPointItemList m_pointList;

    QPointF m_center;
    QPointF m_edge;
    ItemType m_type;

    QPen m_pen_isSelected;
    QPen m_pen_noSelected;

    /*QColor m_innercolor;
    QColor m_innercolor_copy;*/

    bool m_dragOver;

};
//------------------------------------------------------------------------------

// 坐标系

class CoordinateSystem : public QGraphicsItemBasic
{
public:
    CoordinateSystem() { ; }

protected:
    QRectF boundingRect() const override
    {
        return QRectF(-1000, -1000, 2000, 2000); // 坐标系的边界矩形
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override
    {
        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(1);
        painter->setPen(pen);

        // 绘制横轴
        painter->drawLine(-1000, 0, 1000, 0);
        for (int x = -1000; x <= 1000; x += 50)
            painter->drawText(x - 3, 15, QString::number(x));

        // 绘制纵轴
        painter->drawLine(0, -1000, 0, 1000);
        for (int y = -1000; y <= 1000; y += 50)
            painter->drawText(-15, y + 5, QString::number(y));
    }
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

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

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

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

public:
    qreal m_radius;
};

//------------------------------------------------------------------------------

// 饼
class BPie : public BCircle
{
public:
    BPie(qreal x, qreal y, qreal radius, qreal angle, ItemType type);

    void updateAngle();

protected:

    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

public:
    qreal m_startAngle;
    qreal m_endAngle;
};

//------------------------------------------------------------------------------


// 矩形
class BRectangle : public QGraphicsItemBasic
{
public:
    BRectangle(qreal x, qreal y, qreal width, qreal height, ItemType type);

protected:
    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
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

// 线段
class BLine : public QGraphicsItemBasic
{
    Q_OBJECT

public:
    BLine(QPointF startPoint, QPointF endPoint, ItemType type);

protected:
    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;
};
//------------------------------------------------------------------------------

// 点
class BPoint : public QGraphicsItemBasic
{
    Q_OBJECT

public:
    BPoint(QPointF position, ItemType type);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QPointF m_position;
};