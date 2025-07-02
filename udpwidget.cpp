#include "UdpWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHostAddress>
#include <QDateTime>
#include <QLabel>

UdpWidget::UdpWidget(QWidget *parent) : QWidget(parent)
{
    m_ipEdit = new QLineEdit("192.168.1.10");
    m_txPortSpin = new QSpinBox;
    m_txPortSpin->setRange(1, 65535);
    m_txPortSpin->setValue(1234);
    m_rxPortSpin = new QSpinBox;
    m_rxPortSpin->setRange(1, 65535);
    m_rxPortSpin->setValue(1235);

    m_payloadEdit = new QTextEdit;
    m_sendBtn = new QPushButton("Send");
    m_log = new QTextBrowser;

    auto top = new QHBoxLayout;
    top->addWidget(new QLabel("STM32 IP:"));
    top->addWidget(m_ipEdit);
    top->addWidget(new QLabel("Destination port:"));
    top->addWidget(m_txPortSpin);
    top->addWidget(new QLabel("Listen port:"));
    top->addWidget(m_rxPortSpin);
    top->addWidget(m_sendBtn);

    auto main = new QVBoxLayout(this);
    main->addLayout(top);
    main->addWidget(new QLabel("Payload to send:"));
    main->addWidget(m_payloadEdit, 1);
    main->addWidget(new QLabel("Log:"));
    main->addWidget(m_log, 2);

    connect(m_sendBtn, &QPushButton::clicked, this, &UdpWidget::sendDatagram);
    connect(&m_socket, &QUdpSocket::readyRead, this, &UdpWidget::readPendingDatagrams);

    m_socket.bind(m_rxPortSpin->value(), QUdpSocket::ShareAddress);
}

void UdpWidget::sendDatagram()
{
    QByteArray data = m_payloadEdit->toPlainText().toUtf8();
    QHostAddress addr(m_ipEdit->text());
    quint16 port = static_cast<quint16>(m_txPortSpin->value());

    auto written = m_socket.writeDatagram(data, addr, port);
    QString ts = QDateTime::currentDateTime().toString("hh:mm:ss");
    m_log->append(QString("[%1] TX %2 bytes send %3:%4")
                      .arg(ts).arg(written).arg(addr.toString()).arg(port));
}

void UdpWidget::readPendingDatagrams()
{
    while (m_socket.hasPendingDatagrams())
    {
        QHostAddress sender;
        quint16 senderPort;
        QByteArray datagram;
        datagram.resize(m_socket.pendingDatagramSize());
        m_socket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString ts = QDateTime::currentDateTime().toString("hh:mm:ss");
        m_log->append(QString("[%1] RX %2 bytes receive %3:%4\n%5")
                          .arg(ts).arg(datagram.size())
                          .arg(sender.toString()).arg(senderPort)
                          .arg(QString::fromUtf8(datagram)));
    }
}
