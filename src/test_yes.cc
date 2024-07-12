#include <iostream>
#include "test_yes.h"
using namespace std;
Yes::Yes(const char *n,const char *f,int num):msg(n),file(f),seq(num){
    std::cout << "开始　" << n << " " << f << "(" << num << ")" << std::endl;
}
Yes::~Yes(){
    std::cout << "结束　" << msg << " " << file <<"(" << seq << ")" << std::endl;
}
void Yes::show() const{
    std::cout << "显示　" << msg << " " << file <<"(" << seq << ")" << std::endl;
}