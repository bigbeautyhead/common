#include <iostream>
#include "../include/log.h"

int main()
{
    //创建日志器
    Logger logger(LogLevel::INFO);
    LOG_INFO(logger, "Hello, World!");

    int a = 10;
    LOG_INFO(logger, "a = ", a);
    int b = 20;
    LOG_INFO(logger, "a = ", a, ", b = ", b);
    int c = a + b;
    LOG_INFO(logger, "a = ", a, ", b = ", b, ", a + b = ", c);

    








    return 0;
}