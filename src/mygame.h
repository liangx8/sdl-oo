#pragma once
#include <SDL2/SDL.h>

#include "soo/soo_app.h"
class GameData;
class MyGame:public SooApp{
private:
    const char     *name;
protected:
    virtual int init(void *);
    virtual int release(void *);
public:
    MyGame(const char *);
    virtual ~MyGame();
};