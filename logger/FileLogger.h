#ifndef DEV_STACK__FILE_LOGGER_H
#define DEV_STACK__FILE_LOGGER_H

#include "OutputLogger.h"

#include <fstream>

using namespace std;

class FileLoggerStream {
public:
    ofstream handle;
    bool _isOpen = false;
    string path;
    const bool isOpen() {
        return _isOpen;
    }
    void open() {
        handle.open(path, fstream::out | fstream::app);
        _isOpen = true;
    }
    void close() {
        handle.close();
        _isOpen = false;
    }

    void write(const string& content) {
        handle << content;
    }
};


class FileLogger : public OutputLogger {
protected:
    FileLoggerStream logStream;

    virtual void log(const int& type, const string& message, const int code = 0) {
        logToFile(logStream, prepareLogEntry(type, message, code));
    }

    void logToFile(FileLoggerStream& stream, const string& content) {
        if (!stream.isOpen()) {
            stream.open();
        }

        stream.write(content);
    }
public:
    virtual FileLogger* setLogPath(string path) {
        logStream.path = path;
        return this;
    }

    virtual void close() {
        if (logStream.isOpen()) {
            logStream.close();
        }
    }
};

#endif