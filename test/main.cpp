#include <iostream>
#include "../include/log.h"

int main()
{
   try {
        Logger logger(LogLevel::INFO);

        int aa = 10;
        std::string bb = "Hello";

        logger.debug("This is a debug message");
        logger.info("This is an info message");
        logger.warning("This is a warning message");
        logger.error("This is an error message");

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}