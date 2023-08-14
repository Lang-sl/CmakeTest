
// MFCApplicationTest.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MFCApplicationTest.h"
#include "MFCApplicationTestDlg.h"
#include "qmfcapp.h"
#include "MainUI.h"

#include "untitleddll.h"
#pragma comment(lib,"untitledDLL.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplicationTestApp

BEGIN_MESSAGE_MAP(CMFCApplicationTestApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCApplicationTestApp 构造

CMFCApplicationTestApp::CMFCApplicationTestApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCApplicationTestApp 对象

CMFCApplicationTestApp theApp;


// CMFCApplicationTestApp 初始化

BOOL CMFCApplicationTestApp::InitInstance()
{
	CWinApp::InitInstance();
	/*QMfcApp::instance(this);
	
	MainUI ui;
	ui.show();
	QMfcApp::exec();*/

	testFormUI(0, 0);
	return FALSE;
}

int CMFCApplicationTestApp::Run()
{
	int result = QMfcApp::run(this);
	delete qApp;
	return result;
}

