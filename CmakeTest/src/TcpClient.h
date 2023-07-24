#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHostAddress>
#include <QDebug>
#include <QCloseEvent>
#include <QFocusEvent>

class TcpClient :
    public QMainWindow
{
    Q_OBJECT

public:
    TcpClient(QMainWindow* parent = nullptr);
    void closeEvent(QCloseEvent* event) override
    {
        authClose();
    }

signals:
    void authSucces();
    void authClose();

private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onSendButtonClicked();

    void onConnected();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket* m_socket;

    QLabel* m_ipLabel;
    QLineEdit* m_ipLineEdit;
    QLabel* m_portLabel;
    QLineEdit* m_portLineEdit;
    QPushButton* m_connectButton;
    QPushButton* m_disconnectButton;

    QTextEdit* m_messageTextEdit;
    QLineEdit* m_sendTextEdit;
    QPushButton* m_sendButton;

    QLabel* m_statusLabel;

    void initUI();
};

