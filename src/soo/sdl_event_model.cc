#include "sdl_event_model.h"

int SdlEventModel::run(void *param){
    SDL_Event ev;
    int cnt=0;
    while(SDL_PollEvent(&ev)){
        if(ev.type==SDL_QUIT){
            return -1;
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
