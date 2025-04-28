#ifndef _RESULT_H
#define _RESULT_H

#include <optional>
#include <string>

template<typename T>
struct Result {
    bool success;
    T data;
    std::string errorMessage;
};


#endif