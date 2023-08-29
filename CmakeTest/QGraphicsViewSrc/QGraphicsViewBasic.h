#pragma once
#pragma execution_character_set("utf-8")
#include <QGraphicsView>
#include <QMouseEvent>

#include "QGraphicsSceneBasic.h"

class QGraphicsViewBasic : public QGraphicsView
{
public:
    QGraphicsViewBasic(QWidget* parent = nullptr);

    void addItem(QGraphicsItemBasic::ItemType itemType);

    void clear();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QGraphicsSceneBasic* m_scene;
};