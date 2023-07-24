#include <QPainter>
#include <QDebug>
#include <cmath>

#include "GLWidget.h"

GLWidget::GLWidget(QWidget* parent)
    : QWidget(parent), m_bgColor(Qt::white)
{
    m_gridVisible = true;
    m_axisVisible = true;
    m_drawVisible = true;
    m_autosizing = false;
    m_up = true;
    m_wheel = false;
    m_originpoint.setX(width() / 2);
    m_originpoint.setY(height() / 2);
    scaleFactor = 1.1;
    axissacleFactor = 1.0;
    gridsacleFactor = 1.0;
    m_drawMode = 0;
}

void GLWidget::setDrawMode(int mode)
{
    m_drawMode = mode;
}

void GLWidget::setAutoSizing()
{
    m_autosizing = !m_autosizing;
    update();
}

void GLWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(rect(), m_bgColor);

    if (m_gridVisible) {
        drawGrid(painter, 20);
    }
    if (m_axisVisible) {
        drawAxis(painter, 40);
    }
    if (m_drawVisible)
    {
        drawAll(painter);
    }
    if (m_autosizing)
    {
        drawAutoSizing(painter);
    }
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_lastPos = event->pos();
    }
    if (event->button() == Qt::RightButton)
    {
        m_lastPos = event->pos();
        if (m_drawMode != 0) {
            m_startPoint = m_lastPos;
        }
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = event->pos() - m_lastPos;
        m_lastPos = event->pos();
        scroll(delta);
    }
    if (event->buttons() & Qt::RightButton) {
        m_lastPos = event->pos();
        if (m_drawMode == 0) {
            return;
        }
        else {
            m_endPoint = m_lastPos;
            update();
        }
    }
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    QPoint numDegrees = event->angleDelta() / 8;
    QPoint numSteps = numDegrees / 15;
    m_wheel = true;
    setscalefactor();

    if (!numSteps.isNull()) {
        QPoint deltaaxis = event->pos() - m_originpoint;
        QPoint deltastart = event->pos() - m_startPoint;
        QPoint deltaend = event->pos() - m_endPoint;


        if (numSteps.y() > 0) {
            m_up = true;
            zoom(deltaaxis, deltastart, deltaend);
        }
        else if (numSteps.y() < 0) {
            m_up = false;
            zoom(deltaaxis, deltastart, deltaend);
        }
    }

    event->accept();
}

void GLWidget::setGridVisible(bool visible)
{
    m_gridVisible = visible;
    update();
}

void GLWidget::setAxisVisible(bool visible)
{
    m_axisVisible = visible;
    update();
}

void GLWidget::setDrawVisible(bool visible)
{
    m_drawVisible = visible;
    if (m_autosizing != false || visible != true)
    {
        m_autosizing = visible;
    }
    update();
}

void GLWidget::drawGrid(QPainter& painter, int size)
{
    painter.setPen(QPen(Qt::gray, 0.5));

    //qDebug() << m_wheel << " grid";
    //m_wheel = false;
    double tempsize;
    if (size * gridsacleFactor == 0)
    {
        tempsize = std::numeric_limits<double>::min();
    }
    else
    {
        tempsize = (double)size * (double)gridsacleFactor;
    }

    for (double y = m_originpoint.y(); y >= 0; y -= tempsize) {
        painter.drawLine(0, y, width(), y);
    }
    for (double y = m_originpoint.y(); y <= height(); y += tempsize) {
        painter.drawLine(0, y, width(), y);
    }

    for (double x = m_originpoint.x(); x >= 0; x -= tempsize) {
        painter.drawLine(x, 0, x, height());
    }
    for (double x = m_originpoint.x(); x <= width(); x += tempsize) {
        painter.drawLine(x, 0, x, height());
    }
}

