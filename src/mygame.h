#pragma once
#include <memory>
#include <SDL.h>
#include "soo/soo_app.h"
//#include "resources.h"
class SooWindow;
class SooRenderer;
class SooTexture;
class PngName;
class SooBrush;
class Resource;
class MyGame:public SooApp{
private:
    std::unique_ptr<SooWindow>   mWin;
    SooRenderer                 *mRender;
    std::unique_ptr<PngName>     mPngs;
    SDL_TimerID                  mTimer;
    std::unique_ptr<SDL_Rect>    m_rectMain;
    std::unique_ptr<Resource>   m_res;
    int mCount;
    void SetRandomPicture();
    bool m_outdate;

public:
    void ShowCount();
    MyGame(const char *title);
    // 已经是能够直接实例化的对象。必须把析构函数设置为公开
    virtual ~MyGame();

protected:
    void triggerEvent(SDL_Event *ev);
    void init();
    void update();

};