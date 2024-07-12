#pragma once
#include <SDL.h>
class SooApp{
private:
    int mMode;
protected:
    virtual ~SooApp();
    virtual int OnInit()=0;
    virtual bool OnEvent(SDL_Event *ev)=0;
    virtual bool Alter()=0;
    virtual int Render()=0;
public:
    SooApp(Uint32);
    /**
     * @param sdlFlag param of SDL_Init()
     * @param imgFlag param of IMG_Init()
     */
    SooApp(Uint32 sdlFlag,Uint32 imgFlag);
    void Run();
};