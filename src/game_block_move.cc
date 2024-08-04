#include <iostream>
#include <random>
#include "game_func_data.h"

extern std::mt19937 rand32;

BlockMove::BlockMove(int dir):m_dir(dir){}
int BlockMove::execute(void *)
{
    switch(m_dir){
        case MOVE_LEFT:
            std::cout << "left";
            break;
        case MOVE_RIGHT:
            std::cout << "right";
            break;
        case MOVE_DOWN:
            std::cout << "down";
            break;
    }
    std::cout << std::endl;
    return 0;
}
class Rotate:public SooCommand{
public:
    int execute(void *){
        std::cout << "rotate" << std::endl;
        return 0;
    }
};
static Rotate _rotate;
SooCommand *rotate=&_rotate;

class Land:public SooCommand{
public:
    int execute(void *){
        std::cout << "land" << std::endl;
        return 0;
    }
};
static Land _land;
SooCommand *land=&_land;

