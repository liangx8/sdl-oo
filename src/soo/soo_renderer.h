#pragma once

#include <SDL.h>

class SooWindow;
class SooTexture;
class SooRenderer{
public:
    virtual ~SooRenderer();
    SooRenderer(const SooRenderer &)=delete;
    void SetDrawColor(Uint8,Uint8,Uint8,Uint8);
    void Clear();
    void SetViewport(const SDL_Rect *);
    void FillRect(const SDL_Rect *rect);
    void DrawRect(const SDL_Rect *rect);
    void Present();
    void DrawLine(int x1,int y1,int x2,int y2);
    void resetTarget();
    SDL_RendererInfo* RenderInfo();
private:
    SDL_Renderer *mRenderer;
    SooRenderer(SDL_Renderer *ren);
    friend class SooWindow;
    friend class SooTexture;
};