#include "resources.h"
#include "soo_renderer.h"
#include "soo_texture.h"
#include "soo_exception.h"
Resource::~Resource()
{
    delete background;
    for(int ix=0;ix<10;ix++){
        delete number[ix];
    }
    for(int ix=0;ix<3;ix++){
        delete menuItem[ix];
    }
}

SooTexture *loadBackground(SooRenderer *render,int w,int h)
{
    auto textrueBackground=render->CreateTexture(SDL_PIXELFORMAT_ABGR8888,SDL_TEXTUREACCESS_TARGET,w,h);
    render->SetRenderTarget(textrueBackground);

    render->SetDrawColor(0x0f,0x0f,0x0f,0);
    
    render->Clear();

    render->SetDrawColor(0xff,0,0,0xff);
    SDL_Rect rect={0,0,w,h};
    render->DrawRect(&rect);
    const int cd=55;
    int lx=cd;
    int ly=cd;
    render->SetDrawColor(0x4a,0x4a,0x4a,0xff);
    while(1){
        if(lx >= w){
            break;
        }
        render->DrawLine(lx,0,lx,h);
        lx += cd;
    }
    while(1){
        if(ly >= h){
            break;
        }
        render->DrawLine(0,ly,w,ly);
        ly += cd;
    }
    render->SetRenderTarget(nullptr);
    render->RenderCopy(textrueBackground,nullptr,nullptr);
    return textrueBackground;
}
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
void loadText(Resource *res,SooRenderer *render)
{
    const char* fname=fontname[9];
    TTF_Font *font=TTF_OpenFont(fname,40);
    if(font == NULL){
        throw EX(TTF_GetError());
    }
    
//    std::string tn(fname.c_str());
//    tn += " 字体";
//    SooSurface text(font,tn.c_str());

//    text.SetColorKey(SDL_TRUE,0xffffff);
//    mWin->BlitSurface(&text,NULL,NULL);
//    mWin->UpdateWindowSurface();
    char numstr[2];
    numstr[1]='\0';
    SDL_Color fg={0,0xff,0xff};
    int w,h;
    for(int ix=0;ix<10;ix++){
        numstr[0]='0'+ix;
        res->number[ix]=render->CreateTexture(font,&numstr[0],fg);
        res->number[ix]->GetSize(&w,&h);
        res->number[ix]->SetAlphaMod(128);
    }
    res->menuItem[0]=render->CreateTexture(font,"开始游戏",fg);
    res->menuItem[1]=render->CreateTexture(font,"选项",fg);
    res->menuItem[2]=render->CreateTexture(font,"退出",fg);
    TTF_CloseFont(font);

}
void Resource::loadTexture(SooRenderer *render,int w,int h)
{
    
    background=loadBackground(render,w,h);
    loadText(this,render);
}
void Resource::renderMe(SooRenderer *render,SDL_Rect *rect)
{
    SDL_Rect center;
    center.y=240;
    for(int ix=0;ix<3;ix++){

        menuItem[ix]->GetSize(&center.w,&center.h);
        center.x=rect->x+(rect->w-center.w)/2;
        render->RenderCopy(menuItem[ix],nullptr,&center);
        center.y += 40 + center.h;
    }
}