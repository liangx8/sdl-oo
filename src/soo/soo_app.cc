#include <exception>
#include <utility>
#include <iostream>
#include "soo_app.h"
#include "soo_model.h"
#include "soo_command.h"
class NoOpModel:public SooModel{
public:
    void attach(){}
    int run(void *_){return 0;}
    void detach(){}
    NoOpModel():SooModel(nullptr){}
} noOperation;

class QuitCommand:public SooCommand{
private:
    int *run;
public:
    int execute(void *){
        *run=0;
        return 0;
    }
    QuitCommand(int *ptr):run(ptr){}
};


SooApp::SooApp():
    m_model(&noOperation),
    m_quitCommand(new QuitCommand(&m_isRun)),
    m_isRun(1){}
SooApp::~SooApp()
{
    delete (QuitCommand *)m_quitCommand;
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
    while(m_isRun){
        while(!m_cmds.empty()){
            auto pa=m_cmds.front();
            m_cmds.pop();
            pa.first->execute(pa.second);
        }
        m_model->run(param);
    }
    if((res=release(param))!=0){
        return res;
    }
    return res;
}
void SooApp::setModel(SooModel *model)
{
    // FIXME:模型切换的步骤应该在这里实现
    m_model->detach();
    model->attach();
    m_model=model;
}
void SooApp::pushCommand(SooCommand *cmd,void *arg)
{
    m_cmds.push(std::make_pair(cmd,arg));
}
void SooApp::quit()
{
    m_isRun=0;
}