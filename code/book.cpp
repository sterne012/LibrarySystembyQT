#include "book.h"
QList<Book> blist;
QList<Book> booklist;
QList<Book> perlist;
QList<Book> newslist;
QList<Book> searchlist;
Book::Book(){
    id='\0';
    book_name='\0';
    author_name='\0';
    press='\0';
    p_year='\0';
    p_month='\0';
    p_day='\0';
    price=0;
    cat=0;
    amount_in=0;
    amount_lend=0;
    amount_now=0;

}

void Book::Add_Book(QString _id,QString _book_name,QString _author_name,int _cat,
              QString _press,QString _p_year,QString _p_month,QString _p_day,float _price,
              int _amount_in,int _amount_now,int _amount_lend){
    this->id=_id;
    this->book_name=_book_name;
    this->author_name=_author_name;
    this->cat=_cat;
    this->press=_press;
    this->p_year=_p_year;
    this->p_month=_p_month;
    this->p_day=_p_day;
    this->price=_price;
    this->amount_in=_amount_in;
    this->amount_now=_amount_now;
    this->amount_lend=_amount_lend;
    blist.push_back(*this);
    if(cat==1) booklist.push_back(*this);
    else if(cat==2) perlist.push_back(*this);
    else if(cat==3) newslist.push_back(*this);

}
//增加
void Book::Save_Book(QString _id,QString _book_name,QString _author_name,int _cat,
               QString _press,QString _p_year,QString _p_month,QString _p_day,float _price,
               int _amount_in,int _amount_now,int _amount_lend){
    Add_Book(_id,_book_name,_author_name,_cat,_press,_p_year,_p_month,_p_day,
             _price,_amount_in,_amount_now,_amount_lend);
    DeleteBook(_id);
}

