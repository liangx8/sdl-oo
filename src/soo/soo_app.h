#pragma once
class SooCommand;
class SooApp{
private:
    int mMode;
protected:
    virtual ~SooApp();
    // 带事件的
    virtual void triggerEvent(SDL_Event *)=0;
    // 无事件发生时的空闲时段以及更新屏幕
    virtual void update()=0;
    virtual void init()=0;
public:
    SooApp(Uint32);
    /**
     * @param sdlFlag param of SDL_Init()
     * @param imgFlag param of IMG_Init()
     */
    SooApp(Uint32 sdlFlag,Uint32 imgFlag);
    SooApp(const SooApp&)=delete;
    void Run();
};