#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>

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
    , socket(new QLocalSocket(this))
{
    ui->setupUi(this);
    connect(socket, &QLocalSocket::connected, this, &MainWindow::onConnected);
    connect(socket, &QLocalSocket::disconnected, this, &MainWindow::onDisconnected);
    connect(socket, &QLocalSocket::readyRead, this, &MainWindow::onReadyRead);
    connect(socket, &QLocalSocket::errorOccurred, this, &MainWindow::displayError);
    socket->connectToServer("qt_test_local_server");
}

MainWindow::~MainWindow()
{
    delete ui;
    socket->close();
}

void MainWindow::showMessage(const QString &msg)
{
    QTextEdit *edit = findChild<QTextEdit*>("textEdit");
    if (edit) edit->append(msg);
}

void MainWindow::onConnected()
{
    showMessage("connected");
}

void MainWindow::onDisconnected()
{
    showMessage("disconnected");
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
}

void MainWindow::displayError(QLocalSocket::LocalSocketError socketError)
{
    switch (socketError) {
    case QLocalSocket::ServerNotFoundError:
        QMessageBox::information(this, tr("Local Fortune Client"),
                                 tr("The host was not found. Please make sure "
                                    "that the server is running and that the "
                                    "server name is correct."));
        break;
    case QLocalSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Local Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the server name "
                                    "is correct."));
        break;
    case QLocalSocket::PeerClosedError:
        break;
    default:
        QMessageBox::information(this, tr("Local Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(socket->errorString()));
    }
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
    socket->write(block);
    socket->flush();
}
