#ifndef SOO_RENDERER_H_KQJJ3J23
#define SOO_RENDERER_H_KQJJ3J23
#include <SDL.h>
class SooWindow;
class SooRenderer{
public:
    virtual ~SooRenderer();
    void SetDrawColor(Uint8,Uint8,Uint8,Uint8);
    void Clear();
    void SetViewport(const SDL_Rect *);
    void FillRect(const SDL_Rect *rect);
    void Present()throw();
    void DrawLine(int x1,int y1,int x2,int y2);
private:
    SDL_Renderer *mRenderer;
    SooRenderer(SDL_Renderer *ren);
    friend class SooWindow;
};
#endif