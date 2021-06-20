#ifndef BOOKMAINWINDOW_H
#define BOOKMAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "book.h"
#include "extern.h"
#include <QMessagebox>
#include "timer.h"
#include "operatedialog.h"
#include "adddialog.h"
namespace Ui {
class BookMainWindow;
}

class BookMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookMainWindow(QWidget *parent = 0);
    ~BookMainWindow();
    void PrintList(int n);

private:
    Ui::BookMainWindow *ui;


signals:
    void sendsignal();
    void sendid(QString id);
public slots:
    void backtoMain();
    void Search();
    void lendBook();
    void admin_operate();
    void admin_add();
    void reshow();

};

#endif // BOOKMAINWINDOW_H
