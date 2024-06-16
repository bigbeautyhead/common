#include <iostream>
#include "../include/log.h"

int main()
{
   try {
        Logger logger(LogLevel::INFO);

        int aa = 10;
        std::string bb = "Hello";

        logger.debug("This is a debug message ", aa);
        logger.info("This is an info message ", aa, bb);
        logger.warning("This is a warning message ","test", aa, bb);
        logger.error("This is an error message ", "test---", " ", aa, bb);

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}