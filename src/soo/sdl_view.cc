
#include <vector>
#include "soo_exception.h"
#include "sdl_view.h"
#define RGBA8888(r,g,b,a) ((a) | ((b)<<8) | ((g)<<16) | ((r)<<24))


#define RED(u32)   (((u32) >> 24) & 0xff)
#define GREEN(u32) (((u32) >> 16) & 0xff)
#define BLUE(u32)  (((u32) >> 8)  & 0xff)
#define ALPHA(u32) ((u32) & 0xff)
FillRect::FillRect(SDL_Rect *rect,Uint32 color):m_rect(rect)
{
    m_r      = RED(color);
    m_g      = GREEN(color);
    m_b      = BLUE(color);
    m_a      = ALPHA(color);
}
int FillRect::paint(SDL_Renderer *ren)
{
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(ren,m_r,m_g,m_b,m_a))
    THROW_SDL_NOT_ZERO(SDL_RenderFillRect(ren,m_rect))
    return 0;
}

DrawRect::DrawRect(SDL_Rect *rect,Uint32 color):m_rect(rect)
{
    m_r      = RED(color);
    m_g      = GREEN(color);
    m_b      = BLUE(color);
    m_a      = ALPHA(color);
}
int DrawRect::paint(SDL_Renderer *ren)
{
    THROW_SDL_NOT_ZERO(SDL_SetRenderDrawColor(ren,m_r,m_g,m_b,m_a))
    THROW_SDL_NOT_ZERO(SDL_RenderDrawRect(ren,m_rect))
    return 0;
}