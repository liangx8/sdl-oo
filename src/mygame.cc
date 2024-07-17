#include <iostream>
#include <exception>
#include <SDL_image.h>

#include "soo/soo_surface.h"
#include "soo/soo_exception.h"
#include "soo/soo_window.h"
#include "soo/soo_renderer.h"
#include "soo/soo_texture.h"
#include "soo/soo_command.h"
#include "gmenu.h"
#include "resources.h"
#include "mygame.h"
#include "png_name.h"
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
    m_rectMain(std::make_unique<SDL_Rect>()),
    m_outdate(false)
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
        std::cout << "width1: " << win_w << ", height1:" << win_h << std::endl;
        mWin = std::make_unique<SooWindow>(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,win_w,win_h,SDL_WINDOW_SHOWN);

        mRender=mWin->CreateRenderer(-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        mRender->Clear();
        SDL_RendererInfo *info=mRender->RenderInfo();
        std::cout << "render driver name: " <<info->name << std::endl;
        delete info;
    }catch(std::exception &ex){
        throw;
    }
MyGame::~MyGame(){
    std::cout << "MyGame destruction" << std::endl;
    SDL_RemoveTimer(mTimer);
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
    //SDL_Rect rect={1000,20,0,0};
    int n=mCount;
    while(n){
        int m=n /10;
        int d=n  - (m *10);
        n=m;
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
    std::unique_ptr<SooTexture> png=std::make_unique<SooTexture>(mRender, name.c_str());
    png->GetSize(&rect2.w,&rect2.h);
    png->render(mRender,NULL,&rect2);
    //mRender->Present();
#endif
}
void MyGame::init()
{
    
    mTimer=SDL_AddTimer(3000,callback,this);
    int w,h;
    mWin->GetSize(&w,&h);
    std::cout << "width: " << w << ", height:" << h << std::endl;
    m_res=std::make_unique<Resource>(mRender,w,h);
    //mainbox(mRender,m_rectMain.get());
    m_res->mainMenu->paintAll();
    std::cout << m_res->mainMenu->commandAt(0)->getDescription() << std::endl;
    std::cout << m_res->mainMenu->commandAt(1)->getDescription() << std::endl;
    m_outdate=true;
}
void MyGame::triggerEvent(SDL_Event *ev)
{

}
void MyGame::update()
{
    if(m_outdate){
        mRender->Present();
        m_outdate=false;
    }
}