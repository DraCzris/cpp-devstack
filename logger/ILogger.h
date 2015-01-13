#ifndef DEV_STACK__LOGGER_H
#define DEV_STACK__LOGGER_H

#include <sstream>
#include <ostream>
#include <ios>
#include <iomanip>

#define LOG_RESULTS     0x0000001
#define LOG_INFO        0x0000010
#define LOG_PROGRESS    0x0000100
#define LOG_META        0x0001000

#define LOG_ALL         LOG_RESULTS | LOG_INFO | LOG_PROGRESS | LOG_META
#define LOG_NONE        false

using namespace std;

class Logger__TokenFlush {
public:
    Logger__TokenFlush(int code = 0) {
        this->code = code;
    }
    int code;
};

class Logger__TokenType {
public:
    Logger__TokenType(int type = 0) {
        this->type = type;
    }
    int type;
};

class ILogger {
protected:
    int verbose = LOG_ALL;
    int _type = LOG_INFO;
    stringstream info_buffer = stringstream();
    stringstream meta_buffer = stringstream();
    stringstream progress_buffer = stringstream();
    stringstream result_buffer = stringstream();

    stringstream& getStream(const int& type) {
        switch (type) {
            case LOG_INFO:
                return info_buffer;
            case LOG_META:
                return meta_buffer;
            case LOG_RESULTS:
                return result_buffer;
            case LOG_PROGRESS:
                return progress_buffer;
            default:
                return info_buffer;
        }
    }

    void logWithVerbosityCheck(const int& type, const string& message, const int code = 0) {
        if (!(verbose & type)) {
            return;
        }

        log(type, message, code);
    }

    virtual void log(const int& type, const string& message, const int code = 0) = 0;
public:
    ILogger& type(int type) {
        _type = type;
        return *this;
    }

    void setVerbose(const int& level = LOG_ALL) {
        this->verbose = level;
    }
    void quite() {
        this->verbose = LOG_NONE;
    }

    void reset()
    {
        meta_buffer.clear();
        info_buffer.clear();
        progress_buffer.clear();
        result_buffer.clear();
    }
    virtual void close() {}

    void log(const int code = 0) {
        if (verbose & _type) {
            logWithVerbosityCheck(_type, getStream(_type).str(), code);
        }
        getStream(_type).clear();
    }

    virtual void logResult(const string& message, const int &code = 0) {
        logWithVerbosityCheck(LOG_RESULTS, message, code);
    }
    virtual void logInfo(const string& message, const int &code = 0) {
        logWithVerbosityCheck(LOG_INFO, message, code);
    }
    virtual void logMeta(const string& message, const int &code = 0) {
        logWithVerbosityCheck(LOG_META, message, code);
    }
    virtual void logProgress(const string& message, const int &code = 0) {
        logWithVerbosityCheck(LOG_PROGRESS, message, code);
    }

    #define DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(data_type) ILogger& operator<< (data_type){\
       getStream(_type) << val; return *this;\
    }
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(bool val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(short val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(unsigned short val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(int val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(unsigned int val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(long val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(unsigned long val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(long long val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(unsigned long long val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(float val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(double val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(string val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(long double val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(void* val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(streambuf* val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(ostream& (*val)(ostream&))
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(ios& (*val)(ios&))
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(ios_base& (*val)(ios_base&))
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(__iom_t1 val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(__iom_t2 val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(__iom_t3 val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(__iom_t4<basic_string<char>> val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(__iom_t5 val)
    DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(__iom_t6 val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(__iom_t7<basic_string<char>> val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(__iom_t8<basic_string<char>> val)
    //DEV_STACK__LOGGER_CREATE_OPERATOR_TYPE(__iom_t9<basic_string<char>> val)


    // Custom operators
    ILogger& operator<< (const Logger__TokenFlush& token) {

        log(token.code);
        return *this;
    }
    ILogger& operator<< (const Logger__TokenType& token) {

        type(token.type);
        return *this;
    }
};

namespace logger {
    const Logger__TokenType& info = Logger__TokenType(LOG_INFO);
    const Logger__TokenType& meta = Logger__TokenType(LOG_META);
    const Logger__TokenType& progress = Logger__TokenType(LOG_PROGRESS);
    const Logger__TokenType& results = Logger__TokenType(LOG_RESULTS);

    const Logger__TokenFlush& log = Logger__TokenFlush();

    const Logger__TokenFlush logc(const int& code = 0) {
        return Logger__TokenFlush(code);
    }
}

#endif