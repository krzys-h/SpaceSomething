#pragma once

#include <string>
#include <sstream>

template<typename T>
std::string to_string(T val)
{
    std::ostringstream ss;
    ss << val;
    return ss.str();
}

template<typename T>
T from_string(std::string str)
{
    std::istringstream ss(str);
    T val;
    ss >> val;
    return val;
}