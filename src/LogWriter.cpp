#include "LogWriter.h"

#include <iostream>
#include <fstream>

LogWriter::LogWriter()
{
}

LogWriter::~LogWriter()
{
}

void LogWriter::writeLog(std::string _string, std::string _fileName)
{
    std::ofstream logFile(_fileName, std::ios_base::out | std::ios_base::app);
    logFile << _string << "\n";
    logFile.close();
}
