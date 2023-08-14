#pragma once
#pragma execution_character_set("utf-8")
#include <QGraphicsView>
#include <QMouseEvent>

class QGraphicsViewBasic : public QGraphicsView
{
public:
    QGraphicsViewBasic(QWidget* parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
};