#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>
#include <QWidget>


class MainWindow: public QMainWindow {
// This class defines a window with adjustable width and height
public:
    MainWindow(int width, int height, QWidget *parent = nullptr);
    ~MainWindow()=default;
private:
    Q_OBJECT

protected:
    // This function shuts down the client when the application is closed
    void closeEvent(QCloseEvent *event) override;
};

#endif  // _MAIN_WINDOW_H_