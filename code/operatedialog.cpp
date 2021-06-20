#include "operatedialog.h"
#include "ui_operatedialog.h"

operateDialog::operateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::operateDialog)//admin点击operate后弹出窗口
{
    ui->setupUi(this);
    connect(ui->saveButton,&QPushButton::clicked,this,&operateDialog::savebook);//保存
    connect(ui->backButton,&QPushButton::clicked,this,&operateDialog::backtobook);//返回
    connect(ui->deleteButton,&QPushButton::clicked,this,&operateDialog::deletebook);//删除
}

operateDialog::~operateDialog()
{
    delete ui;
}
void operateDialog::getid(QString id){//通过这本书的id获得book的信息
    ui->tableWidget->setRowCount(1);//一本书，所以只有一行
    Book b;
    b=b.GetaBook(id);
    QString str10=b.id;
    int cat=b.cat;
    if(cat==1) ui->book_Button->setChecked(true);
    else if(cat==2) ui->per_Button->setChecked(true);
    else if(cat==3) ui->news_Button->setChecked(true);//确定初始时位于哪个分类
    QString str0=b.book_name;
    QString str1=b.author_name;
    QString str2=b.press;
    QString str3=b.p_year;
    QString str4=b.p_month;
    QString str5=b.p_day;
    QString str6=QString::number(b.price);
    QString str7=QString::number(b.amount_in);
    QString str8=QString::number(b.amount_lend);
    QString str9=QString::number(b.amount_now);
    ui->tableWidget->setItem(0,0,new QTableWidgetItem(str0));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(str1));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(str2));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem(str3));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem(str4));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(str5));
    ui->tableWidget->setItem(0,6,new QTableWidgetItem(str6));
    ui->tableWidget->setItem(0,7,new QTableWidgetItem(str7));
    ui->tableWidget->setItem(0,8,new QTableWidgetItem(str8));
    ui->tableWidget->setItem(0,9,new QTableWidgetItem(str9));
    ui->idlabel->setText(str10);
    //将书籍信息填入tablewidget

}
void operateDialog::savebook(){//保存按钮
    Book b;
    QString _id=ui->idlabel->text();//获取id
    QButtonGroup *bg=new QButtonGroup(this);
    bg->addButton(ui->book_Button,1);
    bg->addButton(ui->per_Button,2);
    bg->addButton(ui->news_Button,3);
    int _cat=bg->checkedId();//获取cat
    QTableWidgetItem *item0 = ui->tableWidget->item(0,0);
    QTableWidgetItem *item1 = ui->tableWidget->item(0,1);
    QTableWidgetItem *item2 = ui->tableWidget->item(0,2);
    QTableWidgetItem *item3 = ui->tableWidget->item(0,3);
    QTableWidgetItem *item4 = ui->tableWidget->item(0,4);
    QTableWidgetItem *item5 = ui->tableWidget->item(0,5);
    QTableWidgetItem *item6 = ui->tableWidget->item(0,6);
    QTableWidgetItem *item7 = ui->tableWidget->item(0,7);
    QTableWidgetItem *item8 = ui->tableWidget->item(0,8);
    QTableWidgetItem *item9 = ui->tableWidget->item(0,9);
    if(item0==NULL||item0->text().isEmpty()){//若item0指针指向的表格为空，或者输入的text为空，下面同理
        QMessageBox::warning(this,tr("warning"),tr("失败：书名不能为空"));
        return;
    }
    QString _book_name=item0->text();

    if(item1==NULL||item1->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：作者不能为空"));
        return;
    }
    QString _author_name=item1->text();

    if(item2==NULL||item2->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：出版社不能为空"));
        return;
    }
    QString _press=item2->text();

    if(item3==NULL||item3->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：出版年不能为空"));
        return;
    }
    QString _p_year=item3->text();

    if(item4==NULL||item4->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：出版月不能为空"));
        return;
    }
    QString _p_month=item4->text();

    if(item5==NULL||item5->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：出版日不能为空"));
        return;
    }
    QString _p_day=item5->text();

    if(item6==NULL||item6->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：金额不能为空"));
        return;
    }
    QString _price=item6->text();

    if(item7==NULL||item7->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：总入库数量不能为空"));
        return;
    }
    QString _amount_in=item7->text();

    if(item8==NULL||item8->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：借出数量不能为空"));
        return;
    }
    QString _amount_lend=item8->text();

    if(item9==NULL||item9->text().isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：当前库存不能为空"));
        return;
    }
    QString _amount_now=item9->text();
    int temp=b.Operate_checkbook(_amount_in.toInt(),_amount_now.toInt(),_amount_lend.toInt());
    if(temp==2){
        QMessageBox::warning(this,tr("warning"),tr("失败：总入库数量不等于借出数加当前库存"));
    }
    else if(temp==0){
        b.Save_Book(_id,_book_name,_author_name,_cat,_press,_p_year,_p_month,_p_day,
                    _price.toFloat(),_amount_in.toInt(),_amount_now.toInt(),_amount_lend.toInt());
        QMessageBox::information(this,tr("accepted"),tr("保存成功"));
    }
}

void operateDialog::backtobook(){//返回bookmainwindow
    this->close();
    BookMainWindow *bmwindow=new BookMainWindow;
    bmwindow->show();
}
void operateDialog::deletebook(){//删除这本书
    Book b;
    QString _id=ui->idlabel->text();
    b.DeleteBook(_id);
    QMessageBox::information(this,tr("accepted"),tr("删除成功"));
}
