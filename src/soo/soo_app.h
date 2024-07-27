#pragma once
#include "soo_abstract_base.h"
class SooModel;
class SooApp:public SooAbstractBase{
private:
    SooModel *m_mdlCurrent,*m_mdlNext;
protected:
    SooApp();
    ~SooApp();
    virtual int init(void *)=0;
    virtual int release(void *)=0;
public:
    virtual const char *className() const;
    int run(void *param);
    void setModel(SooModel *model);
};