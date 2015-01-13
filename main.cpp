#include <iostream>
#include <string>
#include "logger/MultiFileLogger.h"

using namespace std;

int main() {

    MultiFileLogger* logger = new MultiFileLogger();

    logger
            ->setLogPath("/Users/draczris/Library/Caches/clion10/cmake/generated/89b20623/89b20623/Debug/info.txt", LOG_INFO)
            ->setLogPath("/Users/draczris/Library/Caches/clion10/cmake/generated/89b20623/89b20623/Debug/meta.txt", LOG_META)
    ;
    *logger << logger::info << "info heureka" << logger::log;
    *logger << logger::meta << "meta heureka" << logger::log;

    logger->close();

    return 0;
}