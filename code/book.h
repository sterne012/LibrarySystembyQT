#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QList>
#include <QDebug>
#include "extern.h"
class Book
{
public:
    QString id;									//id
    QString book_name;						//书名
    QString author_name;                    //作者
    QString press;							//出版社
    QString p_year, p_month, p_day;				//出版日期
    float price;							//金额
    int cat;                                //类别,1=book,2=period,3=newspaper
    int amount_in;							//总入库数量
    int amount_now;							//当前库存量
    int amount_lend;						//借出本数

    Book();
    void Add_Book(QString _id,QString _book_name,QString _author_name,int _cat,
                  QString _press,QString _p_year,QString _p_month,QString _p_day,float _price,
                  int _amount_in,int _amount_now,int _amount_lend);//参数大全版
    void Save_Book(QString _id,QString _book_name,QString _author_name,int _cat,
                   QString _press,QString _p_year,QString _p_month,QString _p_day,float _price,
                   int _amount_in,int _amount_now,int _amount_lend);
    QString category();
    Book GetaBook(int i,int n);
    Book GetaBook(QString _id);
    int SearchBook(QString str,int n);
    int LendBook(QString _id);
    void ReturnBook(QString _id);
    int GetList(int n);
    void deleteList(int n);
    void DeleteBook(QString _id);
    int Add_checkbook(QString _id,int _cat,int _amount_in,int _amount_now,int _amount_lend);
    int Operate_checkbook(int _amount_in,int _amount_now,int _amount_lend);
};

#endif // BOOK_H
