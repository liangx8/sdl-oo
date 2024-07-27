#include <SDL2/SDL_ttf.h>
#include "soo/soo_exception.h"
#include "soo/sdl_event_model.h"
#include "soo/sdl_texture.h"
#define ITEM_COUNT 4

class MenuModel:public SdlEventModel{
private:
    SdlTexture *menutext;
    SDL_Rect   range[ITEM_COUNT*2];
    int menuSel,oldMenuSel;
    virtual int onEvent(SDL_Event *){return 0;}
    virtual int present(){return 0;}
public:
    virtual void attach(void *args){}
    virtual int execute(void *args){
        return SdlEventModel::execute(args);
    }
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
MenuModel* loadMenu(SDL_Renderer *render,int win_w)
{
    return 0;
}



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
    mm->oldMenuSel=0;
    
    // for(int ix=0;ix<5;ix++){
    //     SDL_Log("range:{%d,%d,%d,%d}",res->range[ix].x,res->range[ix].y,res->range[ix].w,res->range[ix].h);
    // }
    mm->menutext=tx;
    TTF_CloseFont(font);
    return mm;
}
void deleteMenuModel(SooModel *model)
{
    delete (MenuModel *)model;
}