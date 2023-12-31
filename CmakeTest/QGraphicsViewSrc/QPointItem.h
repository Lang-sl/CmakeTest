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

// 自定义功能图元 - 点
class BPointItem : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:
    enum class PointType {
        Center = 0, // 中心点
        Edge,       // 边缘点（可拖动改变图形的形状、大小）
        ArcEdge,    // 圆弧终点
        Special     // 拖拽改变半径
    };

    BPointItem(QAbstractGraphicsShapeItem* parent, QPointF p, PointType type);

    QPointF getPoint() { return m_point; }
    void setPoint(QPointF p) { m_point = p; }

signals:
    void isFocusIn(BPointItem* item);
    void isFocusOut(BPointItem* item);

protected:
    virtual QRectF boundingRect() const override;

    virtual void paint(QPainter* painter,
        const QStyleOptionGraphicsItem* option,
        QWidget* widget) override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    virtual void focusInEvent(QFocusEvent* event) override;
    virtual void focusOutEvent(QFocusEvent* event) override;

private:
    QPointF m_point;
    PointType m_type;

    //friend class QGraphicsItemBasic;
    friend class BMixArcLineItems;
};

//------------------------------------------------------------------------------

// 存放点的容器
class BPointItemList : public QObject, public QList<BPointItem*>
{
    Q_OBJECT
public:
    void setRandColor();
    void setColor(const QColor color);
    void setVisible(bool visible);
    QList<QPointF> getQPointFList();

    void append(BPointItem* item)
    {
        QList<BPointItem*>::append(item);

        // 发出自定义信号
        emit itemAppended(item);
    }

signals:
    void itemAppended(BPointItem* item);
};