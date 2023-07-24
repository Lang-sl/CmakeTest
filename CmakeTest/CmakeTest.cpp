#include <QIcon>
#include <QPainter>
#include <math.h>
#include <QVBoxLayout>

#include "CmakeTest.h"
#include "Config.h"

CmakeTest::CmakeTest(QWidget* parent):QMainWindow(parent)
{
	//ui_.setupUi(this);
    InitScene();
}


CmakeTest::~CmakeTest()
{
    m_timeThread->terminate();
    m_timeThread->deleteLater();
}

void CmakeTest::InitScene()
{
    //set fixed size
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);

    //set title
    setWindowTitle(GAME_TITLE);

    //set icon
    setWindowIcon(QIcon(GAME_ICON));

    QToolBar* toolbar = addToolBar("Tools");
    toolbar->setMinimumHeight(50);
    toolbar->addAction("画直线");
    toolbar->addAction("画圆");
    toolbar->addAction("画矩形");
    toolbar->addSeparator();
    toolbar->addAction("自动尺寸");
    toolbar->addSeparator();
    toolbar->addAction("快速认证");

    navigationDock = new NavigationDock(this);
    addDockWidget(Qt::LeftDockWidgetArea, navigationDock);

    glWidget = new GLWidget(this);
    setCentralWidget(glWidget);

    m_timeLabel = new QLabel(this);
    remindLabel = new QLabel(this);
    remindLabel->setText("试用10s！超时将需要认证!");
    m_timeThread = new TimeThread(this);

    //QThreadPool::globalInstance()->setMaxThreadCount(5);

    QStatusBar* bar = new QStatusBar(this);
    bar->addWidget(m_timeLabel);
    bar->addWidget(remindLabel);

    setStatusBar(bar);

    connect(navigationDock->GridCheckBox(), &QCheckBox::stateChanged, glWidget, &GLWidget::setGridVisible);
    connect(navigationDock->AxisCheckBox(), &QCheckBox::stateChanged, glWidget, &GLWidget::setAxisVisible);
    connect(navigationDock->DrawCheckBox(), &QCheckBox::stateChanged, glWidget, &GLWidget::setDrawVisible);

    connect(toolbar, &QToolBar::actionTriggered, this, &CmakeTest::onToolBarActionTriggered);

    connect(m_timeThread, &TimeThread::authRemind, this, &CmakeTest::authRemindWindow);
    connect(m_timeThread, &TimeThread::timeChanged, this, &CmakeTest::updateTime);

    //QThreadPool::globalInstance()->start(m_timeThread);
    m_timeThread->start();
    //set qtimer
    //m_Timer.setInterval(GAME_RATE);
    /*connect(this, &QMainWindow::destroyed, this, [=]()
    {
            toolbar->deleteLater();
            navigationDock->deleteLater();
            glWidget->deleteLater();
            m_timeLabel->deleteLater();
            bar->deleteLater();
            remindLabel->deleteLater();
            m_tcpClient->deleteLater();
    });*/
}

void CmakeTest::updateTime(const QString& time)
{
    m_timeLabel->setText(time);
}

void CmakeTest::authRemindWindow()
{
    QMessageBox msgBox;
    msgBox.setText("您需要进行认证！");
    //msgBox.setModal(true);
    //msgBox.setWindowModality(Qt::ApplicationModal);
    msgBox.setWindowFlags(msgBox.windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    QPushButton* authButton = msgBox.addButton("认证", QMessageBox::AcceptRole);
    QPushButton* cancelButton = msgBox.addButton("取消", QMessageBox::AcceptRole);
    QPushButton* quitButton = msgBox.addButton("退出程序", QMessageBox::AcceptRole);
    connect(authButton, &QPushButton::clicked, this, &CmakeTest::auth);
    connect(cancelButton, &QPushButton::clicked, this, &CmakeTest::cancel);
    connect(quitButton, &QPushButton::clicked, this, &CmakeTest::quit);
    msgBox.exec();
}

void CmakeTest::authSuccessWindow()
{
    QMessageBox::information(this, "认证成功", "认证成功！");
    m_timeThread->setAuthTrue();
    m_timeThread->start();
    remindLabel->setText("已认证");
    this->show();
}

void CmakeTest::auth()
{
    m_tcpClient = new TcpClient(this);
    m_tcpClient->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);
    m_tcpClient->show();
    this->hide();
    connect(m_tcpClient, &TcpClient::authSucces, this, &CmakeTest::authSuccessWindow);
    connect(m_tcpClient, &TcpClient::authClose, this, &CmakeTest::cancel);
    // 在这里执行认证操作
}

void CmakeTest::quit()
{
    this->close();
    qApp->quit();
}

void CmakeTest::cancel()
{
    this->show();
    m_timeThread->start();
}

void CmakeTest::onToolBarActionTriggered(QAction* action)
{
    if (action->text() == tr("画直线")) {
        glWidget->setDrawMode(1);
    }
    else if (action->text() == tr("画圆")) {
        glWidget->setDrawMode(2);
    }
    else if (action->text() == tr("画矩形")) {
        glWidget->setDrawMode(3);
    }
    else if (action->text() == tr("自动尺寸")) {
        glWidget->setAutoSizing();
    }
    else if (action->text() == tr("快速认证")) {
        this->authSuccessWindow();
    }
}