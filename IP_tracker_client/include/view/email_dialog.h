#ifndef _EMAIL_DIALOG_H
#define _EMAIL_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class EmailDialog : public QDialog {
    Q_OBJECT

public:
    explicit EmailDialog(QWidget *parent = nullptr);

signals:
    void saveEmail(const std::string &email, const std::string &current_password);

public slots:
    void displayMessageDialogEmail(const std::string &message);

private:
    QPushButton *change_email_button_;
    QVBoxLayout *dialog_box_layout_email_;
    QLineEdit *new_email_;
    QLineEdit *current_password_email_;
    QPushButton *button_save_email_;
    QLabel *error_label_box_email_;
};

#endif // _EMAIL_DIALOG_H
