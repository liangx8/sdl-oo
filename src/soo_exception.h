#pragma once
#include <exception>
#include <string>
#include <memory>

class SooException :public std::exception{
private:
    std::string m_strMsg;
public:
    virtual const char* what()const throw();
    SooException(const char *);
    SooException(const exception &,const char *);
    ~SooException();
};

#define EX(msg) SooException(msg)
#define EXMSG(ex,msg) SooException(ex,msg)

