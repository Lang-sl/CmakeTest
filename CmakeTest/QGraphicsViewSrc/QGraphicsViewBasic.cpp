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

    // �����������¼�
    setMouseTracking(true); // �������׷�٣�ȷ�����Բ����������¼�

    // ��GraphicsView���¼��������к����������¼�
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
        event->ignore(); // �����������¼�
        return true;
    }

    return QObject::eventFilter(obj, event);
}
