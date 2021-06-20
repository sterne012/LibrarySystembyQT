#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <qdatetime.h>
#include <QMainWindow>
#include <QString>
#include <QDebug>
#include "account.h"
#include "book.h"
#include "logindialog.h"
#include "signupdialog.h"
#include "bookmainwindow.h"
#include "accountmainwindow.h"
#include "timer.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT    //宏，允许程序使用信号和槽机制

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

public slots:
    void timerUpdate(void);
    void turntoLibrary();
    void reshow();
    void Printlist();
    void ReturnBook();
    void RenewBook();
    void turntoAccWindow();
};


#endif // MAINWINDOW_H
