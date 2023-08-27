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
#define SELECTWIDTH 10 // ѡ���߿�Ŀ��
#define MIXRADIUS 10   // ����߿�Ĭ�ϰ뾶

// �Զ���ͼԪ - ������
class QGraphicsItemBasic : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:
    friend class BPointItem;

    enum class ItemType {
        Circle = 0,         // Բ
        Ellipse,            // ��Բ
        CoordinateSystem,   // ������
        Pie,                // Բ��
        Rectangle,          // ����
        Square,             // ������
        Line,               // ֱ��
        Point,              // ��
        Polygon,            // �����
        MixArcLine,         // Բ��ֱ�߻��
        MixArcLineItems     // Բ��ֱ�߻���ع���
    };

    QGraphicsItemBasic(ItemType type);

    QPointF getCenter() { return m_center; }
    void setCenter(QPointF p) { m_center = p; }

    QList<QPointF> getEdges() { return m_edges; }
    virtual void setEdges(QList<QPointF> p, int i) { m_edges = p; }
    int getEdgeIndex(BPointItem* pointItem) const;


    QList<QPointF> getPointList() { return m_pointList.getQPointFList(); }

    ItemType getType() { return m_type; }

    /*QColor getColor() { return m_innercolor; }
    void setColor(QColor c) { m_innercolor = c; m_innercolor_copy = c; }*/

    bool getDragOver() { return m_dragOver; }

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

    QPointF m_center;
    QPointF m_edge;         //ȷ���߽���
    QList<QPointF> m_edges; //���Ͽ���ק�㼯��

    QPointF m_lastPos;
    ItemType m_type;

    QPen m_pen_isSelected;
    QPen m_pen_noSelected;

    /*QColor m_innercolor;
    QColor m_innercolor_copy;*/

    bool m_dragOver;

    friend class QGraphicsViewDemo;
    friend class BMixArcLineItems;
};
//------------------------------------------------------------------------------

// ����ϵ

class CoordinateSystem : public QGraphicsItemBasic
{
public:
    CoordinateSystem(ItemType itemType):QGraphicsItemBasic(itemType){}

protected:
    QRectF boundingRect() const override
    {
        return QRectF(-1000, -1000, 2000, 2000); // ����ϵ�ı߽����
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override
    {
        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(1);
        painter->setPen(pen);

        // ���ƺ���
        painter->drawLine(-1000, 0, 1000, 0);
        for (int x = -1000; x <= 1000; x += 50)
            painter->drawText(x - 3, 15, QString::number(x));

        // ��������
        painter->drawLine(0, -1000, 0, 1000);
        for (int y = -1000; y <= 1000; y += 50)
            painter->drawText(-15, y + 5, QString::number(y));
    }
};

//------------------------------------------------------------------------------

// ��Բ
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

// Բ
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

// ��
class BPie : public QGraphicsItemBasic
{
public:
    BPie(qreal x, qreal y, qreal radius, qreal startangle, qreal endangle, ItemType type);

    BPie(QPointF origin, QPointF end, qreal radius, ItemType itemType, bool addToGroup = true);

    void updateAngle(QPointF origin, QPointF end);

    void updateRadius(QPointF origin, QPointF end);

    QPainterPath getArc(QPointF origin, QPointF end, qreal& radius) const;

    QPointF getCircleCenter(QPointF origin, QPointF end, qreal radius) const;

    QPainterPath getArc() const;

protected:

    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

public:
    mutable qreal m_startAngle;
    mutable qreal m_endAngle;
    mutable qreal m_radius;
    bool m_addToGroup;
    QPointF m_origin;
    QPointF m_end;
    friend class BMixArcLineItems;
};

//------------------------------------------------------------------------------


// ����
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

// ������
class BSquare : public BRectangle
{
public:
    BSquare(qreal x, qreal y, qreal width, ItemType type);

protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

};

//------------------------------------------------------------------------------

// �߶�
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

// ��
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

// �����
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

// ���ֱ��Բ��
class BMixArcLine : public BPolygon
{
    Q_OBJECT

public:
    BMixArcLine(ItemType type);

    enum class PointType {
        LineEdgeEnd = 0,         // ֱ���յ�
        ArcEdgeEnd,              // Բ���յ�
        Center                   // ����
    };

    void updateMixArcLine(QPointF origin, QPointF end);

    QPainterPath getArc(QPointF origin, QPointF end, qreal& radius) const;

    QPointF getCircleCenter(QPointF origin, QPointF end, qreal radius) const;

public slots:
    void pushPoint(QPointF p, QList<QPointF> list, BMixArcLine::PointType pointType);

    void movePoint(QPointF p, QList<QPointF> list, BMixArcLine::PointType pointType);

protected:
    
    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

public:
    mutable QList<qreal> m_radiuses;
    BPointItemList m_pointArcList;
};
//------------------------------------------------------------------------------
// 
// ���ֱ��Բ��(�ع���)
class BMixArcLineItems : public QGraphicsItemBasic
{
    Q_OBJECT

public:
    BMixArcLineItems(ItemType itemType);

    enum class PointType {
        LineEdgeEnd = 0,         // ֱ���յ�
        ArcEdgeEnd,              // Բ���յ�
        Center                   // ����
    };

    void updateMixArcLine(QPointF origin, QPointF end);

    QPointF getCentroid(QList<QPointF> list);

    void getMaxLength();

Q_SIGNALS:


public slots:
    void pushPoint(QPointF p, QList<QPointF> list, BMixArcLineItems::PointType pointType);

protected:

    //virtual void focusInEvent(QFocusEvent* event) override;
    //virtual void focusOutEvent(QFocusEvent* event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    virtual QRectF boundingRect() const override;

    virtual QPainterPath shape() const;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    void paintItemRecursive(QGraphicsItemBasic* item, QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

public:
    bool is_create_finished;
    qreal m_radius;
    QGraphicsItemGroup* m_Items;
    QGraphicsItemGroup* m_mirrorItems;
    BPointItemList m_mirrorPointList;
};