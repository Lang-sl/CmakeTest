#include <QHBoxLayout>
#include <QVBoxLayout>

#include "TcpClient.h"

TcpClient::TcpClient(QMainWindow* parent)
    : QMainWindow(parent)
    , m_socket(nullptr)
{
    //qDebug() << "���빹�캯��";
    initUI();
    //qDebug() << "��ʼ��UI���";
}

void TcpClient::onConnectButtonClicked()
{
    // ��ȡ����IP�Ͷ˿�
    QString ip = m_ipLineEdit->text();
    int port = m_portLineEdit->text().toInt();

    // �����׽���
    m_socket = new QTcpSocket(this);

    // ���ӷ�����
    m_socket->connectToHost(ip, port);

    // ���½���״̬
    m_statusLabel->setText(tr("�������ӷ����������Ժ�..."));
    m_ipLineEdit->setEnabled(false);
    m_portLineEdit->setEnabled(false);
    m_connectButton->setEnabled(false);
    m_disconnectButton->setEnabled(true);

    // �����źŲ�
    connect(m_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
}


void TcpClient::onDisconnectButtonClicked()
{
    // �ر��׽���
    m_socket->close();
    m_socket->deleteLater();

    // ���½���״̬
    m_statusLabel->setText(tr("�ѶϿ��������������"));
    m_ipLineEdit->setEnabled(true);
    m_portLineEdit->setEnabled(true);
    m_connectButton->setEnabled(true);
    m_disconnectButton->setEnabled(false);

    // ���ͨ�ż�¼
    m_messageTextEdit->clear();
}

void TcpClient::onSendButtonClicked()
{
    // ��ȡ��������
    QString message = m_sendTextEdit->text();

    // ��������
    if (m_socket && m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(message.toUtf8());
    }

    // ����ͨ�ż�¼
    m_messageTextEdit->append(message);
    m_sendTextEdit->clear();
}

void TcpClient::onConnected()
{
    // ���½���״̬
    m_statusLabel->setText(tr("�����ӵ���������%1:%2")
        .arg(m_socket->peerAddress().toString())
        .arg(m_socket->peerPort()));
}

void TcpClient::onReadyRead()
{
    // ��ȡ����
    QByteArray message = m_socket->readAll();

    // ����ͨ�ż�¼
    m_messageTextEdit->append(tr("��������") + QString::fromUtf8(message));

    if (QString::fromUtf8(message) == "������ȷ����֤�ɹ���")
    {
        onDisconnectButtonClicked();
        this->hide();
        authSucces();
    }
}

void TcpClient::onDisconnected()
{
    // ���½���״̬
    m_statusLabel->setText(tr("�ѶϿ��������������"));

    // �ر��׽���
    m_socket->close();
    m_socket->deleteLater();

    // ���½���״̬
    m_ipLineEdit->setEnabled(true);
    m_portLineEdit->setEnabled(true);
    m_connectButton->setEnabled(true);
    m_disconnectButton->setEnabled(false);
}

void TcpClient::initUI()
{
    setWindowTitle(tr("TCP-��֤�ͻ���"));

    // ����IP�Ͷ˿�
    m_ipLabel = new QLabel(tr("IP��"));
    m_ipLineEdit = new QLineEdit;
    m_ipLineEdit->setPlaceholderText(tr("�����������IP"));
    m_ipLineEdit->setClearButtonEnabled(true);
    m_ipLineEdit->setText("127.0.0.1");
    m_portLabel = new QLabel(tr("�˿ڣ�"));
    m_portLineEdit = new QLineEdit;
    m_portLineEdit->setPlaceholderText(tr("������������˿�"));
    m_portLineEdit->setText("55555");

    // ���ӷ�������ť
    m_connectButton = new QPushButton(tr("���ӷ�����"));
    connect(m_connectButton, &QPushButton::clicked, this, &TcpClient::onConnectButtonClicked);

    // �Ͽ���������ť
    m_disconnectButton = new QPushButton(tr("�Ͽ�������"));
    m_disconnectButton->setEnabled(false);
    connect(m_disconnectButton, &QPushButton::clicked, this, &TcpClient::onDisconnectButtonClicked);

    // ������Ϣ
    m_messageTextEdit = new QTextEdit;
    m_messageTextEdit->setReadOnly(true);
    m_messageTextEdit->setPlaceholderText(tr("��Ϣ��¼"));
    m_sendTextEdit = new QLineEdit;
    m_sendTextEdit->setPlaceholderText(tr("�����뷢������"));
    connect(m_sendTextEdit, &QLineEdit::returnPressed, this, &TcpClient::onSendButtonClicked);
    m_sendButton = new QPushButton(tr("����"));
    connect(m_sendButton, &QPushButton::clicked, this, &TcpClient::onSendButtonClicked);

    // ״̬��
    m_statusLabel = new QLabel(tr("δ���ӵ�������"));

    // ����
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