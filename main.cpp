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
    *logger << log::info << "info heureka" << log::log;
    *logger << log::meta << "meta heureka" << log::log;

    logger->close();

    return 0;
}
