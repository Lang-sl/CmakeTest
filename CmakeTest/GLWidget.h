#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>

class GLWidget : public QWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget* parent = nullptr);
    void setDrawMode(int mode);
    void setAutoSizing();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

public slots:
    void setGridVisible(bool visible);
    void setAxisVisible(bool visible);
    void setDrawVisible(bool visible);

private:
    void drawGrid(QPainter& painter, int size);
    void drawAxis(QPainter& painter, int size);
    void drawAll(QPainter& painter);
    void drawAutoSizing(QPainter& painter);
    void setscalefactor();
    void scroll(const QPoint& delta);
    void zoom(const QPoint& deltaaxis, const QPoint& deltastart, const QPoint& deltaend);

    bool m_gridVisible;
    bool m_axisVisible;
    bool m_drawVisible;
    bool m_autosizing;
    bool m_up;
    bool m_wheel;
    qreal scaleFactor;
    qreal axissacleFactor;
    qreal gridsacleFactor;
    QColor m_bgColor;
    QPoint m_lastPos;
    QPoint m_originpoint;
    QPoint m_startPoint;  // Start point for line/circle
    QPoint m_endPoint;    // End point for line/circle
    int m_drawMode;
};
