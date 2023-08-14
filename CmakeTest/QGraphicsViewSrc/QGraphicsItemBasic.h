#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include <QAbstractGraphicsShapeItem>
#include <QPointF>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QCursor>
#include <QKeyEvent>
#include <QList>
//#include "bpointitem.h"

#define PI 3.1415926

// �Զ���ͼԪ - ������
class QGraphicsItemBasic : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:
    enum class ItemType {
        Circle = 0,         // Բ
        Ellipse,            // ��Բ
        Concentric_Circle,  // ͬ��Բ
        Pie,                // ��
        Chord,              // ����
        Rectangle,          // ����
        Square,             // ������
        Polygon,            // �����
        Round_End_Rectangle,// Բ�˾���
        Rounded_Rectangle   // Բ�Ǿ���
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

// ��Բ
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
};

//------------------------------------------------------------------------------

// Բ
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

// ͬ��Բ
class BConcentricCircle : public BCircle
{
public:
    BConcentricCircle(qreal x, qreal y, qreal radius1, qreal radius2, ItemType type);

    void updateOtherRadius();
    void setAnotherEdge(QPointF p);

protected:
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

public:
    QPointF m_another_edge;
    qreal m_another_radius;
};

//------------------------------------------------------------------------------

// ��
class BPie : public BCircle
{
public:
    BPie(qreal x, qreal y, qreal radius, qreal angle, ItemType type);

    void updateAngle();

protected:
    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

public:
    qreal m_angle;
};

//------------------------------------------------------------------------------

// ����
class BChord : public BPie
{
public:
    BChord(qreal x, qreal y, qreal radius, qreal angle, ItemType type);

    void updateEndAngle();

protected:
    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

public:
    qreal m_end_angle;
};

//------------------------------------------------------------------------------

// ����
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

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

public:
    qreal m_radius;
    bool is_create_finished;
};

//------------------------------------------------------------------------------

// Բ�˾���
class BRound_End_Rectangle : public BRectangle
{
public:
    BRound_End_Rectangle(qreal x, qreal y, qreal width, qreal height, ItemType type);

protected:
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;
};

//------------------------------------------------------------------------------

// Բ�Ǿ���
class BRounded_Rectangle : public BRectangle
{
public:
    BRounded_Rectangle(qreal x, qreal y, qreal width, qreal height, ItemType type);

    void updateRadius();
    void updateAnotherEdge(QPointF p);
    qreal getRadius();
    QPointF getAnotherEdge();
    void setAnotherEdge(QPointF p);

protected:
    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

public:
    QPointF m_another_edge;
    qreal m_radius;
};

//------------------------------------------------------------------------------
