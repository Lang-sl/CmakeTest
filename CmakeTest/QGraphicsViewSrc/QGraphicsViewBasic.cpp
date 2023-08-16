#include "QGraphicsViewBasic.h"

QGraphicsViewBasic::QGraphicsViewBasic(QWidget* parent) : QGraphicsView(parent)
{
    // 隐藏水平/竖直滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 设置场景范围
    setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);

    // 反锯齿
    setRenderHints(QPainter::Antialiasing);

    // 忽略鼠标滚轮事件
    setMouseTracking(true); // 开启鼠标追踪，确保可以捕获鼠标滚轮事件

    // 在GraphicsView的事件过滤器中忽略鼠标滚轮事件
    installEventFilter(this);
}

void QGraphicsViewBasic::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
}

bool QGraphicsViewBasic::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Wheel)
    {
        event->ignore(); // 忽略鼠标滚轮事件
        return true;
    }

    return QObject::eventFilter(obj, event);
}
