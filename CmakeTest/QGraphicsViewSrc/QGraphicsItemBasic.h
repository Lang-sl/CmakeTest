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

#define SELECTOFFSET 5 
#define SELECTWIDTH 10 // 选中线框的宽度
#define MIXRADIUS 10   // 混合线框默认半径

#define NOSELECTCOLOR QColor(220, 220, 220)
#define ISSELECTCOLOR QColor(255, 160, 0)

#define AUTOLINECOLOR QColor(138, 43, 226)

// 自定义图元 - 基础类
class QGraphicsItemBasic : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:
    friend class BPointItem;

    enum class ItemType {
        Circle = 0,         // 圆
        Ellipse,            // 椭圆
        CoordinateSystem,   // 坐标轴
        Arc,                // 圆弧
        Rectangle,          // 矩形
        Square,             // 正方形
        Line,               // 直线
        Point,              // 点
        Polygon,            // 多边形
        MixArcLine,         // 圆弧直线混合
        MixArcLineItems     // 圆弧直线混合重构版
    };

    QGraphicsItemBasic(ItemType type);

    QPointF getCenter() { return m_center; }
    void setCenter(QPointF p) { m_center = p; }

    QList<QPointF> getEdges() { return m_edges; }
    virtual void setEdges(QList<QPointF> p, int i) { m_edges = p; }

    QPointF getEdge() { return m_edge; }
    void setEdge(QPointF p) { m_edge = p; }

    int getEdgeIndex(BPointItem* pointItem) const;


    QList<QPointF> getPointFList() { return m_pointList.getQPointFList(); }
    BPointItemList* getPointList() { return &m_pointList; }

    ItemType getType() { return m_type; }

    /*QColor getColor() { return m_innercolor; }
    void setColor(QColor c) { m_innercolor = c; m_innercolor_copy = c; }*/

    bool getDragOver() { return m_dragOver; }
    bool getConnectFocus() { return m_connectFocus; }
    void setConnectFocus(bool b) { m_connectFocus = b; }

Q_SIGNALS:
    void isFocusIn(QGraphicsItemBasic* i);
    void isFocusOut(QGraphicsItemBasic* i);

protected:
    QGraphicsItemBasic(QPointF center, QPointF edge, QList<QPointF> edges, ItemType type);

    //QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;

    virtual void focusInEvent(QFocusEvent* event) override;
    virtual void focusOutEvent(QFocusEvent* event) override;

    /*QPointF m_itemPosInScene;
    QList<QPointF> m_itemedgePosInScene;*/

    BPointItemList m_pointList;

    mutable QPointF m_center;
    QPointF m_edge;         //确定边界用
    QList<QPointF> m_edges; //边上可拖拽点集合

    QPointF m_lastPos;
    ItemType m_type;

    QPen m_pen_isSelected;
    QPen m_pen_noSelected;

    /*QColor m_innercolor;
    QColor m_innercolor_copy;*/

    bool m_dragOver;
    bool m_connectFocus;

    friend class QGraphicsViewDemo;
    friend class BMixArcLineItems;
};
//------------------------------------------------------------------------------

// 坐标系

class CoordinateSystem : public QGraphicsItemBasic
{
public:
    CoordinateSystem(ItemType itemType):QGraphicsItemBasic(itemType){}

protected:
    QRectF boundingRect() const override
    {
        return QRectF(-1000, -1000, 2000, 2000); // 坐标系的边界矩形
    }

    QPainterPath shape() const override
    {
        return QPainterPath();
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

    virtual void setEdges(QList<QPointF> p, int i) override;

protected:
    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

private:

    qreal m_semiMajorAxis;
    qreal m_semiMinorAxis;

};

//------------------------------------------------------------------------------

// 圆
class BCircle : public QGraphicsItemBasic
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

class BLine;

// 圆弧
class BArc : public QGraphicsItemBasic
{
public:
    BArc(qreal x, qreal y, qreal radius, qreal startangle, qreal endangle, ItemType type);

    BArc(QPointF origin, QPointF end, ItemType itemType, bool addToGroup = true);

