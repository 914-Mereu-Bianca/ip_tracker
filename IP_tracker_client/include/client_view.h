#ifndef _CLIENT_VIEW_H_
#define _CLIENT_VIEW_H_

#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include "rtopclient_impl.h"
#include "components/info_process_widget.h"
#include "mainwindow.h"
#include <memory>

class ClientView {
//This class controls the way the data from the client is displayed
public:
    ClientView();
    // Copy constructor - deleted
    ClientView(RTopClientView &other) = delete;
    // Copy assignment operator - deleted
    ClientView& operator=(RTopClientView &other) = delete;
    // Move constructor
    ClientView(RTopClientView &&other) = default;
    // Move assignment operator
    ClientView& operator=(RTopClientView &&other) = default;
    // This function starts the client and the thread that reads the data
    void runClient();
    ~ClientView();
private:
    MainWindow* main_window_;

};

#endif