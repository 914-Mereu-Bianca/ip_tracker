#ifndef _MAIN_WIDGET_H_
#define _MAIN_WIDGET_H_

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QLayoutItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <../build/proto_generated/ip_tracker.grpc.pb.h>
#include <../build/proto_generated/ip_tracker.pb.h>

class MainWidget: public QWidget {
public:
    MainWidget(QMainWindow* parent=nullptr);
    ~MainWidget()=default;
    void SetupWidgets();
    
signals:
    void authenticate(const std::string &username, const std::string &password);
    void setRequest(const std::string &request, const std::string &name, const std::string &mac);

public slots:
    void HandleLogin();
    void onCellClicked(int row, int column);
    void populate(data::Response devices);
    void createTable();
    void displayErrorMessage(); 
    
private:
    Q_OBJECT
    QVBoxLayout *layout_;
    QWidget* central_widget_;

    QLabel *error_label_;

    QLineEdit *username_input_;
    QLineEdit *password_input_;
    QPushButton *button_;
    QLabel *image_label_;

    QLabel *router_ip_;
    QLabel *router_mac_;

    QTableWidget *table_;

    bool auth = 0;
};
#endif  // _MAIN_WIDGET_H_  