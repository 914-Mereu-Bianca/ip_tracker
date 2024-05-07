#ifndef _AUTH_WIDGET_H_
#define _AUTH_WIDGET_H_

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QLayoutItem>

class AuthWidget: public QWidget {
public:
    AuthWidget(QMainWindow* parent=nullptr);
    ~AuthWidget()=default;
    void SetupWidgets();
    inline const std::string getUsername() { return username_input_->text().toStdString().c_str(); }
    inline const std::string getPassword() { return password_input_->text().toStdString().c_str(); }
    inline const int clicked() { return clicked_; }
    void setClicked(); // This function gets called when an authentification failed
    void clear();

private slots:
    void HandleButtonClick();
    
private:
    Q_OBJECT
    QVBoxLayout *layout_;
    QWidget* central_widget_;
    QLabel *username_label_;
    QLineEdit *username_input_;
    QLabel *password_label_;
    QLineEdit *password_input_;
    QPushButton *button_;
    QLabel *error_label_;
    int clicked_ = -1;   // -1 - never clicked, 1 - clicked, 0 - back to not clicked
};
#endif  // _AUTH_WIDGET_H_  