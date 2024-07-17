#pragma once

class Yes{
private:
    const char *clone;
    const char *msg;
    const char *file;
    const int seq;
public:
    Yes(const char *,const char *,int);
    //Yes(const Yes&)=delete;
    Yes(const Yes&);
    virtual ~Yes();
    void show(const char *) const;
};
class WrapYes{
private:
    Yes instance;
    Yes *ptr;
public:
    WrapYes(const char *,int);
    ~WrapYes();
    const Yes& refOfPtr();
    const Yes& refOfInst();
    const Yes* ptrOfPtr();
    const Yes* ptrOfInst();
};