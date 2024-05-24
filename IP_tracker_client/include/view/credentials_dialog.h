#ifndef _CREDENTIALS_DIALOG_H
#define _CREDENTIALS_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class CredentialsDialog : public QDialog {
    Q_OBJECT

public:
    explicit CredentialsDialog(QWidget *parent = nullptr);

signals:
    void saveCredentials(const std::string &username, const std::string &password, const std::string &current_password);

public slots:
    void displayMessageDialogCredentials(const std::string &message);

private:
    QVBoxLayout *dialog_box_layout_;
    QLineEdit *new_username_;
    QLineEdit *new_password_;
    QLineEdit *current_password_;
    QPushButton *button_save_credentials_;
    QLabel *error_label_box_;
};

#endif // _CREDENTIALS_DIALOG_H
