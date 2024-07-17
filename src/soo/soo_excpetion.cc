#include <iostream>
#include <SDL.h>
#include "soo_exception.h"

const char *SooException::what() const throw(){
    
    return m_strMsg.c_str();
}

SooException::SooException(const char *msg):
    exception(),
    m_strMsg(msg){}
SooException::SooException(const exception &ex,const char *m):
    exception(),
    m_strMsg(ex.what())
{
    m_strMsg += m;
}
SooException::~SooException(){
}

// const char* SooException::className()
// {
//     return "Class[SooException]";
// }

