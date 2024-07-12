#pragma once
class SooRenderer;
class SooView{
protected:
    virtual ~SooView();
public:
    virtual int paint(SooRenderer *render)=0;
};