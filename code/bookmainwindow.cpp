#include "bookmainwindow.h"
#include "ui_bookmainwindow.h"
void BookMainWindow::PrintList(int n){//打印对应分类的图书列表
    Book b;
    int length=b.GetList(n);//获得某个分类的链表长度
    ui->tableWidget->setRowCount(length);//获取列表的长度
    for(int i=0;i<length;i++){
        b=b.GetaBook(i,n);//获取一本书，输出一行的信息
        QString str0=b.id;
        QString str1=b.category();
        QString str2=b.book_name;
        QString str3=b.author_name;
        QString str4=b.press;
        QString str5=b.p_year+"."+b.p_month+"."+b.p_day;
        QString str6=QString::number(b.price);
        QString str7=QString::number(b.amount_now);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(str0));//id
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(str1));//类别
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(str2));//书名
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(str3));//作者
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(str4));//出版社
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(str5));//出版日期
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(str6));//金额
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(str7));//当前库存
    }
    //书列表实现
}

BookMainWindow::BookMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookMainWindow)//显示book的ui界面
{
    ui->setupUi(this);
    connect(ui->backButton,&QPushButton::clicked,this,&BookMainWindow::backtoMain);
    //back按钮，返回主界面
    if(user.name=='\0'){//检查登录状态
        ui->labe_log->setText("请先登录");
    }
    else{
        QString str="Welcome,"+user.name;
        ui->labe_log->setText(str);
    }
    //登录label提示 welcome+用户名
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可修改
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置一次只能选一行/列
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选行
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(1,120);
    ui->tableWidget->setColumnWidth(2,200);
    ui->tableWidget->setColumnWidth(3,200);
    ui->tableWidget->setColumnWidth(4,150);
    ui->tableWidget->setColumnWidth(5,100);
    ui->tableWidget->setColumnWidth(6,100);
    ui->tableWidget->setColumnWidth(7,100);
    //tablewidget设置每个项目的列宽


    if(user.rank==0){//管理员模式
        QPushButton* operatorButton=new QPushButton("Operate",this);
        operatorButton->move(940,650);
        operatorButton->setFixedSize(191,28);
        operatorButton->setStyleSheet("QPushButton{font: 20px 黑体}");
        connect(operatorButton,&QPushButton::clicked,this,&BookMainWindow::admin_operate);
        //将借阅按钮替换为operate，对这本书进行操作

        QPushButton* operatoraddButton=new QPushButton("Add",this);
        operatoraddButton->move(730,650);
        operatoraddButton->setFixedSize(191,28);
        operatoraddButton->setStyleSheet("QPushButton{font: 20px 黑体}");
        connect(operatoraddButton,&QPushButton::clicked,this,&BookMainWindow::admin_add);
        //增加一个add按钮用于添加图书
    }
    ui->lineEdit->setPlaceholderText(QStringLiteral("输入编号/书名/作者/出版社 进行搜索...,若无输入，进行分类筛选"));
    connect(ui->searchbutton,&QPushButton::clicked,this,&BookMainWindow::Search);
    //搜索框实现

    ui->all_Button->setChecked(1);
    PrintList(0);
    //筛选项，默认所有都显示(all)

    connect(ui->lendButton,&QPushButton::clicked,this,&BookMainWindow::lendBook);
    //借阅按钮


}
BookMainWindow::~BookMainWindow()
{
    delete ui;
}
void BookMainWindow::backtoMain(){//返回主界面
    emit sendsignal();//发送信号
    this->close();//关闭窗口
}
void BookMainWindow::Search(){//点击放大镜图标后调用筛选函数
    QButtonGroup *bg=new QButtonGroup(this);
    bg->addButton(ui->all_Button,0);
    bg->addButton(ui->book_Button,1);
    bg->addButton(ui->per_Button,2);
    bg->addButton(ui->news_Button,3);
    int cat=bg->checkedId();
    //筛选栏按钮定义编号
    QString strText = ui->lineEdit->text();
    if(strText.isEmpty()){//若搜索框为空，实现分类筛选
        PrintList(cat);//显示对应分类下的链表
    }
    else{
        Book b;
        int temp=b.SearchBook(strText,cat);//搜索
        if(temp) {
            PrintList(4);//输出searchlist
            b.deleteList(4);//并删除，下次查找时再使用
        }
        else
        {
            QMessageBox::warning(this, QStringLiteral("搜索"), QStringLiteral("查无此书"));
        }
    }
}
void BookMainWindow::lendBook(){//借阅
    if(user.name=='\0'){//没登录
        QMessageBox::warning(this, QStringLiteral("warning"), QStringLiteral("请先登录"));
        return;
    }
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    int count = items.count();//看选择了几行，因为设置每次只能选一行所以只可能是0和1
    if(count== 0){//没选书
        QMessageBox::warning(this, QStringLiteral("借阅"), QStringLiteral("请先选择一本书，再点击借阅"));
    }
    else{
        if(!user.Check_Lendbook(user)){//借阅上限
            QMessageBox::warning(this, QStringLiteral("借阅"), QStringLiteral("达到当前借阅上限"));
            return;
        }
        else{
            QTableWidgetItem *item = items.at(0);
            QString bookid=item->text();//取书的编号
            Book b;
            int temp=b.LendBook(bookid);//在Book类中，查看库存，如果库存大于0则借阅成功
            if(temp==-1||temp==-2){
                QMessageBox::warning(this, QStringLiteral("借阅"), QStringLiteral("异常退出"));
            }
            else if(temp==0){
                QMessageBox::warning(this, QStringLiteral("借阅"), QStringLiteral("库存不足"));
            }
            else if(temp==1){
                user.add_book(bookid,user);//成功的时候在account中增加借的这本书的信息
                QMessageBox::information(this,tr("accepted"),tr("借阅成功，可返回主界面查看"),QMessageBox::Yes);
            }
        }
    }
}
void BookMainWindow::admin_operate(){//管理员的operate按钮
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    int count = items.count();//看选择了几行，因为设置每次只能选一行所以只可能是0和1
    if(count== 0){
        QMessageBox::warning(this, QStringLiteral("warning"), QStringLiteral("请先选择一本书"));
        return;
    }
    else{
        operateDialog *operad=new operateDialog();
        QTableWidgetItem *item = items.at(0);
        QString bookid=item->text();//取书的编号
        connect(this,SIGNAL(sendid(QString)),operad,SLOT(getid(QString)));//获取这本书的id，便于在新的窗口中显示这本书的信息
        emit sendid(bookid);
        operad->show();
        connect(operad,SIGNAL(sendsignal()),this,SLOT(reshow()));
    }
}
void BookMainWindow::admin_add(){//管理员的add按钮
    addDialog *operadd=new addDialog();
    operadd->show();//显示新窗口
    connect(operadd,SIGNAL(sendsignal()),this,SLOT(reshow()));
}
void BookMainWindow::reshow(){//与mainwindow中reshow相同，重新显示bookmainwindow界面
    this->show();
}
