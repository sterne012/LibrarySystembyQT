#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QDateTime>
#include <QString>
#include <QList>
#include <QDebug>
#include "timer.h"
struct book{
    QString id;
    int y,m,d;
    int renew;//续借，1=续借了一次
};
class Account
{
public:
    static int num;
    int id;
    QString name;
    int rank;
    int lend_book;
    int max_lend_book;
    int max_date;
    QList<book> b_list;

    void add_Account(int _id,QString _name,int _rank);
    bool Search_Account();//遍历链表，用于登录
    bool Check_Account();//遍历链表，用于注册检查有没有使用重复的id和name
    bool Check_Lendbook(Account acc);//检查这个账户是否达到借阅上限
    int Check_maxdate(int n,Account acc);//聪明的我选择传递行号（要不然可能借了一本书很多次）
    void add_book(QString _id,Account acc);//记录每个账户借书的信息
    void add_book(QString _id,Account acc,int _y,int _m,int _d);
    void return_book(int n,Account acc);//聪明的我还想用行号
    bool renew_book(int n,Account acc);
    int Getlist(Account acc);//获得某个账户下借阅列表的长度
    int Getacclist();//获得用户的数目
    Account Getaccount(int i);//获得第i个用户的信息
    book GetaBookid(Account acc,int i);
    void DeleteAccount(int _id);

};

#endif // ACCOUNT_H
