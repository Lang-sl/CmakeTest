#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QWidget>
#include <QMainWindow>
#include <QToolBar>
#include <Qtimer>
#include <Qevent>
#include <QLabel>
#include <QStatusBar>
#include <QThreadPool>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

#include "NavigationDock.h"
#include "GLWidget.h"
#include "TimeThread.h"
#include "TcpClient.h"
#include "ui_CmakeTest.h"

class CmakeTest:public QMainWindow
{
	Q_OBJECT
public:
	CmakeTest(QWidget *parent = nullptr);
	~CmakeTest();

	void InitScene();

private slots:
	void onToolBarActionTriggered(QAction* action);
	void updateTime(const QString& time);
	void authRemindWindow();
	void authSuccessWindow();
	void auth();
	void quit();
	void cancel();

private:
	Ui::CmakeTestClass ui_;
	NavigationDock* navigationDock;
	GLWidget* glWidget;
	TimeThread* m_timeThread;
	TcpClient* m_tcpClient;

	QLabel* m_timeLabel;
	QLabel* remindLabel;

};
