#include "soo/soo_exception.h"
#include "soo/sdl_event_model.h"

class GameModel:public SdlEventModel{
protected:
    virtual int onEvent(void *,SDL_Event *){return 0;}
    virtual int present(void *){return 0;}
public:
    virtual void attach(void *){}
    virtual void detach(void *){}
    virtual ~GameModel(){}
};

SooModel *createGameModel(SDL_Renderer *){
    return new GameModel();
}
void deleteGameModel(SooModel *obj)
{
    delete (GameModel *)obj;
}