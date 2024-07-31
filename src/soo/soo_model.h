#pragma once
class SooApp;
 class SooModel{
protected:
    SooApp *m_app;
public:
    virtual void attach(void *)=0;
    virtual int run(void *)=0;
    virtual void detach(void *)=0;
    SooModel(SooApp *app);
};