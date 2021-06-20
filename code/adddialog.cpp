#include "adddialog.h"
#include "ui_adddialog.h"

addDialog::addDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialog)//admin点击add后开启窗口
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    connect(ui->saveButton,&QPushButton::clicked,this,&addDialog::savebook);//保存
    connect(ui->backButton,&QPushButton::clicked,this,&addDialog::backtobook);//返回

}
void addDialog::savebook(){//保存，功能与operatedialog中类似，在此不再赘述
    Book b;
    QString _id=ui->lineEdit->text();
    if(_id.isEmpty()){
        QMessageBox::warning(this,tr("warning"),tr("失败：id不能为空"));
        return;
    }
    QButtonGroup *bg=new QButtonGroup(this);
    bg->addButton(ui->book_Button,1);
    bg->addButton(ui->per_Button,2);
    bg->addButton(ui->news_Button,3);
    int _cat=bg->checkedId();
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
    if(item0==NULL||item0->text().isEmpty()){
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


    int temp=b.Add_checkbook(_id,_cat,_amount_in.toInt(),_amount_now.toInt(),_amount_lend.toInt());
    if(temp==1){
        QMessageBox::warning(this,tr("warning"),tr("失败：使用了重复的id"));
    }
    else if(temp==2){
        QMessageBox::warning(this,tr("warning"),tr("失败：总入库数量不等于借出数加当前库存"));
    }
    else if(temp==3){
        QMessageBox::warning(this,tr("warning"),tr("失败：请选择分类"));
    }
    else if(temp==0){
        b.Add_Book(_id,_book_name,_author_name,_cat,_press,_p_year,_p_month,_p_day,
                    _price.toFloat(),_amount_in.toInt(),_amount_now.toInt(),_amount_lend.toInt());
        QMessageBox::information(this,tr("accepted"),tr("保存成功"));
    }
}
addDialog::~addDialog()
{
    delete ui;
}
void addDialog::backtobook(){
    this->close();
    BookMainWindow *bmwindow=new BookMainWindow;
    bmwindow->show();
}