    void updateAngle(QPointF origin, QPointF end);

    void updateRadius(QPointF origin, QPointF end);

    QPainterPath getArc(QPointF origin, QPointF end, qreal& radius) const;

    QPointF getCircleCenter(QPointF origin, QPointF end, qreal radius) const;

    QPainterPath getArc() const;

    QPointF getOrigin() { return m_origin; }
    QPointF getEnd() { return m_end; }

protected:

    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

private:
    mutable qreal m_startAngle;
    mutable qreal m_endAngle;
    mutable qreal m_radius;
    bool m_addToGroup;
    bool m_isAnticlockwise;
    QPointF m_origin;
    QPointF m_end;
    friend class BMixArcLineItems;
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
    BLine(QPointF startPoint, QPointF endPoint, ItemType itemType, bool addToGroup);

    QPainterPath getLine();


protected:
    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

private:
    bool m_addToGroup;
    friend class BMixArcLineItems;
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

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

public:
    qreal m_radius;
    bool is_create_finished;
};

//------------------------------------------------------------------------------

// 混合直线圆弧
//class BMixArcLine : public BPolygon
//{
//    Q_OBJECT
//
//public:
//    BMixArcLine(ItemType type);
//
//    enum class PointType {
//        LineEdgeEnd = 0,         // 直线终点
//        ArcEdgeEnd,              // 圆弧终点
//        Center                   // 质心
//    };
//
//    void updateMixArcLine(QPointF origin, QPointF end);
//
//    QPainterPath getArc(QPointF origin, QPointF end, qreal& radius) const;
//
//    QPointF getCircleCenter(QPointF origin, QPointF end, qreal radius) const;
//
//public slots:
//    void pushPoint(QPointF p, QList<QPointF> list, BMixArcLine::PointType pointType);
//
//    void movePoint(QPointF p, QList<QPointF> list, BMixArcLine::PointType pointType);
//
//protected:
//    
//    virtual QRectF boundingRect() const override;
//
//    virtual QPainterPath shape() const;
//
//    virtual void paint(QPainter* painter,
//        const QStyleOptionGraphicsItem* option,
//        QWidget* widget) override;
//
//public:
//    mutable QList<qreal> m_radiuses;
//    BPointItemList m_pointArcList;
//};
//------------------------------------------------------------------------------
// 
// 混合直线圆弧(重构版)
class BMixArcLineItems : public QGraphicsItemBasic
{
    Q_OBJECT

public:
    BMixArcLineItems(ItemType itemType);

    enum class PointType {
        LineEdgeEnd = 0,         // 直线终点
        ArcEdgeEnd,              // 圆弧终点
        Center                   // 质心
    };

    void updateMixArcLineItems(QPointF origin, QPointF end, BPointItem* point);

    QPointF getCentroid(QList<QPointF> list);

    void getMaxLength();

    void convertLineToArc(BLine* line);

    void convertLineToArc(BLine* line, int i);

    void convertArcToLine(BArc* arc);

    void convertArcToLine(BArc* arc, int i);

    void checkPointList();

    void fitByCenter();

    QGraphicsItemGroup* getItemsGroup() { return m_Items; }

    QGraphicsItemGroup* getStartEndGroup()
    {
        QGraphicsItemGroup* Items = new QGraphicsItemGroup();
        //if (m_startLine)
        Items->addToGroup(m_startLine);
        //if (m_endLine)
        Items->addToGroup(m_endLine);
        return Items;
    }

Q_SIGNALS:
    void groupChanged(QGraphicsItemGroup* group);

public slots:
    void pushPoint(QPointF p, BMixArcLineItems::PointType pointType);

protected:

    int findArcIndex(const QList<QGraphicsItem*>& items);

    int findLineIndex(const QList<QGraphicsItem*>& items);

    //virtual void focusInEvent(QFocusEvent* event) override;
    //virtual void focusOutEvent(QFocusEvent* event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

private:
    bool is_create_finished;
    qreal m_radius;
    QGraphicsItemGroup* m_Items;
    BLine* m_startLine;
    BLine* m_endLine;

    friend class BPointItem;
};