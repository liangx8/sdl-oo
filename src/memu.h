#pragma once
#include "soo_view.h"
class SooTexture;
class MainMenu :public SooView{
private:
    int m_width,m_height;
    SooTexture *menuItem[3];
public:
    int paint(SooRenderer *);
};