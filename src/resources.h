#pragma once

class SooTexture;
class SooRenderer;
struct SDL_Rect;
class Resource{
public:
    SooTexture *background;
    SooTexture *number[10];
    SooTexture *menuItem[3];
    virtual ~Resource();

    void loadTexture(SooRenderer *,int,int);
    void renderMe(SooRenderer *render,SDL_Rect *rect);
};