void GLWidget::drawAxis(QPainter& painter, int size)
{
    painter.setPen(QPen(Qt::black, 1.0));

    //qDebug() << m_wheel << " axis";
    //qDebug() << axissacleFactor << " " << scaleFactor;
    painter.drawLine(0, m_originpoint.y(), width(), m_originpoint.y());
    for (int x = m_originpoint.x(); x <= width(); x += size) {
        painter.drawLine(x, m_originpoint.y() - 5, x, m_originpoint.y() + 5);
        painter.drawText(x - 10, m_originpoint.y() + 15, QString::number(((qreal)x - m_originpoint.x()) * axissacleFactor));
    }

    for (int x = m_originpoint.x(); x >= 0; x -= size) {
        painter.drawLine(x, m_originpoint.y() - 5, x, m_originpoint.y() + 5);
        painter.drawText(x - 10, m_originpoint.y() + 15, QString::number(((qreal)x - m_originpoint.x()) * axissacleFactor));
    }

    painter.drawLine(m_originpoint.x(), 0, m_originpoint.x(), height());
    for (int y = m_originpoint.y(); y <= height(); y += size) {
        painter.drawLine(m_originpoint.x() - 5, y, m_originpoint.x() + 5, y);
        painter.drawText(m_originpoint.x() + 10, y + 5, QString::number((m_originpoint.y() - (qreal)y) * axissacleFactor));

    }
    for (int y = m_originpoint.y(); y >= 0; y -= size) {
        painter.drawLine(m_originpoint.x() - 5, y, m_originpoint.x() + 5, y);
        painter.drawText(m_originpoint.x() + 10, y + 5, QString::number((m_originpoint.y() - (qreal)y) * axissacleFactor));
    }
}

void GLWidget::drawAll(QPainter& painter)
{
    painter.setPen(QPen(Qt::black, 2.0));
    switch (m_drawMode) {
    case 1:  // Line
        painter.drawLine(m_startPoint, m_endPoint);
        break;
    case 2:  // Circle
        painter.drawEllipse(QRect(m_startPoint, m_endPoint));
        break;
    case 3:  // Rectangle
        painter.drawRect(QRect(m_startPoint, m_endPoint));
        break;
    default:
        break;
    }
}

void GLWidget::drawAutoSizing(QPainter& painter)
{
    painter.setPen(QPen(Qt::black, 1.0));
    painter.setPen(QPen(Qt::DashLine));

    painter.drawLine(m_startPoint.x(), m_startPoint.y() - 10, m_endPoint.x(), m_startPoint.y() - 10);
    painter.drawLine(m_startPoint.x(), m_startPoint.y() - 20, m_startPoint.x(), m_startPoint.y());
    painter.drawLine(m_endPoint.x(), m_startPoint.y() - 20, m_endPoint.x(), m_startPoint.y());
    painter.drawText((m_startPoint.x() + m_endPoint.x()) / 2, m_startPoint.y() - 10, QString::number(abs(m_endPoint.x() - m_startPoint.x())));

    painter.drawLine(m_endPoint.x() + 10, m_startPoint.y(), m_endPoint.x() + 10, m_endPoint.y());
    painter.drawLine(m_endPoint.x() + 20, m_startPoint.y(), m_endPoint.x(), m_startPoint.y());
    painter.drawLine(m_endPoint.x() + 20, m_endPoint.y(), m_endPoint.x(), m_endPoint.y());
    painter.drawText(m_endPoint.x() + 10, (m_startPoint.y() + m_endPoint.y()) / 2, QString::number(abs(m_endPoint.y() - m_startPoint.y())));
}

void GLWidget::setscalefactor()
{
    if (m_up && m_wheel)
    {
        gridsacleFactor /= scaleFactor;
        axissacleFactor *= scaleFactor;
    }
    else if (m_wheel)
    {
        gridsacleFactor *= scaleFactor;
        axissacleFactor /= scaleFactor;
    }
    m_wheel = false;
}

void GLWidget::scroll(const QPoint& delta)
{

    m_originpoint += delta;
    m_startPoint += delta;
    m_endPoint += delta;
    update();
}

void GLWidget::zoom(const QPoint& deltaaxis, const QPoint& deltastart, const QPoint& deltaend)
{

    //qDebug() << scaleFactor;
    if (m_up)
    {
        m_originpoint -= deltaaxis;
        m_originpoint += deltaaxis * scaleFactor;
        m_startPoint -= deltastart;
        m_startPoint += deltastart * scaleFactor;
        m_endPoint -= deltaend;
        m_endPoint += deltaend * scaleFactor;
    }
    else
    {
        m_originpoint -= deltaaxis;
        m_originpoint += deltaaxis / scaleFactor;
        m_startPoint -= deltastart;
        m_startPoint += deltastart / scaleFactor;
        m_endPoint -= deltaend;
        m_endPoint += deltaend / scaleFactor;
    }
    update();
    //m_wheel = false;
}
