#pragma once
class SooCommand{
public:
    virtual const char* getDescription()=0;
    virtual void execute()=0;
    virtual ~SooCommand();
};