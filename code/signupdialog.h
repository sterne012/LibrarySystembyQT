#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "account.h"
#include "extern.h"
namespace Ui {
class SignupDialog;
}

class SignupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDialog(QWidget *parent = 0);
    ~SignupDialog();

public slots:
    void sign();
private:
    Ui::SignupDialog *ui;
};

#endif // SIGNUPDIALOG_H
