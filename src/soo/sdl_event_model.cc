#include "sdl_event_model.h"
#include "soo_app.h"
int SdlEventModel::run(void *param){
    SDL_Event ev;
    while(SDL_PollEvent(&ev)){
        if(ev.type==SDL_QUIT){
            m_app->quit();
            return 0;
        }
        if(onEvent(param,&ev)){
            return -1;
        }
    }
    if(present(param)){
        return -1;
    }
    
    return 0;
}
SdlEventModel::SdlEventModel(SooApp *app):SooModel(app){}