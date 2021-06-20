#include "signupdialog.h"
#include "ui_signupdialog.h"

SignupDialog::SignupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignupDialog)//显示注册账户的ui界面
{
    ui->setupUi(this);
    connect(ui->ok_Button,&QPushButton::clicked,this,&SignupDialog::sign);//点击ok调用sign函数
    connect(ui->cancel_Button,&QPushButton::clicked,this,&SignupDialog::close);//点击cancel调用close函数
}
void SignupDialog::sign(){//登录
    Account acc;
    int rank=-1;
    int id = ui->idEdit->text().toInt();
    QString name = ui->nameEdit->text();
    QButtonGroup *bg=new QButtonGroup(this);
    bg->addButton(ui->stu,1);
    bg->addButton(ui->tea,2);
    rank=bg->checkedId();
    acc.id=id;
    acc.name=name;
    acc.rank=rank;//获取id 用户名，rank
    if(acc.Check_Account()){//检查账户的id和name不重复或输入不合法
        acc.add_Account(acc.id,acc.name,acc.rank);
        user=acc;
        QMessageBox::information(this,tr("accepted"),tr("注册成功"),QMessageBox::Yes);

        accept();
    }
    else{
        QMessageBox::warning(this, tr("warning"),tr("注册失败：使用了重复的id/用户 或输入不合法"),QMessageBox::Yes);
    }

}

SignupDialog::~SignupDialog()
{
    delete ui;
}
