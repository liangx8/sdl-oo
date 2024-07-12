#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "soo_app.h"
#include "soo_exception.h"
SooApp::SooApp(Uint32 sdlf,Uint32 imgf):mMode(1)
{
    if(SDL_Init(sdlf)){
        throw EX(SDL_GetError());
    }
    if(!(IMG_Init(imgf) & imgf)){
        SDL_Quit();
        throw EX(IMG_GetError());
    }
    if(TTF_Init() == -1){
        IMG_Quit();
        SDL_Quit();
        throw EX(TTF_GetError());
    }
}
SooApp::SooApp(Uint32 flag):mMode(0)
{
    if(SDL_Init(flag)){
        throw EX(SDL_GetError());
    }
    if(TTF_Init()==-1){
        SDL_Quit();
        throw EX(TTF_GetError());
    }
}
SooApp::~SooApp()
{
    std::cout << "SooApp destruction" << std::endl;
    if(mMode==1){
        IMG_Quit();
    }
    TTF_Quit();
    SDL_Quit();
}
void SooApp::Run(){
    bool run=true;
    SDL_Event ev;
    OnInit();
    while(run){
        bool update=false;
        while(SDL_PollEvent(&ev)){
            if(ev.type==SDL_QUIT){
                run = false;
            }
            if(OnEvent(&ev)){
                update=true;
            }
        }
        if(Alter()){
            update=true;
        }
        if(update){
            Render();
        }
    }
}