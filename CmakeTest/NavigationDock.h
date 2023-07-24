#pragma once
#pragma execution_character_set("utf-8")
#include <QDockWidget>
#include <QListWidget>
#include <QCheckBox>

#include "GLWidget.h"

class NavigationDock : public QDockWidget {
    Q_OBJECT
public:
    explicit NavigationDock(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    QCheckBox* GridCheckBox();
    QCheckBox* AxisCheckBox();
    QCheckBox* DrawCheckBox();

private:
    QListWidget* listWidget;
    QCheckBox* gridCheckBox;
    QCheckBox* axisCheckBox;
    QCheckBox* drawCheckBox;

};

