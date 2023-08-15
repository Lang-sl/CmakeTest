#include "QGraphicsSceneBasic.h"
#include "QColorItem.h"
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>

QGraphicsSceneBasic::QGraphicsSceneBasic(QObject* parent) : QGraphicsScene(parent)
{
    is_creating_BPolygon = false;
    for (int i = 0; i < 10; ++i) {
        ColorItem* colorItem = new ColorItem;
        colorItem->setPos(i * 100 - 500, -300);

        this->addItem(colorItem);
    }
}

void QGraphicsSceneBasic::startCreate()
{
    is_creating_BPolygon = true;
    m_list.clear();
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
