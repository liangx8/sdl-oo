#include <iostream>
#include <sstream>
#include "soo_exception.h"

const char *SooException::what() const throw(){
    
    return mMsg;
}

SooException::SooException(const char *file,int line,const char *m){
    std::ostringstream ss;
    ss << file << '(' << line << ')' << m << std::endl;
    auto msg=ss.str();
    mMsg = new char[msg.size()+1];
    msg.copy(mMsg,msg.size()+1);
        
}
SooException::SooException(const char *file,int line,const exception &ex,const char *m)
{
        std::ostringstream ss;
        ss << file << '(' << line << ')' << m << "=>" << ex.what() << std::endl;
        auto msg=ss.str();
        mMsg = new char[msg.size()+1];
        msg.copy(mMsg,msg.size()+1);
}
SooException::~SooException(){
    delete []mMsg;
}

Yes::Yes(const char *n,const char *f,int num):msg(n),file(f),seq(num){
    std::cout << "开始　" << n << " " << f << "(" << num << ")" << std::endl;
}
Yes::~Yes(){
    std::cout << "结束　" << msg << " " << file <<"(" << seq << ")" << std::endl;
}
void Yes::show() const{
    std::cout << "显示　" << msg << " " << file <<"(" << seq << ")" << std::endl;
}