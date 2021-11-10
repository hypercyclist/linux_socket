#include "FlexTime.h"

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

FlexTime::FlexTime()
{
}

FlexTime::~FlexTime()
{
}

std::string FlexTime::currentTime()
{
    // Return example [2018-09-19 13:50:01.000]
    std::chrono::system_clock::time_point chronoTime = std::chrono::system_clock::now();
    std::chrono::milliseconds milliseconds = 
        std::chrono::duration_cast<std::chrono::milliseconds>(chronoTime.time_since_epoch());

    std::time_t secondsTime = std::chrono::system_clock::to_time_t(chronoTime);
    std::tm time = *localtime(&secondsTime);
    std::string stringTime = "[";
    stringTime += convertPartToString(time.tm_year + 1900, 4) + "-";
    stringTime += convertPartToString(time.tm_mon + 1, 2) + "-";
    stringTime += convertPartToString(time.tm_mday, 2) + " ";
    stringTime += convertPartToString(time.tm_hour, 2) + ":";
    stringTime += convertPartToString(time.tm_min, 2) + ":";
    stringTime += convertPartToString(time.tm_sec, 2) + ".";
    stringTime += convertPartToString(milliseconds.count() % 1000, 3);
    stringTime += "]";
    return stringTime;
}

std::string FlexTime::convertPartToString(int _part, int _digitsCount)
{
    std::stringstream stringStream;
    stringStream << std::setw(_digitsCount) << std::setfill('0') << _part;
    std::string result = stringStream.str(); 
    return result;
}