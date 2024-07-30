#include <SDL2/SDL_ttf.h>
#include "soo/soo_exception.h"
#include "soo/sdl_event_model.h"
#include "soo/sdl_texture.h"
#include "game_data.h"
#include "soo/soo_command.h"
#define ITEM_COUNT 4
#define MENU_WIDTH 600

class MenuModel:public SdlEventModel{
private:
    SdlTexture *menutext;
    SDL_Rect   range[ITEM_COUNT*2];
    int menuSel;
    int update;
    virtual int onEvent(void *args,SDL_Event *ev){
        auto gd=static_cast<GameData*>(args);
        if(ev->type == SDL_KEYUP){
            switch (ev->key.keysym.sym){
                case SDLK_UP:
                {
                    int sel=menuSel-1;
                    if(sel == -1){
                        sel=ITEM_COUNT -1;
                    }
                    focusShow(gd,sel);
                    break;
                }

                case SDLK_DOWN:
                {
                    int sel=menuSel+1;
                    if (sel == ITEM_COUNT){
                        sel=0;
                    }
                    focusShow(gd,sel);
                    break;
                }
                case SDLK_RETURN:
                    switch(menuSel){
                        case 0:
                        case 1:
                        case 2:
                        break;
                        case 3:
                        return -1;
                    }
                    break;
            }
            //gd->setModel->execute(gd->game);
        }
        return 0;
    }
    virtual int present(void *args)
    {

        if(update){
            auto gd=static_cast<GameData*>(args);
            SDL_RenderPresent(gd->renderer);
            update=0;
        }
        return 0;
    }
    void focusShow(GameData *gd,int select)
    {
        SDL_SetRenderDrawColor(gd->renderer,0xf7,0xbe,0x05,0xff);
        SDL_Rect *sr=&range[select+ITEM_COUNT];
        SDL_Rect rect={(gd->win_w-MENU_WIDTH)/2,sr->y-2,MENU_WIDTH,sr->h+4};

        if(SDL_RenderDrawRect(gd->renderer,&rect)){
            throw EX(SDL_GetError());
        }
        if(select!=menuSel){
            SDL_Rect *sr=&range[menuSel+ITEM_COUNT];
            const int x1=(gd->win_w-MENU_WIDTH)/2;
            const int y1=sr->y-2;
            const int x2=x1+MENU_WIDTH-1;
            const int y2=y1 + sr->h+4-1;
            SDL_Rect dst={x1,y1,MENU_WIDTH,1};
            gd->background->renderCopy(gd->renderer,&dst,&dst);
            dst.w=1;
            dst.h=sr->h+4;
            gd->background->renderCopy(gd->renderer,&dst,&dst);
            dst.y=y2;
            dst.w=MENU_WIDTH;
            dst.h=1;
            gd->background->renderCopy(gd->renderer,&dst,&dst);
            dst.x=x2;
            dst.w=1;
            dst.y=y1;
            dst.h=sr->h+4;
            gd->background->renderCopy(gd->renderer,&dst,&dst);
        }
        menuSel=select;
        update=1;
    }
public:
    virtual void attach(void *args){
        auto gd=static_cast<GameData*>(args);
        for(int ix=0;ix<ITEM_COUNT;ix++){
            SDL_Rect *src=&range[ix];
            SDL_Rect *dst=&range[ix+ITEM_COUNT];
            menutext->renderCopy(gd->renderer,src,dst);
        }
        focusShow(gd,0);
        update=1;
    }
    // virtual int execute(void *args){
    //     return SdlEventModel::execute(args);
    // }
    virtual void detach(void *args){}
    virtual ~MenuModel(){}
    friend SooModel *createMenuModel(SDL_Renderer *render,int win_w);
};


const char *const fontname[]={
"/usr/share/fonts/gnu-free/FreeMono.otf",
"/usr/share/fonts/gnu-free/FreeMonoOblique.otf",
"/usr/share/fonts/gnu-free/FreeMonoBold.otf",
"/usr/share/fonts/gnu-free/FreeMonoBoldOblique.otf",
"/usr/share/feh/fonts/yudit.ttf",
"/usr/share/ppsspp/assets/Roboto-Condensed.ttf",
"/usr/share/vlc/skins2/fonts/FreeSansBold.ttf",
"/usr/share/vlc/skins2/fonts/FreeSans.ttf",
"/usr/share/fonts/noto-cjk/NotoSansCJK-Light.ttc",
"/usr/share/fonts/noto-cjk/NotoSerifCJK-ExtraLight.ttc",
"/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc",
"/usr/share/fonts/noto-cjk/NotoSerifCJK-Bold.ttc",
"/usr/share/fonts/noto-cjk/NotoSansCJK-Bold.ttc",
"/usr/share/fonts/noto-cjk/NotoSerifCJK-Regular.ttc",
"/usr/share/fonts/noto-cjk/NotoSerifCJK-Black.ttc",
"/usr/share/fonts/noto-cjk/NotoSansCJK-DemiLight.ttc",
"/usr/share/fonts/noto-cjk/NotoSansCJK-Thin.ttc",
"/usr/share/fonts/noto-cjk/NotoSerifCJK-Light.ttc",
"/usr/share/fonts/noto-cjk/NotoSerifCJK-Medium.ttc",
"/usr/share/fonts/noto-cjk/NotoSerifCJK-SemiBold.ttc",
"/usr/share/fonts/noto-cjk/NotoSansCJK-Medium.ttc",
"/usr/share/fonts/noto-cjk/NotoSansCJK-Black.ttc",
"/usr/share/imlib2/data/fonts/notepad.ttf",
"/usr/share/imlib2/data/fonts/cinema.ttf",
"/usr/share/imlib2/data/fonts/morpheus.ttf"
};

const char *menustr="开始游戏按键控制难度玩腻了";
const int rng[]={            4,      8,  10,   13};
#define CHAR_COUNT 13


SooModel *createMenuModel(SDL_Renderer *render,int win_w)
{
    MenuModel *mm=new MenuModel();
    SDL_Color c={0xf3,0xb8,0xf0};
    TTF_Font *font=TTF_OpenFont(fontname[10],56);
    if(font==NULL){
        throw EX(TTF_GetError());
    }
    
    auto tx=new SdlTexture(render,font,menustr,&c);
    int w,h;
    tx->getSize(&w,&h);
    w=w/CHAR_COUNT;
    int st=0;
    int y=150;
    for(int ix=0;ix<ITEM_COUNT;ix++){
        mm->range[ix].x=st*w;
        mm->range[ix].y=0;
        mm->range[ix].w=(rng[ix]-st) *w;
        mm->range[ix].h=h;
        st=rng[ix];
        SDL_Rect *src=&mm->range[ix];
        int x=(win_w-src->w)/2;
        mm->range[ix+ITEM_COUNT].x=x;
        mm->range[ix+ITEM_COUNT].y=y;
        mm->range[ix+ITEM_COUNT].w=src->w;
        mm->range[ix+ITEM_COUNT].h=src->h;
        y += 55 + src->h;
    }
    mm->menuSel=0;
    
    // for(int ix=0;ix<5;ix++){
    //     SDL_Log("range:{%d,%d,%d,%d}",res->range[ix].x,res->range[ix].y,res->range[ix].w,res->range[ix].h);
    // }
    mm->menutext=tx;
    mm->update=1;
    TTF_CloseFont(font);
    return mm;
}
void deleteMenuModel(SooModel *model)
{
    delete (MenuModel *)model;
}