#ifndef _RESULT_H
#define _RESULT_H

#include <optional>
#include <string>

template<typename T>
struct Result {
    bool success;
    T data;
    std::string errorMessage;

    Result() {}
    Result(bool success, T data, const std::string& errorMessage = "")
        : success(success), data(data), errorMessage(errorMessage) {}
    Result(bool success, const std::string& errorMessage = "")
        : success(success), errorMessage(errorMessage) {}

};


#endif