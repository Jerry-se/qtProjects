#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLocalSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void showMessage(const QString &msg);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void displayError(QLocalSocket::LocalSocketError socketError);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QLocalSocket *socket;
};
#endif // MAINWINDOW_H
