#include "soo/soo_exception.h"
#include "soo/sdl_event_model.h"
#include "soo/soo_command.h"
#include "soo/sdl_texture.h"
#include "soo/soo_app.h"
#include "game_thread_data.h"
#include "game_data.h"



void game_draw(GameData *gd);
extern SooCommand *rotate;
extern SooCommand *left;
extern SooCommand *right;
extern SooCommand *down;
extern SooCommand *nextBlock;



/// @brief 把command对象推进commands队列中
class ThreadPushCommand:public SooCommand{
private:
    SooCommand *m_cmd;
    void       *m_arg;
public:
    int execute(void *arg){
        auto app=static_cast<SooApp*>(arg);
        app->pushCommand(m_cmd,m_arg);
        return 0;
    }
    ThreadPushCommand(SooCommand *cmd,void *arg):m_cmd(cmd),m_arg(arg){}
};

int g_coloridx=0;

void game_background(int idx);
Uint32 game_forward(Uint32 interval, void *arg)
{
    auto gtd = static_cast<GameThreadData*>(arg);
    ThreadPushCommand tpc(down,nullptr);
    gtd->excuteMutex(&tpc,gtd->gameData->app);
    return gtd->gameSpeed;
}
class GameModel:public SdlEventModel{
private:
    // 保护了commands队列的数据，游戏模型(GameModel)中的数据处理都是在主线程
    // ??? 好像有问题，应该是保护读出来的时候
    GameThreadData m_threadData;
    SDL_TimerID    m_forward;
protected:
    virtual int onEvent(void *arg,SDL_Event *ev){
        auto gd=static_cast<GameData*>(arg);
        if(ev->type==SDL_KEYUP){
            switch(ev->key.keysym.sym){
                case SDLK_ESCAPE:
                m_app->setModel(gd->menu);
                break;
                case SDLK_UP:
                {
                    ThreadPushCommand tpc(rotate,nullptr);
                    m_threadData.excuteMutex(&tpc,m_app);
                }
                break;
                case SDLK_LEFT:
                {
                    ThreadPushCommand tpc(left,nullptr);
                    m_threadData.excuteMutex(&tpc,m_app);
                }
                break;
                case SDLK_RIGHT:
                {
                    ThreadPushCommand tpc(right,nullptr);
                    m_threadData.excuteMutex(&tpc,m_app);
                }
                break;
                case SDLK_DOWN:
                {
                    ThreadPushCommand tpc(down,nullptr);
                    m_threadData.excuteMutex(&tpc,m_app);
                }
                break;
                case SDLK_n:
                m_app->pushCommand(nextBlock,&m_threadData);
                break;
            }
        }
        return 0;
    }
    virtual int present(void *arg){
        auto gd=static_cast<GameData*>(arg);
        if(m_threadData.renderUpdate){
            m_threadData.renderUpdate=0;
            SDL_RenderPresent(gd->renderer);
        }
        return 0;
    }
public:
    virtual void attach(){
        g_coloridx = (g_coloridx +1) & 0xff;
        game_background(g_coloridx);
        gd->background->renderCopy(gd->renderer,nullptr,nullptr);
        game_draw(gd);
        m_threadData.gameData=gd;
        m_forward=SDL_AddTimer(1000,game_forward,&m_threadData);
        if(m_forward==0){
            throw EX(SDL_GetError());
        }
        m_threadData.renderUpdate=1;
    }
    virtual void detach(){
        SDL_RemoveTimer(m_forward);
    }
    GameModel(SooApp *app,SDL_Renderer *rend)try:SdlEventModel(app,rend){
    }catch(...){throw;}
    virtual ~GameModel(){
    }
};

SooModel *createGameModel(GameData *gd){
    return new GameModel(gd->app,gd->renderer);
}
void deleteGameModel(SooModel *obj)
{
    delete obj;
}