#pragma once
#include <queue>
#include <memory>
#include "soo_abstract_base.h"
class SooModel;

class SooCommand;
class SooApp:public SooAbstractBase{
private:
    std::queue<std::pair<SooCommand *,void *>> m_cmds;
    SooModel   *m_model;
    SooCommand *m_quitCommand;
    int m_isRun;
protected:
    SooApp();
    ~SooApp();
    virtual int init(void *)=0;
    virtual int release(void *)=0;
public:
    virtual const char *className() const;
    int run(void *param);
    void quit();
    void setModel(SooModel *model);
    void pushCommand(SooCommand *,void *);
};