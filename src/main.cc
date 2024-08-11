

#include <iostream>
#include <exception>

void gamestart();
int main(int argc,char **argv)
{
    int res;
    try {
        gamestart();
    }catch(std::exception &e){
        std::cout <<e.what();
        res=-1;
    }
    return res;
}
