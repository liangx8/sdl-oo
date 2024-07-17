#include <memory>
#include <SDL_ttf.h>

#include "gmenu.h"
#include "soo/soo_texture.h"
#include "soo/soo_exception.h"
#include "soo/soo_renderer.h"
#include "soo/soo_command.h"




class menuCmd:public SooCommand{
private:
    const char *m_desc;
    int m_incrment;
    int *m_menuFocus;
public:
    menuCmd(const char* desc,int incr,int *ptr):m_desc(desc),m_incrment(incr),m_menuFocus(ptr){}
    virtual const char* getDescription(){
        return m_desc;
    }
    virtual void execute(){
        int focus=*m_menuFocus+m_incrment;
        if(focus<0)return;
        if(focus>2)return;
        *m_menuFocus=focus;
    }
    ~menuCmd(){};
    friend class MainMenu;
};

const char *const fontname[]={
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

MainMenu::MainMenu(SooRenderer *render,int w,int h):m_render(render),m_focus(0)
{
    SDL_Color fg={0,0xff,0xff};
    const char* fname=fontname[9];
    TTF_Font *font=TTF_OpenFont(fname,40);
    if(font == NULL){
        throw EX(TTF_GetError());
    }

    m_menuItem[0]=new SooTexture(render,font,"开始游戏",fg);
    m_menuItem[1]=new SooTexture(render,font,"选项",fg);
    m_menuItem[2]=new SooTexture(render,font,"退出",fg);
    m_itemPos[0].y=250;
    for(int ix=0;ix<3;ix++){
        m_menuItem[ix]->GetSize(&m_itemPos[ix].w,&m_itemPos[ix].h);
        int rw=m_itemPos[ix].w;
        m_itemPos[ix].x=(w - rw)/2;
        if(ix>0){
            m_itemPos[ix].y=m_itemPos[ix-1].y+m_itemPos[ix-1].h+50;
        }
    }
    TTF_CloseFont(font);
    m_cmd=new menuCmd[2]{menuCmd("前一项菜单",-1,&m_focus),menuCmd("下一项菜单",1,&m_focus)};
}
MainMenu::~MainMenu()
{
    for(int ix=0;ix<3;ix++){
        delete m_menuItem[ix];
    }
    menuCmd *p=static_cast<menuCmd*>(m_cmd) ;
    delete [] p;
}
void MainMenu::paintAll()
{
    m_render->SetDrawColor(0x12,0x34,0x56,0x80);
    m_render->FillRect(&m_itemPos[m_focus]);
    for(int ix=0;ix<3;ix++){
        m_menuItem[ix]->render(m_render,nullptr,&m_itemPos[ix]);
    }
}
SooCommand* MainMenu::commandAt(int idx)
{
    menuCmd *p=static_cast<menuCmd*>(m_cmd) ;
    return p+idx;
}