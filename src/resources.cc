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

void loadBackground(Resource *res,SooRenderer *render,int w,int h)
{
    
    res->background=std::make_unique<SooTexture>(render,SDL_PIXELFORMAT_ABGR8888,SDL_TEXTUREACCESS_TARGET,w,h);
    auto textrueBackground=res->background.get();
    textrueBackground->setRenderTarget(render);

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
    textrueBackground->render(render,nullptr,nullptr);
}
Resource::Resource(SooRenderer *render,int w,int h):mainMenu(std::make_unique<MainMenu>(render,w,h))
{
    loadBackground(this,render,w,h);
}
