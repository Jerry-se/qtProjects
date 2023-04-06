#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLocalServer;
class QLocalSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void showMessage(const QString &msg);

private slots:
    void onNewConnection();
    void onDisconnected();
    void onReadyRead();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QLocalServer *server;
    QList<QLocalSocket *> clients;
};
#endif // MAINWINDOW_H
