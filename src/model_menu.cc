#include <memory>
#include "soo/sdl_model.h"
#include "soo/sdl_app.h"
#include "soo/sdl_texture.h"
#include "soo/sdl_view.h"
#include "game_data.h"
#define ITEM_COUNT 4


class MenuView:public SdlView{
public:
    SdlTexture *textureMenuStr;
    SDL_Rect range[ITEM_COUNT*2];
    int menuSel,oldMenuSel;
    int win_w,win_h;
    virtual int paint(SDL_Renderer *ren){
        GameData *gd=GameData::getInstance();
        gd->background->renderCopy(ren,nullptr,nullptr);
        for (int ix=0;ix<ITEM_COUNT;ix++){
            SDL_Rect *src=&range[ix];
            SDL_Rect *dst=&range[ix+ITEM_COUNT];
            textureMenuStr->renderCopy(ren,src,dst);
        }
        return 0;
    }
};
#define MENU_WIDTH 600
void deselect(MenuView *mv,int sel,SDL_Renderer *ren)
{
    SDL_Rect *sr=&mv->range[sel+ITEM_COUNT];
    GameData *gd=GameData::getInstance();
    const int x1=(mv->win_w-MENU_WIDTH)/2;
    const int y1=sr->y-2;
    const int x2=x1+MENU_WIDTH-1;
    const int y2=y1 + sr->h+4-1;
    SDL_Rect dst={x1,y1,MENU_WIDTH,1};
    gd->background->renderCopy(ren,&dst,&dst);
    dst.w=1;
    dst.h=sr->h+4;
    gd->background->renderCopy(ren,&dst,&dst);
    dst.y=y2;
    dst.w=MENU_WIDTH;
    dst.h=1;
    gd->background->renderCopy(ren,&dst,&dst);
    dst.x=x2;
    dst.w=1;
    dst.y=y1;
    dst.h=sr->h+4;
    gd->background->renderCopy(ren,&dst,&dst);
}

class FocusMenuView:public SdlView{
public:
    MenuView m_menu;
    virtual int paint(SDL_Renderer *ren){
        SDL_SetRenderDrawColor(ren,0xf7,0xbe,0x05,0xff);
        SDL_Rect *sr=&m_menu.range[m_menu.menuSel + ITEM_COUNT];
        SDL_Rect rct={(m_menu.win_w-MENU_WIDTH)/2,sr->y-2,MENU_WIDTH,sr->h+4};
        THROW_SDL_NOT_ZERO(SDL_RenderDrawRect(ren,&rct));
        if(m_menu.menuSel != m_menu.oldMenuSel){
            //SDL_Log("wipe out old rect %d/%d",m_menu.menuSel,m_menu.oldMenuSel);
            deselect(&m_menu,m_menu.oldMenuSel,ren);
            m_menu.oldMenuSel=m_menu.menuSel;
        }
        return 0;
    }
};


class ModelMenu:public SdlModel{
private:
    ModelMenu(SdlApplication *);
    FocusMenuView m_focus;
    int focusUpdate;
public:
    ModelMenu(const ModelMenu &)=delete;
    virtual void attach(SdlApplication *);
    virtual void onEvent(SDL_Event *,SdlApplication *);
    virtual void present(SdlApplication *);
    virtual void detach(SdlApplication *);

    virtual ~ModelMenu();
    friend void initMenu(SdlApplication *);
};
static std::unique_ptr<ModelMenu> instancePtr;


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
const int rng[]=    {        4,      8,  10,   13};

class InitMenuView:public SdlView{
    /*这个对象只需要被执行１次 */
public:
    MenuView *menuView;
    SdlApplication *app;
    virtual int paint(SDL_Renderer *ren){
        SDL_Log("initializing Menu ...");
        SDL_Color co={0xf0,0xa8,0xe0};
        TTF_Font *font=TTF_OpenFont(fontname[11],60);
        THROW_SDL_NULL(font)
        menuView->textureMenuStr=new SdlTexture(ren,font,menustr,&co);
        THROW_SDL_NULL(menuView->textureMenuStr)
        int width,height;
        int win_w,win_h;
        app->getSize(&win_w,&win_h);
        menuView->win_w=win_w;
        menuView->win_h=win_h;
        menuView->textureMenuStr->getSize(&width,&height);
        width=width/rng[3];
        int st=0;
        int y=190;
        for (int ix=0;ix<ITEM_COUNT;ix++){
            menuView->range[ix].x=st*width;
            menuView->range[ix].y=0;
            menuView->range[ix].w=(rng[ix]-st) *width;
            menuView->range[ix].h=height;
            st=rng[ix];
            SDL_Rect *src=&menuView->range[ix];
            int x=(win_w-src->w)/2;
            menuView->range[ix+ITEM_COUNT].x=x;
            menuView->range[ix+ITEM_COUNT].y=y;
            menuView->range[ix+ITEM_COUNT].w=src->w;
            menuView->range[ix+ITEM_COUNT].h=src->h;
            y += 55 + src->h;        
        }
        menuView->menuSel=0;
        menuView->oldMenuSel=0;
        TTF_CloseFont(font);
        return 0;
    }
};


ModelMenu::ModelMenu(SdlApplication *app)
{

    InitMenuView imv;
    imv.menuView= &m_focus.m_menu;
    imv.app=app;
    app->initRenderView(&imv);
    focusUpdate=0;
}
ModelMenu::~ModelMenu(){
    SDL_Log("destory resources of Menu ...");
    delete m_focus.m_menu.textureMenuStr;
}
void ModelMenu::attach(SdlApplication *app)
{
    app->pushSdlView(&m_focus);
    app->pushSdlView(&m_focus.m_menu);
}
void ModelMenu::onEvent(SDL_Event *ev,SdlApplication *app)
{
    if(ev->type==SDL_KEYUP){
        switch(ev->key.keysym.sym){
            case SDLK_UP:
            {
                int sel=m_focus.m_menu.menuSel;
                if(sel==0){
                    m_focus.m_menu.menuSel=ITEM_COUNT-1;
                } else {
                    m_focus.m_menu.menuSel=sel-1;
                }
                focusUpdate=1;
            }
            break;
            case SDLK_DOWN:
            {
                int sel=m_focus.m_menu.menuSel;
                if(sel==ITEM_COUNT-1){
                    m_focus.m_menu.menuSel=0;
                } else {
                    m_focus.m_menu.menuSel=sel+1;
                }
                focusUpdate=1;
            }
            break;
            case SDLK_RETURN:
            {

                GameData *gd=GameData::getInstance();
                if(m_focus.m_menu.menuSel==3){
                    app->quit();
                }
                if(m_focus.m_menu.menuSel==0){
                    app->setModel(gd->game);
                }
            }
            break;
        }
    }
}
void ModelMenu::present(SdlApplication *app)
{
    if(focusUpdate){
        app->pushSdlView(&m_focus);
        focusUpdate=0;

    }
}
void ModelMenu::detach(SdlApplication *render)
{
}
void initMenu(SdlApplication *app){
    instancePtr=std::unique_ptr<ModelMenu>(new ModelMenu(app));
    
}
SdlModel *getMenu()
{
    return instancePtr.get();
}
