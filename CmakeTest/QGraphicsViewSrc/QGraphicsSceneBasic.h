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

    void startCreate();

    void addColorItem();

    void addCoordinateSystem();

    void isShowColorItem(bool b);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  
signals:
    void updatePoint(QPointF p, QList<QPointF> list, bool isCenter);
    void createFinished();

protected:
    QList<QPointF> m_list;
    QList<ColorItem*> m_colorItemList;
    bool is_creating_BPolygon;
};