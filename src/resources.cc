#include <iostream>
#include <SDL.h>

#include "resources.h"
#include "soo/soo_renderer.h"
#include "soo/soo_texture.h"
#include "soo/soo_exception.h"
#include "gmenu.h"
Resource::~Resource(){
    std::cout << "Resource 结束" << std::endl;
}
void pixeledit(void *pixels,int pitch,int height)
{
    uint8_t *buf=static_cast<Uint8*>(pixels);
    std::cout <<"pitch: "<< pitch << std::endl;
    for(int ix=0;ix<pitch*2;ix++){
        *(buf+ix)=ix & 0xff;
    }
}
void loadBackground(Resource *res,SooRenderer *render,int w,int h)
{
#if 0
    res->background=std::make_unique<SooTexture>(render,SDL_PIXELFORMAT_ABGR8888,SDL_TEXTUREACCESS_TARGET,w,h);
    auto textureBackground=res->background.get();
    textureBackground->setRenderTarget(render);

    render->SetDrawColor(0x0f,0x20,0x90,0xff);
    
    render->Clear();

    render->SetDrawColor(0xff,0,0,0xff);
    SDL_Rect rect={0,0,w,h};
    render->DrawRect(&rect);
    const int cd=55;
    int lx=cd;
    int ly=cd;
    render->SetDrawColor(0x4a,0x4a,0x4a,0xff);
    while(1){
        if(lx >= w){
            break;
        }
        render->DrawLine(lx,0,lx,h);
        lx += cd;
    }
    while(1){
        if(ly >= h){
            break;
        }
        render->DrawLine(0,ly,w,ly);
        ly += cd;
    }
    render->resetTarget();
#else
    SDL_Rect rt={0,0,400,200};
    res->background=std::make_unique<SooTexture>(render,SDL_PIXELFORMAT_ABGR8888,SDL_TEXTUREACCESS_STREAMING,w,h);
    res->background->modify(&rt,pixeledit);
#endif
    res->background->render(render,nullptr,nullptr);
}
Resource::Resource(SooRenderer *render,int w,int h):mainMenu(std::make_unique<MainMenu>(render,w,h))
{
    loadBackground(this,render,w,h);
}
