#include <iostream>
#include <exception>
#include <SDL_image.h>

#include "soo_surface.h"
#include "soo_exception.h"
#include "soo_window.h"
#include "soo_renderer.h"
#include "mygame.h"
#include "png_name.h"
#define BORDER 100




MyGame::MyGame(const char *title)
    try:SooApp(SDL_INIT_VIDEO|SDL_INIT_TIMER,IMG_INIT_PNG)
    {
        mPngs = new PngName();
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0,&dm);
        const int win_w=dm.w-BORDER * 6;
        const int win_h=dm.h-BORDER - BORDER;
        mWin = new SooWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,win_w,win_h,SDL_WINDOW_SHOWN);
        mRender=mWin->CreateRenderer(-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }catch(std::exception &ex){
        throw;
    }
MyGame::~MyGame(){
    std::cout << "MyGame destruction" << std::endl;
    SDL_RemoveTimer(mTimer);
    delete mPngs;
    delete mRender;
    delete mWin;
}
bool MyGame::OnEvent(SDL_Event *ev)
{
    if(ev->type == SDL_KEYUP){
        if(ev->key.keysym.sym==SDLK_n){
            SetRandomPicture();
        }
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
    return 0;
}



Uint32 callback(Uint32 interval,void *param)
{
    MyGame *game=(MyGame *)param;
    if(interval <9000){
        std::cout << "时间" << interval  << "param: " << std::endl;
        if(interval >500){
            return interval - 500;
        }
    }
    
    std::cout << "计时终止" << std::endl;
    game->SetRandomPicture();
    return 10000;
}
void MyGame::SetRandomPicture()
{
    //SDL_Rect rect1={0,0,300,300};
    SDL_Rect rect2={50,50,300,300};
    try{
        std::string name=mPngs->Name();
        std::cout << "文件名:" << name << std::endl;
        SooSurface *png=new SooSurface(name.c_str());
        mWin->BlitSurface(png,NULL,&rect2);
        mWin->UpdateWindowSurface();
        delete png;
    } catch(std::exception &e){
        throw;
    }
}
int MyGame::OnInit()
{
    mTimer=SDL_AddTimer(3000,callback,this);
    SetRandomPicture();
    return 0;
}