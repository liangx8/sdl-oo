#pragma once

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
