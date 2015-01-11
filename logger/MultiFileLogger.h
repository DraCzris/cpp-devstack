#ifndef DEV_STACK__MULTI_FILE_LOGGER_H
#define DEV_STACK__MULTI_FILE_LOGGER_H

#include "FileLogger.h"

using namespace std;

class MultiFileLogger : public FileLogger {
protected:
    FileLoggerStream infoStream;
    FileLoggerStream metaStream;
    FileLoggerStream progressStream;
    FileLoggerStream resultStream;

    virtual void log(const int& type, const string& message, const int code = 0) {
        logToFile(getFileStreamByType(type), prepareLogEntry(type, message, code));
    }

    FileLoggerStream& getFileStreamByType(const int& type) {
        switch (type) {
            case LOG_RESULTS:
                return resultStream;
            case LOG_META:
                return metaStream;
            case LOG_PROGRESS:
                return progressStream;
            case LOG_INFO:
            default:
                return infoStream;
        }
    }
public:
    virtual FileLogger* setLogPath(string path) {
        infoStream.path = path;
        return this;
    }

    MultiFileLogger* setLogPath(string path, const int& type) {
        getFileStreamByType(type).path = path;
        return this;
    }

    virtual void close() {
        infoStream.close();
        metaStream.close();
        progressStream.close();
        resultStream.close();
    }
};

#endif