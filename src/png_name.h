#ifndef PNG_NAME_H_ZCJJWE34232
#define PNG_NAME_H_ZCJJWE34232
#include <sstream>
#include <fstream>
class PngName{
private:
    std::stringbuf mSbuf;
    std::ifstream mPngs;
    long mMax;
public:
    const std::string Name();
    PngName();
    ~PngName();
};
#endif