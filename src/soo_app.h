#ifndef SOO_APP_H_JFW4J34
#define SOO_APP_H_JFW4J34
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
    void Poll();
    int RunAt(Uint32,int (*run)(void *));
};
#endif