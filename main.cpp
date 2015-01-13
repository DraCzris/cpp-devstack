#include <iostream>
#include <string>
#include "logger/MultiFileLogger.h"

using namespace std;

int main() {

    MultiFileLogger* logger = new MultiFileLogger();

    logger
            ->setLogPath("path_info.txt", LOG_INFO)
            ->setLogPath("path_meta.txt", LOG_META)
    ;
    *logger << logger::info << "info heureka" << logger::log;
    *logger << logger::meta << "meta heureka" << logger::log;

    logger->close();

    return 0;
}
