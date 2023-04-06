#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLocalServer>
#include <QLocalSocket>

struct IpcMessage
{
    quint32 version;
    QString type;
    QString data;
};

QDataStream& operator<<(QDataStream &in, const IpcMessage &msg)
{
    in << msg.version << msg.type << msg.data;
    return in;
}

QDataStream& operator>>(QDataStream &out, IpcMessage &msg)
{
    out >> msg.version >> msg.type >> msg.data;
    return out;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , server(new QLocalServer(this))
{
    ui->setupUi(this);
    server->listen("qt_test_local_server");
    connect(server, &QLocalServer::newConnection, this, &MainWindow::onNewConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(clients.begin(), clients.end());
}

void MainWindow::showMessage(const QString &msg)
{
    QTextEdit *edit = findChild<QTextEdit*>("textEdit");
    if (edit) edit->append(msg);
}

void MainWindow::onNewConnection()
{
    showMessage("new connection");
    QLocalSocket *newSocket = server->nextPendingConnection();
    connect(newSocket, &QLocalSocket::readyRead, this, &MainWindow::onReadyRead);
    connect(newSocket, &QLocalSocket::disconnected, this, &MainWindow::onDisconnected);
    clients << newSocket;
}

void MainWindow::onDisconnected()
{
    QLocalSocket *pClient = qobject_cast<QLocalSocket *>(sender());
    if (pClient) {
        showMessage("disconnected");
        clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void MainWindow::onReadyRead()
{
    QLocalSocket *pClient = qobject_cast<QLocalSocket*>(sender());
    if (!pClient) return;
    // QTextStream in(pClient);
    // QString recvData = in.readAll();
    // showMessage(recvData);
    QDataStream in(pClient);
    // in.setDevice(pClient);
    in.setVersion(QDataStream::Qt_5_10);
    IpcMessage msg;
    in >> msg;
    showMessage(
        QString("recv IpcMessage{ \"version\":%1, \"type\":%2, \"data\":%3 }"
                ).arg(msg.version).arg(msg.type).arg(msg.data));
    qDebug() << "recv IpcMessage{ version:" << msg.version
             << ", type:" << msg.type
             << ", data:" << msg.data
             << "}";
}

void MainWindow::on_pushButton_clicked()
{
    QLineEdit *edit = findChild<QLineEdit *>("lineEdit");
    if (!edit) return;
    QString message = edit->text();
    if (message.isEmpty()) return;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    // out << quint32(message.size());
    // out << message;
    IpcMessage msg;
    msg.version = 0x010001;
    msg.type = "command";
    msg.data = message;
    out << msg;
    foreach (QLocalSocket *pClient, clients) {
        pClient->write(block);
        pClient->flush();
    }
}
