#pragma once
#include <QWidget>
#include <QUdpSocket>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QPushButton>
#include <QTextBrowser>

class UdpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UdpWidget(QWidget *parent = nullptr);

private slots:
    void sendDatagram();
    void readPendingDatagrams();

private:
    QUdpSocket m_socket;
    QLineEdit *m_ipEdit;
    QSpinBox *m_txPortSpin;
    QSpinBox *m_rxPortSpin;
    QTextEdit *m_payloadEdit;
    QPushButton *m_sendBtn;
    QTextBrowser *m_log;
};

