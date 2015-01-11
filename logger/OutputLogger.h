#ifndef DEV_STACK__OUTPUT_LOGGER_H
#define DEV_STACK__OUTPUT_LOGGER_H

#include "ILogger.h"
#include <iomanip>

using namespace std;

#define LOGGER_PREFIX_CHAR "►"

class OutputLogger : public ILogger {
protected:
    string prepareLogEntry(const int& type, const string& message, const int code)
    {
        stringstream entry;

        entry << left << LOGGER_PREFIX_CHAR << setw(3);

        switch (type) {
            case LOG_INFO:
                entry << "I";
                break;
            case LOG_PROGRESS:
                entry << "P";
                break;
            case LOG_META:
                entry << "M";
                break;
            case LOG_RESULTS:
                entry << "R";
                break;
            default:
                entry << "?";
        }

        entry << setw(4);

        if (code) {
            entry << code;
        } else {
            entry << "";
        }

        entry << message << endl;

        return entry.str();
    }
    void log(const int& type, const string& message, const int code = 0) {
        cout << prepareLogEntry(type, message, code);
    }
};

#endif