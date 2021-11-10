#ifndef FLEXTIME_H
#define FLEXTIME_H

#include <string>

class FlexTime
{
    private:
        FlexTime();
        static std::string convertPartToString(int _part, int _digitsCount);
    public:
        ~FlexTime();
        static std::string currentTime();
};

#endif