int Book::GetList(int n){
    if(n==0) return blist.size();
    else if(n==1) return booklist.size();
    else if(n==2) return perlist.size();
    else if(n==3) return newslist.size();
    else if(n==4) return searchlist.size();
    else return -1;
}
QString Book::category(){
    if(this->cat==1) return "Book";
    else if(this->cat==2) return "Periodicals";
    else if(this->cat==3) return "Newspaper";
    else return "NULL";
}
Book Book::GetaBook(int i,int n){
    if(n==0) return blist[i];
    else if(n==1) return booklist[i];
    else if(n==2) return perlist[i];
    else if(n==3) return newslist[i];
    else if(n==4) return searchlist[i];

}
Book Book::GetaBook(QString _id){
    for(auto iter=blist.begin();iter!=blist.end();iter++){
        if(iter->id==_id){
            return *iter;
        }
    }
}
int Book::SearchBook(QString str,int n){
    if(n==0){
        int i=0;
        for(auto iter=blist.begin();iter!=blist.end()&&i<blist.size();iter++){
            if(iter->id==str||iter->book_name==str||
                    iter->author_name==str||iter->press==str||
                    iter->p_year==str||iter->p_month==str||
                    iter->p_day==str)
            {
                searchlist.push_back(*iter);
            }
            i++;
        }
        if(i!=0) return 1;//找到书了返回1
        else return 0;//没找到
    }
    if(n==1)
    {
        int i=0;
        for(auto iter=booklist.begin();iter!=booklist.end()&&i<booklist.size();iter++){
            if(iter->id==str||iter->book_name==str||
                    iter->author_name==str||iter->press==str||
                    iter->p_year==str||iter->p_month==str||
                    iter->p_day==str)
            {
                searchlist.push_back(*iter);
            }
            i++;
        }
        if(i!=0) return 1;//找到书了返回1
        else return 0;//没找到
    }
    if(n==2){
        int i=0;
        for(auto iter=perlist.begin();iter!=perlist.end()&&i<perlist.size();iter++){
            if(iter->id==str||iter->book_name==str||
                    iter->author_name==str||iter->press==str||
                    iter->p_year==str||iter->p_month==str||
                    iter->p_day==str)
            {
                searchlist.push_back(*iter);
            }
            i++;
        }
        if(i!=0) return 1;//找到书了返回1
        else return 0;//没找到
    }
    if(n==3){
        int i=0;
        for(auto iter=newslist.begin();iter!=newslist.end()&&i<newslist.size();iter++){
            if(iter->id==str||iter->book_name==str||
                    iter->author_name==str||iter->press==str||
                    iter->p_year==str||iter->p_month==str||
                    iter->p_day==str)
            {
                searchlist.push_back(*iter);
            }
            i++;
        }
        if(i!=0) return 1;//找到书了返回1
        else return 0;//没找到
    }
}
void Book::deleteList(int n){
    if(n==0) blist.clear();
    else if(n==1) booklist.clear();
    else if(n==2) perlist.clear();
    else if(n==3) newslist.clear();
    else if(n==4) searchlist.clear();
    else return;
}
int Book::LendBook(QString _id){
    int _cat;
    for(auto iter=blist.begin();iter!=blist.end();iter++){
        if(iter->id==_id){
            if(iter->amount_now<1) return 0;//库存不足
            else{
                iter->amount_lend++;
                iter->amount_now--;
                _cat=iter->cat;
                break;
            }
        }
    }
    //再在每个分类下操作
    if(_cat==1){
        for(auto iter=booklist.begin();iter!=booklist.end();iter++){
            if(iter->id==_id){
                iter->amount_lend++;
                iter->amount_now--;
                return 1;
            }
        }
    }
    else if(_cat==2){
        for(auto iter=perlist.begin();iter!=perlist.end();iter++){
            if(iter->id==_id){
                iter->amount_lend++;
                iter->amount_now--;
                return 1;
            }
        }
    }
    else if(_cat==3){
        for(auto iter=newslist.begin();iter!=newslist.end();iter++){
            if(iter->id==_id){
                iter->amount_lend++;
                iter->amount_now--;
                return 1;
            }
        }
    }
    else return -2;//异常退出2
}
void Book::ReturnBook(QString _id){
    int _cat;
    for(auto iter=blist.begin();iter!=blist.end();iter++){
        if(iter->id==_id){
            iter->amount_lend--;
            iter->amount_now++;
            _cat=iter->cat;
            break;

        }
    }
    //再在每个分类下操作
    if(_cat==1){
        for(auto iter=booklist.begin();iter!=booklist.end();iter++){
            if(iter->id==_id){
                iter->amount_lend--;
                iter->amount_now++;
                return;
            }
        }
    }
    else if(_cat==2){
        for(auto iter=perlist.begin();iter!=perlist.end();iter++){
            if(iter->id==_id){
                iter->amount_lend--;
                iter->amount_now++;
                return ;
            }
        }
    }
    else if(_cat==3){
        for(auto iter=newslist.begin();iter!=newslist.end();iter++){
            if(iter->id==_id){
                iter->amount_lend--;
                iter->amount_now++;
                return ;
            }
        }
    }
}
void Book::DeleteBook(QString _id){
    int _cat;
    for(auto iter=blist.begin();iter!=blist.end();iter++){
        if(iter->id==_id){
            _cat=iter->cat;
            blist.erase(iter);
            break;

        }
    }
    //再在每个分类下操作
    if(_cat==1){
        for(auto iter=booklist.begin();iter!=booklist.end();iter++){
            if(iter->id==_id){
                booklist.erase(iter);
                return;
            }
        }
    }
    else if(_cat==2){
        for(auto iter=perlist.begin();iter!=perlist.end();iter++){
            if(iter->id==_id){
                perlist.erase(iter);
                return ;
            }
        }
    }
    else if(_cat==3){
        for(auto iter=newslist.begin();iter!=newslist.end();iter++){
            if(iter->id==_id){
                newslist.erase(iter);
                return ;
            }
        }
    }
}
int Book::Add_checkbook(QString _id,int _cat,int _amount_in,int _amount_now,int _amount_lend){
    if(_cat==-1) return 3;
    if(_amount_in!=_amount_lend+_amount_now) return 2;
    for(auto iter=blist.begin();iter!=blist.end();iter++){
        if(iter->id==_id) return 1;
    }
    return 0;
}
int Book::Operate_checkbook(int _amount_in,int _amount_now,int _amount_lend){
    if(_amount_in!=_amount_lend+_amount_now) return 2;
    else return 0;
}
