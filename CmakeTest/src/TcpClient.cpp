#include <QHBoxLayout>
#include <QVBoxLayout>

#include "TcpClient.h"

TcpClient::TcpClient(QMainWindow* parent)
    : QMainWindow(parent)
    , m_socket(nullptr)
{
    //qDebug() << "进入构造函数";
    initUI();
    //qDebug() << "初始化UI完成";
}

void TcpClient::onConnectButtonClicked()
{
    // 获取输入IP和端口
    QString ip = m_ipLineEdit->text();
    int port = m_portLineEdit->text().toInt();

    // 创建套接字
    m_socket = new QTcpSocket(this);

    // 连接服务器
    m_socket->connectToHost(ip, port);

    // 更新界面状态
    m_statusLabel->setText(tr("正在连接服务器，请稍候..."));
    m_ipLineEdit->setEnabled(false);
    m_portLineEdit->setEnabled(false);
    m_connectButton->setEnabled(false);
    m_disconnectButton->setEnabled(true);

    // 连接信号槽
    connect(m_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
}


void TcpClient::onDisconnectButtonClicked()
{
    // 关闭套接字
    m_socket->close();
    m_socket->deleteLater();

    // 更新界面状态
    m_statusLabel->setText(tr("已断开与服务器的连接"));
    m_ipLineEdit->setEnabled(true);
    m_portLineEdit->setEnabled(true);
    m_connectButton->setEnabled(true);
    m_disconnectButton->setEnabled(false);

    // 清空通信记录
    m_messageTextEdit->clear();
}

void TcpClient::onSendButtonClicked()
{
    // 获取发送内容
    QString message = m_sendTextEdit->text();

    // 发送数据
    if (m_socket && m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(message.toUtf8());
    }

    // 更新通信记录
    m_messageTextEdit->append(message);
    m_sendTextEdit->clear();
}

void TcpClient::onConnected()
{
    // 更新界面状态
    m_statusLabel->setText(tr("已连接到服务器：%1:%2")
        .arg(m_socket->peerAddress().toString())
        .arg(m_socket->peerPort()));
}

void TcpClient::onReadyRead()
{
    // 读取数据
    QByteArray message = m_socket->readAll();

    // 更新通信记录
    m_messageTextEdit->append(tr("服务器：") + QString::fromUtf8(message));

    if (QString::fromUtf8(message) == "密码正确，认证成功！")
    {
        onDisconnectButtonClicked();
        this->hide();
        authSucces();
    }
}

void TcpClient::onDisconnected()
{
    // 更新界面状态
    m_statusLabel->setText(tr("已断开与服务器的连接"));

    // 关闭套接字
    m_socket->close();
    m_socket->deleteLater();

    // 更新界面状态
    m_ipLineEdit->setEnabled(true);
    m_portLineEdit->setEnabled(true);
    m_connectButton->setEnabled(true);
    m_disconnectButton->setEnabled(false);
}

void TcpClient::initUI()
{
    setWindowTitle(tr("TCP-认证客户端"));

    // 输入IP和端口
    m_ipLabel = new QLabel(tr("IP："));
    m_ipLineEdit = new QLineEdit;
    m_ipLineEdit->setPlaceholderText(tr("请输入服务器IP"));
    m_ipLineEdit->setClearButtonEnabled(true);
    m_ipLineEdit->setText("127.0.0.1");
    m_portLabel = new QLabel(tr("端口："));
    m_portLineEdit = new QLineEdit;
    m_portLineEdit->setPlaceholderText(tr("请输入服务器端口"));
    m_portLineEdit->setText("55555");

    // 连接服务器按钮
    m_connectButton = new QPushButton(tr("连接服务器"));
    connect(m_connectButton, &QPushButton::clicked, this, &TcpClient::onConnectButtonClicked);

    // 断开服务器按钮
    m_disconnectButton = new QPushButton(tr("断开服务器"));
    m_disconnectButton->setEnabled(false);
    connect(m_disconnectButton, &QPushButton::clicked, this, &TcpClient::onDisconnectButtonClicked);

    // 发送消息
    m_messageTextEdit = new QTextEdit;
    m_messageTextEdit->setReadOnly(true);
    m_messageTextEdit->setPlaceholderText(tr("消息记录"));
    m_sendTextEdit = new QLineEdit;
    m_sendTextEdit->setPlaceholderText(tr("请输入发送内容"));
    connect(m_sendTextEdit, &QLineEdit::returnPressed, this, &TcpClient::onSendButtonClicked);
    m_sendButton = new QPushButton(tr("发送"));
    connect(m_sendButton, &QPushButton::clicked, this, &TcpClient::onSendButtonClicked);

    // 状态栏
    m_statusLabel = new QLabel(tr("未连接到服务器"));

    // 布局
    QHBoxLayout* ipLayout = new QHBoxLayout;
    ipLayout->addWidget(m_ipLabel);
    ipLayout->addWidget(m_ipLineEdit);
    ipLayout->addWidget(m_portLabel);
    ipLayout->addWidget(m_portLineEdit);
    ipLayout->addWidget(m_connectButton);
    ipLayout->addWidget(m_disconnectButton);

    QVBoxLayout* messageLayout = new QVBoxLayout;
    messageLayout->addWidget(m_messageTextEdit);
    messageLayout->addWidget(m_sendTextEdit);
    messageLayout->addWidget(m_sendButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(ipLayout);
    mainLayout->addLayout(messageLayout);
    mainLayout->addWidget(m_statusLabel);

    QWidget* mainWindow = new QWidget();
    mainWindow->setLayout(mainLayout);
    this->setCentralWidget(mainWindow);
}