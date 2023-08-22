#include "QGraphicsSceneBasic.h"
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>

QGraphicsSceneBasic::QGraphicsSceneBasic(QObject* parent) : QGraphicsScene(parent)
{
    //addColorItem();
    addCoordinateSystem();
    is_creating_BPolygon = false;
    is_creating_BMixArcLine = false;
    ArcOrLine = false;
}

void QGraphicsSceneBasic::startCreateBPolygon()
{
    is_creating_BPolygon = true;
    m_list.clear();
}

void QGraphicsSceneBasic::startCreateBMixArcLine()
{
    is_creating_BMixArcLine = true;
    m_list.clear();
}

void QGraphicsSceneBasic::addColorItem()
{
    m_colorItemList.clear();
    for (int i = 0; i < 10; ++i) {
        ColorItem* colorItem = new ColorItem;
        m_colorItemList.push_back(colorItem);
        m_colorItemList[i]->setPos(i * 100 - 500, -300);
        this->addItem(m_colorItemList[i]);
    }
}

void QGraphicsSceneBasic::addCoordinateSystem()
{
    this->addItem(new CoordinateSystem);
}

void QGraphicsSceneBasic::isShowColorItem(bool b)
{
    if (b)
    {
        for (int i = 0; i < 10; ++i) {
            m_colorItemList[i]->show();
        }
    }
    else
    {
        for (int i = 0; i < 10; ++i) {
            m_colorItemList[i]->hide();
        }
    }
}

void QGraphicsSceneBasic::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (is_creating_BPolygon) {
        QPointF p(event->scenePos().x(), event->scenePos().y());

        switch (event->buttons())
        {
        case Qt::LeftButton: {
            m_list.push_back(p);
            emit updatePoint(p, m_list, false);
        } break;
        case Qt::RightButton: {
            if (m_list.size() >= 3) {
                emit updatePoint(p, m_list, true);
                emit createBPolygonFinished();
                is_creating_BPolygon = false;
                m_list.clear();
            }
        } break;
        default: break;
        }
    }
    else if (is_creating_BMixArcLine)
    {
        QPointF p(event->scenePos().x(), event->scenePos().y());

        switch (event->buttons())
        {
        case Qt::LeftButton: {
            m_list.push_back(p);
            if (!ArcOrLine)
                emit updatePoint(p, m_list, BMixArcLine::PointType::LineEdgeEnd);
            else
                emit updatePoint(p, m_list, BMixArcLine::PointType::ArcEdgeEnd);
        } break;
        case Qt::RightButton: {
            if (m_list.size() >= 3) {
                emit updatePoint(p, m_list, BMixArcLine::PointType::Center);
                emit createBMixArcLineFinished();
                is_creating_BMixArcLine = false;
                m_list.clear();
            }
        } break;
        default: break;
        }
    }
    else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void QGraphicsSceneBasic::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF p(event->scenePos().x(), event->scenePos().y());
    if (is_creating_BPolygon) {

        //m_list.push_back(p);
        //emit updatePoint(p, m_list, false);
    }
    else if (is_creating_BMixArcLine && !m_list.empty())
    {
        if (!ArcOrLine)
            emit movePoint(p, m_list, BMixArcLine::PointType::LineEdgeEnd);
        else
            emit movePoint(p, m_list, BMixArcLine::PointType::ArcEdgeEnd);
    }
    else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void QGraphicsSceneBasic::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    if (is_creating_BMixArcLine)
    {
        ArcOrLine = !ArcOrLine;
    }
    else
        QGraphicsScene::wheelEvent(event);
}
