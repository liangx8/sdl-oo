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
    SooException(const SooException&)=delete;
    ~SooException();
};

#define EX(msg) SooException(msg)
#define EXMSG(ex,msg) SooException(ex,msg)

#define THROW_SDL_NOT_ZERO(c) if(c){throw EX(SDL_GetError());}
#define THROW_SDL_NULL(c) if(c==nullptr){throw EX(SDL_GetError());}