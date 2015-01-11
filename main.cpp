#include <iostream>
#include <string>
#include "logger/OutputLogger.h"
#include "logger/FileLogger.h"

using namespace std;


int main() {

    FileLogger* logger = new FileLogger();

    logger->setLogPath("/Users/draczris/Library/Caches/clion10/cmake/generated/89b20623/89b20623/Debug/test.txt");

    *logger << log::info << "xxyyyy" << log::log();

    logger->close();

    return 0;
}