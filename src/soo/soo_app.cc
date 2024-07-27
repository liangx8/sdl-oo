#include <exception>
#include "soo_app.h"
#include "soo_model.h"
class NoOpModel:public SooModel{
    void attach(void *_){}
    int execute(void *_){return 0;}
    void detach(void *_){}
} noOperation;
SooApp::SooApp():m_mdlCurrent(&noOperation),m_mdlNext(nullptr){}
SooApp::~SooApp()
{
    // Nothing done
}
const char *SooApp::className()const{
    return "SooApp";
}
int SooApp::run(void *param)
{
    int res;
    if((res=init(param))!=0){
        return res;
    }
    while(1){
        if(m_mdlNext!= nullptr){
            m_mdlCurrent->detach(param);
            m_mdlNext->attach(param);
            m_mdlCurrent=m_mdlNext;
            m_mdlNext=nullptr;
        }
        if(m_mdlCurrent->execute(param)){
            break;
        }
    }
    if((res=release(param))!=0){
        return res;
    }
    return res;
}
void SooApp::setModel(SooModel *model)
{
    m_mdlNext=model;
}