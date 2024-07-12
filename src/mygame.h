#pragma once
#include <memory>
#include "soo_app.h"
class SooWindow;
class SooRenderer;
class SooTexture;
class PngName;
class SooBrush;
class Resource;
struct SDL_Rect;
class MyGame:public SooApp{
private:
    std::unique_ptr<SooWindow>   mWin;
    SooRenderer                 *mRender;
    std::unique_ptr<PngName>     mPngs;
    SDL_TimerID                  mTimer;
    std::unique_ptr<Resource>    mRes;
    std::unique_ptr<SDL_Rect>    m_rectMain;
    int mCount;
    void SetRandomPicture();
public:
    void ShowCount();
    MyGame(const char *title);
    // 已经是能够直接实例化的对象。必须把析构函数设置为公开
    virtual ~MyGame();

protected:
    bool OnEvent(SDL_Event *ev);
    bool Alter();
    int Render();
    int OnInit();

};