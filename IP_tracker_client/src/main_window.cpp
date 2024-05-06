#include "main_window.h"

MainWindow::MainWindow(int width, int height, QWidget * parent): QMainWindow(parent) {
    setWindowTitle("IP Tracker");
    resize(width, height);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}
