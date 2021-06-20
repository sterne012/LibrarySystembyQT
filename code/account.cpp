#include "account.h"
QList<Account> alist;
int Account::num = 0;

void Account::add_Account(int _id,QString _name,int _rank){//添加账户到alist中
    num++;
    id=_id;
    name=_name;
    rank=_rank;
    lend_book=0;
    b_list.clear();
    if(rank==1){//学生账户，最多借五本，借期30天
        max_lend_book=5;
        max_date=30;
    }
    else if(rank==2){
        max_lend_book=10;
        max_date=60;
    }
    else if(rank==0){
        max_lend_book=10;
        max_date=60;
    }
    alist.push_back(*this);
}
bool Account::Search_Account(){
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==this->id&&iter->name==this->name&&iter->rank==this->rank){
            this->b_list=iter->b_list;
            this->lend_book=iter->lend_book;
            this->max_date=iter->max_date;
            this->max_lend_book=iter->max_lend_book;
            return true;
        }
    }
    return false;
}
bool Account::Check_Account(){
    if(this->name=='\0') return false;
    if(this->rank==-1) return false;
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==this->id||iter->name==this->name){
            return false;
        }
    }
    return true;
}
void Account::add_book(QString _id,Account acc){
    QDate current_date =QDate::currentDate();
    int year=current_date.year();
    int month=current_date.month();
    int day=current_date.day();
    book l;
    l.id=_id;
    l.y=year;
    l.m=month;
    l.d=day;
    l.renew=0;
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==acc.id&&iter->name==acc.name&&iter->rank==acc.rank){
            iter->lend_book++;
            iter->b_list.push_back(l);
            return;
        }
    }
}
void Account::add_book(QString _id,Account acc,int _y,int _m,int _d){
    book l;
    l.id=_id;
    l.y=_y;
    l.m=_m;
    l.d=_d;
    l.renew=0;
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==acc.id&&iter->name==acc.name&&iter->rank==acc.rank){
            iter->lend_book++;
            iter->b_list.push_back(l);
            return;
        }
    }
}
int Account::Getlist(Account acc){
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==acc.id&&iter->name==acc.name&&iter->rank==acc.rank){
            return iter->b_list.size();
        }
    }
    return -1;
}
book Account::GetaBookid(Account acc,int i){
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==acc.id&&iter->name==acc.name&&iter->rank==acc.rank){
            return iter->b_list[i];
        }
    }
}
bool Account::Check_Lendbook(Account acc){
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==acc.id&&iter->name==acc.name&&iter->rank==acc.rank){
            if(iter->lend_book==iter->max_lend_book){
                return false;
            }
            else {
                return true;
            }
        }
    }
    return false;
}
int Account::Check_maxdate(int n,Account acc){
    book l;
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==acc.id&&iter->name==acc.name&&iter->rank==acc.rank){
            l=iter->b_list[n];
            return ((iter->max_date)+(l.renew*30)-Date(l.y,l.m,l.d));//返回最大日期+续借的日期-借书的时间到今天的天数
            //如果是负值就是超期了
        }
    }
    return -1;
}
void Account::return_book(int n,Account acc){
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==acc.id&&iter->name==acc.name&&iter->rank==acc.rank){
            iter->lend_book--;
            int cnt=0;
            for(auto iter1=iter->b_list.begin();iter1!=iter->b_list.end();++iter1){
                if(cnt==n){
                    (iter->b_list).erase(iter1);
                    break;
                }
                cnt++;
            }
        break;
        }
    }
}
bool Account::renew_book(int n,Account acc){
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==acc.id&&iter->name==acc.name&&iter->rank==acc.rank){
            if(iter->b_list[n].renew==1){
                return false;
            }
            else if(iter->b_list[n].renew==0){
                iter->b_list[n].renew++;
                return true;
            }
        }
    }
}
int Account::Getacclist(){
    return alist.size();
}
Account Account::Getaccount(int i){
    return alist[i];
}
void Account::DeleteAccount(int _id){
    for(auto iter=alist.begin();iter!=alist.end();iter++){
        if(iter->id==_id){
            alist.erase(iter);
            return;
        }
    }
}
