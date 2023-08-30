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
    is_creating_BMixArcLineItems = false;
    ArcOrLine = false;
}

void QGraphicsSceneBasic::startCreateBPolygon()
{
    is_creating_BPolygon = true;
}

void QGraphicsSceneBasic::startCreateBMixArcLineItems()
{
    is_creating_BMixArcLineItems = true;
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
    this->addItem(new CoordinateSystem(QGraphicsItemBasic::ItemType::CoordinateSystem));
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
    /*if (is_creating_BPolygon) {
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
    }*/
    if (is_creating_BMixArcLineItems)
    {
        QPointF p(event->scenePos().x(), event->scenePos().y());

        switch (event->buttons())
        {
        case Qt::LeftButton: {
            if (p.x() < 0)
            {
                emit pointIllegal();
                return;
            }
            if (!ArcOrLine)
                emit updatePoint(p, BMixArcLineItems::PointType::LineEdgeEnd);
            else
                emit updatePoint(p, BMixArcLineItems::PointType::ArcEdgeEnd);
        } break;
        case Qt::RightButton: {
            emit updatePoint(p, BMixArcLineItems::PointType::Center);
            emit createBMixArcLineItemsFinished();
            is_creating_BMixArcLineItems = false;
        } break;
        default: break;
        }
    }
    else {
        update();
        QGraphicsScene::mousePressEvent(event);
    }
}

void QGraphicsSceneBasic::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    if (is_creating_BMixArcLineItems)
    {
        ArcOrLine = !ArcOrLine;
    }
    else
        QGraphicsScene::wheelEvent(event);
}
