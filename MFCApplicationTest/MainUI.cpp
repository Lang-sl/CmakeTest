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

	QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("����һ��Qt��ť"), this);
	connect(pBtn, &QPushButton::clicked, [=]() {
		QMessageBox::information(this, QString::fromLocal8Bit("�źŲ�"), QString::fromLocal8Bit("�������źŲ۵�������"));
		});
}


MainUI::~MainUI()
{

}