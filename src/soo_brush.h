#pragma once
class SooRenderer;
class SooTexture;
struct SDL_Rect;

class SooBrush{
private:
    SooTexture                *m_background;
    SooRenderer               *m_render;
    SDL_Rect                  m_rectLast;
    int                       m_Width;
    int                       m_Height;
public:
    SooBrush(SooRenderer *render);
    virtual ~SooBrush();
    void SetBackground(SooTexture *bg);
    void brush(SooTexture *src,SDL_Rect *srcrect,SDL_Rect *dstrect);
};