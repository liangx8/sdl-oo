#include <memory>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime> // clock()
#include <cstdlib> // rand(),srand()
#include "png_name.h"
#include "soo/soo_exception.h"

PngName::~PngName()
{
    mPngs.close();
}
PngName::PngName(const char *listtxt){
    std::srand(clock());
    mMax=std::filesystem::file_size(listtxt);
    mPngs.open(listtxt,std::ios::binary);
    if(!mPngs.is_open()){
        throw EX("打开文件错误");
    }
}

const std::string& PngName::Name()
{
    try{
#if 1
        long pos= std::rand();
        pos = pos * std::rand();
        pos = pos % mMax;
#else
        const long pos=30;
#endif

        mPngs.seekg(pos,std::ios::beg);
        auto npos= mPngs.tellg();
        while(npos){
            int ch=mPngs.get();
            if(ch=='\n'){
                break;
            }
            if(npos <= 2){
                mPngs.seekg(0,std::ios::beg);
                break;
            }
            npos -=2;
            mPngs.seekg(-2,std::ios::cur);
        }
        std::stringbuf sb;
        while(1){
            int ch=mPngs.get();
            if(ch=='\n'){
                sb.sputc('\0');
                break;
            }
            sb.sputc(ch);
        }
        mStr = sb.str();
        return mStr;
    } catch (std::exception &e){
        throw EXMSG(e,"读文件错误");
    } catch (...){
        throw;
    }
}

