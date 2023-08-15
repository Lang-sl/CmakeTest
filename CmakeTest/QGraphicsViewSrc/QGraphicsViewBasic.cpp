#include "QGraphicsViewBasic.h"

QGraphicsViewBasic::QGraphicsViewBasic(QWidget* parent) : QGraphicsView(parent)
{
    // ����ˮƽ/��ֱ������
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // ���ó�����Χ
    setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);

    // �����
    setRenderHints(QPainter::Antialiasing);
}

void QGraphicsViewBasic::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
}
