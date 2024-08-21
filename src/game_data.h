#pragma once
class SdlTexture;
class SdlModel;
class SdlApplication;
class GameData {
public:
    SdlApplication  *app;
    SdlModel        *menu,*game;
    SdlTexture      *background;
    Uint32           colors[256];
    static GameData* getInstance();
    static void      init(SdlApplication *app);
};
#define RGBA8888(r,g,b,a) ((a) | ((b)<<8) | ((g)<<16) | ((r)<<24))


#define RED(u32)   (((u32) >> 24) & 0xff)
#define GREEN(u32) (((u32) >> 16) & 0xff)
#define BLUE(u32)  (((u32) >> 8)  & 0xff)
#define ALPHA(u32) ((u32) & 0xff)