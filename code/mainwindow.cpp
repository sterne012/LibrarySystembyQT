#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "extern.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    //一个显示今天时间的时钟
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//和bookmainwindow里面一样，不能编辑
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//行选
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//单选
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,150);
    ui->tableWidget->setColumnWidth(5,150);
    ui->labe_log->setText("        请先登录");//提示登录

    connect(ui->Login,&QPushButton::clicked,[=](){
        LoginDialog login(this);
        if(login.exec()==LoginDialog::Accepted){
            QString str="Welcome,"+user.name;
            ui->labe_log->setText(str);
            Printlist();
        }
    });
    //login 按钮，按下后弹出logindialog
    connect(ui->libButton,&QPushButton::clicked,this,&MainWindow::turntoLibrary);//进入图书馆
    connect(ui->returnButton,&QPushButton::clicked,this,&MainWindow::ReturnBook);//还书按钮
    connect(ui->renewButton,&QPushButton::clicked,this,&MainWindow::RenewBook);//续借按钮
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::Printlist);//更新借书的列表
    connect(ui->accButton,&QPushButton::clicked,this,&MainWindow::turntoAccWindow);

}
void MainWindow::timerUpdate(void)//时钟
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->label_2->setText(str);
}
void MainWindow::turntoLibrary(){
    this->hide();//主界面隐藏
    BookMainWindow *bmwindow=new BookMainWindow(this);
    bmwindow->show();//子界面出现
    connect(bmwindow,SIGNAL(sendsignal()),this,SLOT(reshow()));
}
void MainWindow::turntoAccWindow(){
    if(user.rank==0){
        this->hide();
        AccountMainWindow *newaccwindow=new AccountMainWindow(this);
        newaccwindow->show();
        connect(newaccwindow,SIGNAL(sendsignal()),this,SLOT(reshow()));
    }
    else{
        QMessageBox::warning(this, QStringLiteral("warning"), QStringLiteral("无操作权限：admin only"));
    }
}

void MainWindow::reshow(){
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Printlist(){
    int length=user.Getlist(user);//获得用户借书的本数
    ui->tableWidget->setRowCount(length);//设置行数
    for(int i=0;i<length;i++){
        book accbook;
        accbook=user.GetaBookid(user,i);//获得书的id
        QString id=accbook.id;

        Book b;
        b.SearchBook(id,0);//用查书函数查找这本书
        b=b.GetaBook(0,4);//在searchlist中得到找到的这本书
        b.deleteList(4);//删掉searchlist
        int date=user.Check_maxdate(i,user);//检查这本书借了多久
        QString str0=b.id;//id
        QString str1=b.category();//类别
        QString str2=b.book_name;//书名
        QString str3=b.author_name;//作者
        QString str4=QString::number(accbook.y)+"."+QString::number(accbook.m)+"."+QString::number(accbook.d);//借阅日期
        QString str5=QString::number(date);//剩余天数
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str0));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(str1));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(str2));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(str3));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(str4));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(str5));
        //写到tablewidegt里
    }
}
void MainWindow::ReturnBook(){//还书函数
    if(user.name=='\0'){//没登录
        QMessageBox::warning(this, QStringLiteral("warning"), QStringLiteral("请先登录"));
        return;
    }
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    int count = items.count();//没选择书
    if(count==0){
        QMessageBox::warning(this, QStringLiteral("还书"), QStringLiteral("请先选择一本书，再点击还书"));
    }
    else{
        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
        int row = ui->tableWidget->row(items.at(0));
        QTableWidgetItem *item = items.at(0);
        QString bookid=item->text();
        Book b;
        int temp=user.Check_maxdate(row,user);//检查这本书借了多久
        if(temp<0){//temp>0
            //提示超期，需要缴纳罚金
            int money=-temp*1;
            QMessageBox::warning(this, QStringLiteral("超期罚款"), QStringLiteral("请缴纳罚金:")+QString::number(money));
        }
        user.return_book(row,user);
        b.ReturnBook(bookid);
        QMessageBox::information(this,tr("accepted"),tr("还书成功"),QMessageBox::Yes);
        //还书成功，把blist里面这本书增加，alist里面这个账户下的b_list数据删除
    }
}
void MainWindow::RenewBook(){//续借函数
    if(user.name=='\0'){
        QMessageBox::warning(this, QStringLiteral("warning"), QStringLiteral("请先登录"));
        return;
    }
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    int count = items.count();
    if(count==0){
        QMessageBox::warning(this, QStringLiteral("还书"), QStringLiteral("请先选择一本书，再点击续借"));
    }//和还书里面一样
    else{
        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
        int row = ui->tableWidget->row(items.at(0));
        if(user.renew_book(row,user)){//续借，最多续一次，30天
            QMessageBox::information(this,tr("accepted"),tr("续借成功，剩余天数增加30天"),QMessageBox::Yes);
        }
        else{
            QMessageBox::warning(this, QStringLiteral("续借"), QStringLiteral("续借失败:已经续借过"));
        }
    }
}
