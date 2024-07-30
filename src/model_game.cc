#include "soo/soo_exception.h"
#include "soo/sdl_event_model.h"
#include "soo/soo_command.h"
#include "soo/sdl_texture.h"
#include "game_data.h"

class GameModel:public SdlEventModel{
private:
    int update;
protected:
    virtual int onEvent(void *arg,SDL_Event *ev){
        auto gd=static_cast<GameData*>(arg);
        if(ev->type==SDL_KEYUP && ev->key.keysym.sym== SDLK_ESCAPE){
            return gd->setModel->execute(gd->menu);
        }
        return 0;
    }
    virtual int present(void *arg){
        auto gd=static_cast<GameData*>(arg);
        if(update)        {
            update=0;
            SDL_RenderPresent(gd->renderer);
        }
        return 0;
    }
public:
    virtual void attach(void *arg){
        auto gd=static_cast<GameData*>(arg);
        gd->background->renderCopy(gd->renderer,nullptr,nullptr);
        update=1;
    }
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