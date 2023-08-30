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

// �Զ��幦��ͼԪ - ��
class BPointItem : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:
    enum class PointType {
        Center = 0, // ���ĵ�
        Edge,       // ��Ե�㣨���϶��ı�ͼ�ε���״����С��
        ArcEdge,    // Բ���յ�
        Special     // ��ק�ı�뾶
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

// ��ŵ������
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

        // �����Զ����ź�
        emit itemAppended(item);
    }

signals:
    void itemAppended(BPointItem* item);
};