#pragma once
class SooModel{
public:
    virtual void attach(void *)=0;
    virtual int execute(void *)=0;
    virtual void detach(void *)=0;
};