#include "QGraphicsSceneBasic.h"
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>

QGraphicsSceneBasic::QGraphicsSceneBasic(QObject* parent) : QGraphicsScene(parent)
{
    //addColorItem();
    addCoordinateSystem();
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
