#include <iostream>
#include "test_yes.h"


using namespace std;
Yes::Yes(const char *n,const char *f,int num):clone("原生"),msg(n),file(f),seq(num){
    std::cout << "开始　" << clone << n << " " << f << "(" << num << ")" << std::endl;
}
Yes::~Yes(){
    std::cout << "结束　" << clone << msg << " " << file <<"(" << seq << ")" << std::endl;
}
void Yes::show(const char *suf) const{
    std::cout << "显示　" << clone << msg << " " << file <<"(" << seq << ")" << suf << std::endl;
}
Yes::Yes(const Yes& r):clone("克隆"),seq(r.seq)
{
    msg=r.msg;
    file=r.file;
    std::cout << "复制　" << clone << msg << " " << file <<"(" << seq << ")" << std::endl;
}

WrapYes::WrapYes(const char *a,int c):instance(Yes(a,"实体",c)),ptr(new Yes(a,"指针",c)){}
WrapYes::~WrapYes()
{
    delete ptr;
}

const Yes& WrapYes::refOfPtr()
{
    std::cout << "inside refOfPtr()" << std::endl;
    return *ptr;
}
const Yes& WrapYes::refOfInst(){
    std::cout << "inside refOfInst()" << std::endl;
    return instance;
}
const Yes* WrapYes::ptrOfPtr(){
    return ptr;
}
const Yes* WrapYes::ptrOfInst(){
    return &instance;
}
