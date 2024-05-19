#include "view/main_window.h"

MainWindow::MainWindow(int width, int height, std::shared_ptr<MainClient> client, QWidget * parent): QMainWindow(parent) {
    setWindowTitle("IP Tracker");
    resize(width, height);
    client_ = client;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    client_->Stop();
    QMainWindow::closeEvent(event);
}
