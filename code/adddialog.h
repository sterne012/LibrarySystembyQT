#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "bookmainwindow.h"
#include "book.h"
namespace Ui {
class addDialog;
}

class addDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDialog(QWidget *parent = 0);
    ~addDialog();
    void savebook();
    void backtobook();
signals:
    void sendsignal();
private:
    Ui::addDialog *ui;
};

#endif // ADDDIALOG_H
