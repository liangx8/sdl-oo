#include <vector>
#include "soo_exception.h"
#include "sdl_view.h"
#define RGBA8888(r,g,b,a) ((a) | ((b)<<8) | ((g)<<16) | ((r)<<24))


#define RED(u32)   (((u32) >> 24) & 0xff)
#define GREEN(u32) (((u32) >> 16) & 0xff)
#define BLUE(u32)  (((u32) >> 8)  & 0xff)
#define ALPHA(u32) ((u32) & 0xff)
class viewFillOrDrawRect:public SdlView{
public:
    SDL_Rect m_rect;
    Uint8 m_r,m_g,m_b,m_a;
    bool m_doDraw;
    bool m_occupy;
    void setProperties(SDL_Rect *rect,Uint32 color,bool fillDraw){
        memcpy(&m_rect,rect,sizeof(SDL_Rect));
        // m_rect.x = rect->x;
        // m_rect.y = rect->y;
        // m_rect.w = rect->w;
        // m_rect.h = rect->h;
        m_r      = RED(color);
        m_g      = GREEN(color);
        m_b      = BLUE(color);
        m_a      = ALPHA(color);
        m_occupy = true;
        m_doDraw = fillDraw;
    }
    int paint(SDL_Renderer *ren){
        THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(ren,m_r,m_g,m_b,m_a))
        if(m_doDraw){
            THROW_SDL_NOT_ZERO(SDL_RenderDrawRect(ren,&m_rect))
        } else {
            THROW_SDL_NOT_ZERO(SDL_RenderFillRect(ren,&m_rect))
        }
        m_occupy = false;
        return 0;
    }
    virtual ~viewFillOrDrawRect(){}
};

std::vector<viewFillOrDrawRect*> g_vecPool;

SdlView *drawRect(SDL_Rect *rect,Uint32 color){
    for (auto viewPtr:g_vecPool){
        if(viewPtr->m_occupy){
            continue;
        }
        viewPtr->setProperties(rect,color,true);
        return viewPtr;
    }
    auto view = new viewFillOrDrawRect();
    
    view->setProperties(rect,color,true);
    g_vecPool.push_back(view);
    SDL_Log("新建view");
    return view;
}
SdlView *fillRect(SDL_Rect *rect,Uint32 color){
    for (auto viewPtr:g_vecPool){
        if(viewPtr->m_occupy){
            continue;
        }
        viewPtr->setProperties(rect,color,false);
        return viewPtr;
    }
    auto view = new viewFillOrDrawRect();
    view->setProperties(rect,color,false);
    g_vecPool.push_back(view);
    SDL_Log("新建view");
    return view;
}
void viewRelease(){
    for (auto viewPtr:g_vecPool){
        delete viewPtr;
    }
}