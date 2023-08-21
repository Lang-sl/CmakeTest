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
}

void QGraphicsSceneBasic::startCreate()
{
    is_creating_BPolygon = true;
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
                emit createFinished();
                is_creating_BPolygon = false;
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
