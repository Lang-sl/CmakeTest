#pragma once
#pragma execution_character_set("utf-8")
#include <QGraphicsView>
#include <QMouseEvent>

#include "QGraphicsSceneBasic.h"

class QGraphicsViewBasic : public QGraphicsView
{
    Q_OBJECT
public:
    QGraphicsViewBasic(QWidget* parent = nullptr);

    void addItem(QGraphicsItemBasic::ItemType itemType);

    void clear();

Q_SIGNALS:
    void ItemFocusIn(QAbstractGraphicsShapeItem* i);

    void ItemFocusOut(QAbstractGraphicsShapeItem* i);


public slots:
    void bindItemFocus(QGraphicsItemGroup* group);
    void bindPointFocus(BPointItem* point);
    void itemIsFocusIn(QAbstractGraphicsShapeItem* i);
    void itemIsFocusOut(QAbstractGraphicsShapeItem* i);

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual bool eventFilter(QObject* obj, QEvent* event) override;

    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    QGraphicsSceneBasic* m_scene;
    BMixArcLineItems* m_mixArcLineItems = nullptr;
};