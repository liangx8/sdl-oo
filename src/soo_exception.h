#ifndef SOO_EXCEPTION_H_JKERJ32J3
#define  SOO_EXCEPTION_H_JKERJ32J3
#include <exception>
#include <string>
#include <memory>

class SooException :public std::exception{
private:
    char *mMsg;
public:
    const char* what()const throw();
    SooException(const char *,int,const char *);
    SooException(const char *,int,const exception &,const char *);
    ~SooException();
};

#define EX(msg) SooException(__FILE__,__LINE__,msg)
#define EXMSG(ex,msg) SooException(__FILE__,__LINE__,ex,msg)

class Yes{
private:
    const char *msg;
    const char *file;
    int seq;
public:
    Yes(const char *,const char *,int);
    virtual ~Yes();
    void show() const;
};

#endif