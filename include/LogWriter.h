#ifndef LOGWRITER_H
#define LOGWRITER_H

#include <string>

class LogWriter
{
    private:
        LogWriter();
    public:
        ~LogWriter();
        static void writeLog(std::string _string, std::string _fileName);
};

#endif
