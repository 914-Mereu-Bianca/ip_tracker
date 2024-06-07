#ifndef _VALIDATION_DIALOG_H
#define _VALIDATION_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class ValidationDialog : public QDialog {
    Q_OBJECT

public:
    explicit ValidationDialog(QWidget *parent = nullptr);
    void execute(const std::string &request, const std::string &name, const std::string &mac);

signals:
    void performRequest(const std::string &request, const std::string &name, const std::string &mac);

private:
    QVBoxLayout *layout_;
    QHBoxLayout *button_layout_;
    QLabel *validation_label_;
    QPushButton *ok_button_;
    QPushButton *cancel_button_;

    std::string request_;
    std::string name_;
    std::string mac_;
};

#endif // _VALIDATION_DIALOG_H
