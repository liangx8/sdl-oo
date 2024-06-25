#include <iostream>
#include <SDL_image.h>
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
}
SooApp::SooApp(Uint32 flag):mMode(0)
{
    if(SDL_Init(flag)){
        throw EX(SDL_GetError());
    }
}
SooApp::~SooApp()
{
    std::cout << "SooApp destruction" << std::endl;
    if(mMode==1){
        IMG_Quit();
    }
    SDL_Quit();
}
void SooApp::Poll(){
    bool run=true;
    SDL_Event ev;
    OnInit();
    while(run){
        bool update;
        while(SDL_PollEvent(&ev)){
            if(ev.type==SDL_QUIT){
                run = false;
            }
            update=OnEvent(&ev);
        }
        update=Alter();
        if(update){
            Render();
        }
    }
}
int SooApp::RunAt(Uint32,int (*run)(void *)){
    return 0;
}