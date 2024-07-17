#pragma once
#include <SDL.h>
class SooTexture;
class SooRenderer;
class SooCommand;
class MainMenu {
private:
    int m_width,m_height;
    SooTexture *m_menuItem[3];
    SDL_Rect m_itemPos[3];
    SooRenderer *m_render;
    SooCommand *m_cmd;
    int m_focus;
public:
    MainMenu(SooRenderer *,int,int);
    MainMenu(const MainMenu&)=delete;
    SooCommand *commandAt(int);
    void paintAll();
    virtual ~MainMenu();
};