#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime> // clock()
#include <cstdlib> // rand(),srand()
#include "png_name.h"
#include "soo_exception.h"
const char *png_list="../png-list.txt";
PngName::~PngName()
{
    mPngs.close();
}
PngName::PngName(){
    std::srand(clock());
    mMax=std::filesystem::file_size(png_list);
    mPngs.open(png_list,std::ios::binary);
    if(!mPngs.is_open()){
        throw EX("打开文件错误");
    }
}

// 文件路径长度不超过ＭＡＸＳＩＺＥ
#define MAXSIZE 256
const std::string& PngName::Name()
{
    try{
        
        long pos= std::rand();
        pos = pos * std::rand();
        pos = pos % mMax;
        if (pos < MAXSIZE){
            pos=0;
        }else {
            pos -=MAXSIZE;
        }
        std::cout <<"文件位置:" <<pos << std::endl;

        mPngs.seekg(pos,std::ios::beg);

        char *buf=new char[MAXSIZE];
        mPngs.read(buf,MAXSIZE);
        if(!mPngs.good()){
            delete [] buf;
            throw EX("read file error");
        }
        
        int idx=0;
        while(*(buf+idx)!='\n'){
            idx++;
        }
        idx++;
        std::stringbuf sb;
        while(*(buf+idx)!='\n'){
            sb.sputc(*(buf+idx));
            idx ++;
        }
        sb.sputc('\0');
        mStr = sb.str();
        delete [] buf;
        return mStr;
    } catch (std::exception &e){
        throw EXMSG(e,"读文件错误");
    } catch (...){
        throw;
    }
}

