#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include "test_yes.h"
using namespace std;
const Yes& newYes()
{
    unique_ptr<Yes> p=make_unique<Yes>("newYes()","a",__LINE__);
    return *(p.get());
}

static Yes *wide;
const Yes& existYes(const Yes &da){
    cout << "inside existYes()" << endl;
    return da;
}
const Yes& wideYes(){
    cout << "inside wideYes()" << endl;
    return *wide;
}

void demo(const Yes &da){
    cout << "exist yes test ================" << endl;
    const Yes no=existYes(da);
    cout << "after existYes()" << endl;
    wide=new Yes("demo中生成","野生",__LINE__);
    const Yes no1=wideYes();
    cout << "after wideYes()" << endl;
    delete wide;

}

void print_ints(const std::vector<int>& ints)
{
    for(auto val:ints){
        std::cout << val << ',';
    }
    std::cout << std::endl;
}

Yes& through(Yes& y)
{
    cout << "inside through()"<<endl;
    return y;
}
const string& spass(const string &s)
{
    cout << "inside spass():" << &s << endl;
    return s;
}
Yes& ary(Yes nos[],int ix)
{
    return nos[ix];
}
void old_test(){
    int myints[] = {10,20,30,30,20,10,10,20};
    std::vector<int> ints(myints,myints+8);
    std::sort(ints.begin(),ints.end());
    print_ints(ints);
    auto itr=std::lower_bound(ints.begin(),ints.end(),20);
    std::cout <<"lower_bound:"<< *itr <<"pos: "<< itr-ints.begin() << std::endl;
    itr=std::upper_bound(ints.begin(),ints.end(),20);
    std::cout <<"upper_bound:"<< *itr <<"pos: "<< itr-ints.begin() << std::endl;
    Yes local("本地","a",__LINE__);
    auto other=through(local);
    // WrapYes wy("top of WrapYes",__LINE__);
    // Yes no=wy.refOfInst();
    // no.show("run_test() 67");
    // Yes no1=wy.refOfPtr();
    // no1.show("run_test() 69");
    Yes nos[2]={Yes("a1","a",1),Yes("a1","a",2)};
    auto no=ary(nos,1);
    no.show(" run_test()");
    cout << "expect top destruction after this" << endl;
    string str("what is this?");
    cout << "address:" << &str << endl;
    auto ss=spass(str);
    cout << "address:" << &ss << endl;
}
void run_test()
{
    Yes *ptr=new Yes[2]{Yes("a1","a",1),Yes("b1","b",2)};
    Yes *p=ptr;
    p->show("----");
    p++;
    p->show("----");
    delete [] ptr;

}