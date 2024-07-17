#pragma once
#include <memory>
class SooTexture;
class SooRenderer;
class MainMenu;
class Resource{
public:
    std::unique_ptr<SooTexture> background;
    //SooTexture *number[10];
    std::unique_ptr<MainMenu> mainMenu;
    virtual ~Resource();
    Resource(SooRenderer *,int,int);
    Resource(const Resource&)=delete;
};