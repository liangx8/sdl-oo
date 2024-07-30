#include <exception>
#include <utility>
#include <iostream>
#include "soo_app.h"
#include "soo_model.h"
#include "soo_command.h"
class NoOpModel:public SooModel{
    void attach(void *_){}
    int run(void *_){return 0;}
    void detach(void *_){}
} noOperation;

class SetModelCommand:public SooCommand{
private:
    SooModel **nextModel;
    SetModelCommand(SooModel **ptrModel):nextModel(ptrModel){}
public:
    virtual int execute(void *arg){
        *nextModel=static_cast<SooModel*>(arg);
        return 0;
    }
    virtual ~SetModelCommand(){
        std::cout << "释放类 SetModelCommand" << std::endl;
    }
    friend class SooApp;
};
SooApp::SooApp():
    m_mdlCurrent(&noOperation),
    m_mdlNext(nullptr),
    m_nextModelCommand(new SetModelCommand(&m_mdlNext))
    {}
SooApp::~SooApp()
{
    auto del=static_cast<SetModelCommand *>(m_nextModelCommand);
    delete del;
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
        while(!m_cmds.empty()){
            auto pa=m_cmds.front();
            m_cmds.pop();
            pa.first->execute(pa.second);
        }
        if(m_mdlCurrent->run(param)){
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
    pushCommand(m_nextModelCommand,model);
}
void SooApp::pushCommand(SooCommand *cmd,void *arg)
{
    m_cmds.push(std::make_pair(cmd,arg));
}