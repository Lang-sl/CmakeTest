#include <QGridLayout>
#include <QVBoxLayout>

#include "NavigationDock.h"

NavigationDock::NavigationDock(QWidget* parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags)
{
    listWidget = new QListWidget(this);
    listWidget->addItem("������");
    listWidget->addItem("������");
    listWidget->addItem("ͼ��");
    listWidget->setFixedSize(60, 65);

    gridCheckBox = new QCheckBox(this);
    gridCheckBox->setChecked(true);
    axisCheckBox = new QCheckBox(this);
    axisCheckBox->setChecked(true);
    drawCheckBox = new QCheckBox(this);
    drawCheckBox->setChecked(true);

    QGridLayout* mainlayout = new QGridLayout;
    mainlayout->addWidget(listWidget, 0, 0);

    QVBoxLayout* checkboxlayout = new QVBoxLayout;
    checkboxlayout->addWidget(gridCheckBox);
    checkboxlayout->addWidget(axisCheckBox);
    checkboxlayout->addWidget(drawCheckBox);

    mainlayout->addLayout(checkboxlayout, 0, 1);

    QWidget* widget = new QWidget(this);
    widget->setLayout(mainlayout);

    setWidget(widget);
    setWindowTitle("Navigation");
    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

}

QCheckBox* NavigationDock::GridCheckBox()
{
    return gridCheckBox;
}

QCheckBox* NavigationDock::AxisCheckBox()
{
    return axisCheckBox;
}

QCheckBox* NavigationDock::DrawCheckBox()
{
    return drawCheckBox;
}
