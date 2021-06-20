#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QMessageBox>
#include "signupdialog.h"
#include "account.h"
#include "mainwindow.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

public slots:
    void login();//点击登录按钮是执行的槽函数

private:
    Ui::LoginDialog *ui;
};
#endif // LOGINDIALOG_H
