#include "logindialog.h"
#include "ui_logindialog.h"
#include "extern.h"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)//用于显示登录的ui界面
{
    ui->setupUi(this);
    connect(ui->signup,&QPushButton::clicked,[=](){
        SignupDialog sign(this);
        sign.exec();
    });
    //点击signup开启注册的界面

    connect(ui->ok_Button,&QPushButton::clicked,this,&LoginDialog::login);//ok后执行login函数
    connect(ui->cancel_Button,&QPushButton::clicked,this,&LoginDialog::close);//取消->关闭窗口
}
void LoginDialog::login(){//点击登录按钮后运行，登录函数
    int id = ui->idEdit->text().toInt();
    int rank=-1;
    QString name = ui->nameEdit->text();
    QButtonGroup *bg=new QButtonGroup(this);
    bg->addButton(ui->admin,0);
    bg->addButton(ui->stu,1);
    bg->addButton(ui->tea,2);
    rank=bg->checkedId();//选择按钮的数值
    user.id=id;
    user.name=name;
    user.rank=rank;
   //获取要登录的用户的信息
    if(user.Search_Account()){//若找到这个账户，提示登录成功
        QMessageBox::information(this,tr("accepted"),tr("登录成功"),QMessageBox::Yes);
        accept();
    }
    else{
        QMessageBox::warning(this, tr("warning"),tr("未检索到账户，请检查id/用户名/账户类型选项"),QMessageBox::Yes);
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
