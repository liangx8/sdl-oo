#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "sdl_app.h"
#include "sdl_model.h"
#include "sdl_view.h"
#include "soo_command.h"
SdlApplication::SdlApplication(Uint32 flag)
{
    THROW_SDL_NOT_ZERO(SDL_Init(flag | SDL_INIT_JOYSTICK))
}
#define DEFAULT_BORDER_WIDTH 100
SdlApplication::SdlApplication(
        Uint32      flag,
        Uint32      imgFlag,
        const char *title,
        int w,
        int h,
        Uint32 winFlag):SdlApplication(flag)
{
    init(imgFlag,title,w,h,winFlag);
}
void SdlApplication::init(Uint32 imgFlag,const char *title,int w,int h,Uint32 winFlag)
{
    if(TTF_Init()){
        SDL_Quit();
        throw EX(TTF_GetError());
    }
    if(imgFlag){
        if(!(IMG_Init(imgFlag) & imgFlag)){
            TTF_Quit();
            SDL_Quit();
            throw EX(IMG_GetError());
        }
    }
    int num;
    if((num=SDL_NumJoysticks())<1){
        SDL_LogWarn(0,"没发现手柄");
    } else {
        SDL_Log("检测到%d个手柄",num);
    }

    THROW_SDL_NOT_ZERO(SDL_CreateWindowAndRenderer(w,h,0,&m_window,&m_renderer))
    m_width=w;
    m_height=h;
    setTitle(title);
}
SdlApplication::SdlApplication(const char *title):SdlApplication(SDL_INIT_VIDEO | SDL_INIT_TIMER){
    SDL_DisplayMode dm;
    THROW_SDL_NOT_ZERO(SDL_GetCurrentDisplayMode(0,&dm))
    const int win_w=dm.w - DEFAULT_BORDER_WIDTH * 4;
    const int win_h=dm.h - DEFAULT_BORDER_WIDTH - DEFAULT_BORDER_WIDTH;
    init(IMG_INIT_PNG,title,win_w,win_h,SDL_WINDOW_SHOWN);
}
void SdlApplication::setTitle(const char *title){
    SDL_SetWindowTitle(m_window,title);
}
void SdlApplication::setModel(SdlModel *model)
{
    m_model->detach(this);
    model->attach(this);
    m_model=model;
}

class NoOpView:public SdlView{
public:
    virtual int paint(SDL_Renderer *){
        return 0;
    }
};
static NoOpView noNoView;
class NoOpModel:public SdlModel{
    virtual void attach(SdlApplication *){};
    virtual void onEvent(SDL_Event *,SdlApplication *){};
    virtual void present(SdlApplication *){};
    virtual void detach(SdlApplication *){};
};
static NoOpModel noOpModel;
class QuitCommand:public SooCommand{
public:
    int *m_isRun;
    QuitCommand():m_isRun(nullptr){}
    virtual int execute(void *){
        if(m_isRun){
            *m_isRun=0;
        }
        return 0;
    }
};
QuitCommand quitCommand;
void SdlApplication::run()
{
    SDL_Event event;
    m_model=&noOpModel;
    int isRun=1;
    quitCommand.m_isRun=&isRun;
    init();
    while(isRun){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                m_model->detach(this);
                isRun=0;
            }
            m_model->onEvent(&event,this);
        }
        m_model->present(this);
        int update=0;
        for(auto vws:m_flistViews){
            update=1;
            vws->paint(m_renderer);
        }
        if(update){
            m_flistViews.clear();
            SDL_RenderPresent(m_renderer);
        }
    }
    quitCommand.m_isRun=nullptr;
    viewRelease();
    TTF_Quit();
    SDL_Quit();
}
void  SdlApplication::quit(){
    quitCommand.execute(nullptr);
}
void SdlApplication::getSize(int *w,int *h) const
{
    *w=m_width;
    *h=m_height;
}
void SdlApplication::pushSdlView(SdlView *view){
    m_flistViews.push_front(view);
}
void SdlApplication::initRenderView(SdlView *view)
{
    view->paint(m_renderer);
}