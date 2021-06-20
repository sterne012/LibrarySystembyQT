#ifndef OPERATEDIALOG_H
#define OPERATEDIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "book.h"
#include "bookmainwindow.h"
namespace Ui {
class operateDialog;
}

class operateDialog : public QDialog
{
    Q_OBJECT
signals:
    void sendsignal();
public:
    explicit operateDialog(QWidget *parent = 0);
    ~operateDialog();
public slots:
    void getid(QString id);
    void savebook();
    void backtobook();
    void deletebook();
private:
    Ui::operateDialog *ui;
};

#endif // OPERATEDIALOG_H
