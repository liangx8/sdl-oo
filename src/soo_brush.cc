#include <SDL.h>
#include "soo_texture.h"
#include "soo_renderer.h"
#include "soo_brush.h"

SooBrush::SooBrush(SooRenderer *render):
    m_background(nullptr),
    m_render(render),m_rectLast(SDL_Rect{0,0,0,0}){}
void SooBrush::SetBackground(SooTexture *bg)
{
    m_background=bg;
    bg->GetSize(&m_Width,&m_Height);
}
SooBrush::~SooBrush(){}
void SooBrush::brush(SooTexture *src,SDL_Rect *srcrect,SDL_Rect *dstrect)
{
    if(m_rectLast.w){
        m_render->RenderCopy(m_background,&m_rectLast,&m_rectLast);
    }
    m_render->RenderCopy(src,srcrect,dstrect);
    m_rectLast.h=dstrect->h;
    m_rectLast.w=dstrect->w;
    m_rectLast.x=dstrect->x;
    m_rectLast.y=dstrect->y;
}
