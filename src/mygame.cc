#include <iostream>
#include <exception>
#include <SDL_image.h>

#include "soo_surface.h"
#include "soo_exception.h"
#include "soo_window.h"
#include "soo_renderer.h"
#include "soo_texture.h"
#include "soo_brush.h"
#include "mygame.h"
#include "png_name.h"
#include "resources.h"
#define BORDER 100

const char *png_list="../png-list.txt";
void mainbox(SooRenderer *render,SDL_Rect *rect)
{
        render->SetDrawColor(0x20,0x50,0xa0,0xff);
        render->FillRect(rect);
}
#define PLAYAREA_BOARD_W   500
#define PLAYAREA_BOARD_H   60

MyGame::MyGame(const char *title)
    try:
    SooApp(SDL_INIT_VIDEO|SDL_INIT_TIMER,IMG_INIT_PNG),
    mRes(std::make_unique<Resource>()),
    m_rectMain(std::make_unique<SDL_Rect>())
    {
        mPngs = std::make_unique<PngName>(png_list);
        
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0,&dm);
        const int win_w=dm.w-BORDER * 8;
        const int win_h=dm.h-BORDER - BORDER - BORDER;
        m_rectMain->h=win_h-PLAYAREA_BOARD_H;
        m_rectMain->w=win_w-PLAYAREA_BOARD_W;
        m_rectMain->x=PLAYAREA_BOARD_W/2;
        m_rectMain->y=PLAYAREA_BOARD_H/2;
        mWin = std::make_unique<SooWindow>(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,win_w,win_h,SDL_WINDOW_SHOWN);
        mRender=mWin->CreateRenderer(-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        mRender->Clear();
    }catch(std::exception &ex){
        throw;
    }
MyGame::~MyGame(){
    std::cout << "MyGame destruction" << std::endl;
    SDL_RemoveTimer(mTimer);
    delete mRender;
}
bool MyGame::OnEvent(SDL_Event *ev)
{
    switch(ev->type){
        case SDL_KEYUP:
            switch(ev->key.keysym.sym){
            case SDLK_n:
                SetRandomPicture();
                return true;
            case SDLK_f:
                mainbox(mRender,m_rectMain.get());
                return true;
            }
        case SDL_KEYDOWN:
            ShowCount();
            mCount ++;
            return true;
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEWHEEL:
        case SDL_WINDOWEVENT:
        break;
        case SDL_DISPLAYEVENT:
            std::cout << "displayevent" << std::endl;
            break;
        default:
            std::cout << "未知の出来事" << std::endl;
    }
    return false;
}
bool MyGame::Alter()
{
    return false;
}
int MyGame::Render()
{
    mRender->Present();
    std::cout << "さん・さま・ちやん" << std::endl;
    return 0;
}



Uint32 callback(Uint32 interval,void *param)
{
    //MyGame *game=(MyGame *)param;
    if(interval <9000){
        std::cout << "时间" << interval  << "param: " << std::endl;
        if(interval >500){
            return interval - 500;
        }
    }
    
    std::cout << "过了１０秒" << std::endl;
    return 10000;
}
void MyGame::ShowCount()
{
    SDL_Rect rect={1000,20,0,0};
    int n=mCount;
    while(n){
        int m=n /10;
        int d=n  - (m *10);
        n=m;
        SooTexture *st=mRes->number[d];

        st->GetSize(&rect.w,&rect.h);
        rect.x -= rect.w;
        mRender->RenderCopy(mRes->background,&rect,&rect);
        mRender->RenderCopy(st,NULL,&rect);
        std::cout << d;
    }
    std::cout  << "=" << mCount<< std::endl;
}
void MyGame::SetRandomPicture()
{
        std::string name=mPngs->Name();
        std::cout << "文件名:" << name << std::endl;
#if 0
    try{
        //SDL_Rect rect1={0,0,300,300};
        SDL_Rect rect2={50,50,300,300};
        SooSurface *png=new SooSurface(name.c_str());
        mWin->BlitSurface(png,NULL,&rect2);
        mWin->UpdateWindowSurface();
        
        delete png;
    } catch(std::exception &e){
        throw;
    }
#else
    //SDL_Rect rect1={0,0,300,300};
    SDL_Rect rect2={50,50,0,0};
    std::unique_ptr<SooTexture> png(mRender->CreateTexture(name.c_str()));
    png->GetSize(&rect2.w,&rect2.h);
    mRender->RenderCopy(png.get(),NULL,&rect2);
    //mRender->Present();
#endif
}
int MyGame::OnInit()
{
    
    mTimer=SDL_AddTimer(3000,callback,this);
    int w,h;
    mWin->GetSize(&w,&h);
    mRes->loadTexture(mRender, w,h);
    mainbox(mRender,m_rectMain.get());
    mRes->renderMe(mRender,m_rectMain.get());
    Render();
    return 0;
}