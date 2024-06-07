#ifndef _CHANGE_NAME_DIALOG_H
#define _CHANGE_NAME_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class ChangeNameDialog : public QDialog {
    Q_OBJECT

public:
    explicit ChangeNameDialog(QWidget *parent = nullptr);
    void execute(const std::string &name, const std::string &mac);

signals:
    void saveName(const std::string &request, const std::string &name, const std::string &mac);

public slots:
    void displayMessageDialogName(const std::string &message);

private:
    QVBoxLayout *dialog_box_layout_;
    QLineEdit *new_name_;
    QPushButton *button_save_;
    QLabel *error_label_box_;

    std::string mac_;
};

#endif // _CHANGE_NAME_DIALOG_H
