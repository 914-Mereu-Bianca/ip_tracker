#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>
#include <QWidget>
#include "auth_client_impl.h"

class MainWindow: public QMainWindow {
// This class defines a window with adjustable width and height
public:
    MainWindow(int width, int height, std::shared_ptr<AuthClientImpl> client, QWidget *parent = nullptr);
    ~MainWindow()=default;
private:
    Q_OBJECT
    std::shared_ptr<AuthClientImpl> auth_client_;

protected:
    // This function shuts down the client when the application is closed
    void closeEvent(QCloseEvent *event) override;

    
};

#endif  // _MAIN_WINDOW_H_