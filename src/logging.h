#pragma once
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>


namespace Logging {

template<class... Args>
void log(Args... args)
{
    time_t actualTime = time(NULL);

    auto timestamp = std::put_time(gmtime(&actualTime), "%Y-%m-%d %H:%M:%S");
    std::cout << "[" << timestamp<< "] ";
    (std::cout << ... << args) << std::endl;
}

}
