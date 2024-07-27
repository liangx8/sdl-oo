#include "sdl_event_model.h"

int SdlEventModel::execute(void *param){
    SDL_Event ev;
    while(SDL_PollEvent(&ev)){
        if(ev.type==SDL_QUIT){
            return -1;
        }
        if(onEvent(&ev)){
            return -1;
        }
    }
    if(present()){
        return -1;
    }
    return 0;
}
