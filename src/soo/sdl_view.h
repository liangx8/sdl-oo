#pragma once
#include <SDL2/SDL.h>
class SdlView{
public:
    virtual int paint(SDL_Renderer *)=0;
};
/**
 * @brief 生成一个SdlView的实例，可以由viewRelease()释放，这３个方法会共用一个vector容器，非线程安全
 * @param rect 会被拷贝内容。因此使用局部变量的引用是安全的
 */
SdlView *drawRect(SDL_Rect *rect,Uint32 color);
SdlView *fillRect(SDL_Rect *rect,Uint32 color);
void viewRelease();