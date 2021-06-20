#ifndef ACCOUNTMAINWINDOW_H
#define ACCOUNTMAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "extern.h"
#include <QMessageBox>
namespace Ui {
class AccountMainWindow;
}

class AccountMainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void sendsignal();
public:
    explicit AccountMainWindow(QWidget *parent = 0);
    ~AccountMainWindow();
    void deleteAccount();
    void PrintaccList();
public slots:
    void backtoMain();

private:
    Ui::AccountMainWindow *ui;
};

#endif // ACCOUNTMAINWINDOW_H
