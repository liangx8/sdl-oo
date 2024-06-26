#ifndef MYGAME_H
#define MYGAME_H
#include "soo_app.h"
class SooWindow;
class SooRenderer;
class PngName;
class MyGame:public SooApp{
private:
    SooWindow   *mWin;
    SooRenderer *mRender;
    PngName     *mPngs;
    SDL_TimerID  mTimer;
public:
    void SetRandomPicture();
    MyGame(const char *title);
    // 已经是能够直接实例化的对象。必须把析构函数设置为公开
    virtual ~MyGame();

protected:
    bool OnEvent(SDL_Event *ev);
    bool Alter();
    int Render();
    int OnInit();

};
#endif