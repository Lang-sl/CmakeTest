#pragma once
#pragma execution_character_set("utf-8")
#include <QGraphicsScene>
//#include "bpointitem.h"
#include "QColorItem.h"
#include "QGraphicsItemBasic.h"

class QGraphicsSceneBasic : public QGraphicsScene
{
    Q_OBJECT

public:
    QGraphicsSceneBasic(QObject* parent = nullptr);

    void startCreateBPolygon();

    void startCreateBMixArcLineItems();

    void addColorItem();

    void addCoordinateSystem();

    void isShowColorItem(bool b);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    virtual void wheelEvent(QGraphicsSceneWheelEvent* event) override;
  
signals:
    void updatePoint(QPointF p, QList<QPointF> list, bool isCenter);
    void updatePoint(QPointF p, QList<QPointF> list, BMixArcLineItems::PointType pointType);
    void movePoint(QPointF p, QList<QPointF> list, BMixArcLineItems::PointType pointType);
    void createBPolygonFinished();
    void createBMixArcLineItemsFinished();

protected:
    QList<QPointF> m_list;
    QList<ColorItem*> m_colorItemList;
    bool is_creating_BPolygon;

    bool is_creating_BMixArcLineItems;
    bool ArcOrLine; // false Ϊ line , true Ϊ arc
};