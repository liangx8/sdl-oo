#pragma once
#include <forward_list>
#include <SDL2/SDL.h>
#include "soo_exception.h"
class SdlModel;
class SdlView;
class SdlTexture;
class SdlApplication{
private:
    SDL_Window            *m_window;
    SDL_Renderer          *m_renderer;
    SdlModel              *m_model;
    SDL_DisplayMode        m_displayMode;
    int                    m_width,m_height;
    bool                   m_update;
//    std::forward_list<SdlView *> m_flistViews;
    SdlApplication(Uint32 flag);
    void init(
        Uint32      imgFlag,
        const char *title,
        int w,
        int h,
        Uint32 winFlag);

public:
    SdlApplication(
        Uint32      flag,
        Uint32      imgFlag,
        const char *title,
        int w,
        int h,
        Uint32 winFlag);
    SdlApplication(const char *);
    void setTitle(const char *);
    void setModel(SdlModel *model);
    void run();
    void getSize(int *w,int *h) const;
    void getScreenSize(int *w,int *h) const;
    void setWindowSize(int w,int h);
    void renderView(SdlView *);

    void quit();
    virtual void init()=0;

    friend class SdlTexture;
};