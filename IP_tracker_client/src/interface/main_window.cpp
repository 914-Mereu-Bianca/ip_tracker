#include "interface/main_window.h"

MainWindow::MainWindow(int width, int height, std::shared_ptr<AuthClientImpl> auth_client, QWidget * parent): QMainWindow(parent) {
    setWindowTitle("IP Tracker");
    resize(width, height);
    auth_client_ = auth_client;
}

void MainWindow::ClientInitiation(std::shared_ptr<ClientImpl> client) {
    client_ = client;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    auth_client_->Stop();
    QMainWindow::closeEvent(event);
}
