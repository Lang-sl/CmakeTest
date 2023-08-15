//MainUI.cpp
#include "pch.h"
#include "MainUI.h"
#include <QPushButton>
#include <QMessageBox>

MainUI::MainUI(QWidget* parent) :
	QWidget(parent)
{
	setWindowTitle("Qt Windows");
	setFixedSize(800, 720);

	QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("这是一个Qt按钮"), this);
	connect(pBtn, &QPushButton::clicked, [=]() {
		QMessageBox::information(this, QString::fromLocal8Bit("信号槽"), QString::fromLocal8Bit("这是由信号槽弹出来的"));
		});
}


MainUI::~MainUI()
{

}