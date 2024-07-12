#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
class SooWindow;
class SooTexture;
class SooRenderer{
public:
    virtual ~SooRenderer();
    void SetDrawColor(Uint8,Uint8,Uint8,Uint8);
    void Clear();
    void SetViewport(const SDL_Rect *);
    void FillRect(const SDL_Rect *rect);
    void DrawRect(const SDL_Rect *rect);
    void Present();
    void DrawLine(int x1,int y1,int x2,int y2);
    void SetRenderTarget(SooTexture *);
    /**
     * @brief Create a texture from image
     */
    SooTexture *CreateTexture(const char *image);
    SooTexture *CreateTexture(TTF_Font *,const char *,SDL_Color color);
    SooTexture *CreateTexture(Uint32 format,int access,int w,int h);
    void RenderCopy(SooTexture *,const SDL_Rect *,const SDL_Rect *);
private:
    SDL_Renderer *mRenderer;
    SooRenderer(SDL_Renderer *ren);
    friend class SooWindow;
};