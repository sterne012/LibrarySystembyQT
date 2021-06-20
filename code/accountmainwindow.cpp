#include "accountmainwindow.h"
#include "ui_accountmainwindow.h"

AccountMainWindow::AccountMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AccountMainWindow)//显示账户管理界面
{
    ui->setupUi(this);
    connect(ui->backButton,&QPushButton::clicked,this,&AccountMainWindow::backtoMain);//设置返回按钮

    QString str="Welcome,"+user.name;
    ui->labe_log->setText(str);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可修改
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置一次只能选一行/列
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选行
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,200);
    ui->tableWidget->setColumnWidth(3,400);
    PrintaccList();

    connect(ui->deleteButton,&QPushButton::clicked,this,&AccountMainWindow::deleteAccount);//注销账户按钮
}

AccountMainWindow::~AccountMainWindow()
{
    delete ui;
}
void AccountMainWindow::backtoMain(){//返回主界面
    emit sendsignal();//发送信号
    this->close();//关闭窗口
}
void AccountMainWindow::deleteAccount(){//注销账户
    Account acc;
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    QTableWidgetItem *item = items.at(0);
    QString accid=item->text();//获得所选用户的id
    acc.DeleteAccount(accid.toInt());
    QMessageBox::information(this,tr("accepted"),tr("该账户已被注销"),QMessageBox::Yes);
}
void AccountMainWindow::PrintaccList(){//打印现有账户列表
    Account a;
    int length=a.Getacclist();
    ui->tableWidget->setRowCount(length);
    for(int i=0;i<length;i++){
        a=a.Getaccount(i);
        QString str0=QString::number(a.id);
        QString str1=a.name;
        QString str2=QString::number(a.rank);
        QString str3;
        int n=a.Getlist(a);
        book accbook;
        for(int j=0;j<n;j++){//遍历a的b_list显示每个用户借阅书籍的id
            accbook=a.GetaBookid(a,j);
            str3+=accbook.id+" ";
        }
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str0));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(str1));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(str2));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(str3));

    }
}
