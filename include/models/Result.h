#ifndef _RESULT_H
#define _RESULT_H

#include <optional>
#include <string>

template<typename T>
struct Result {
    bool success;
    T data;
    std::string error_message;

    Result() {}
    Result(bool success, T data, const std::string& error_message = "")
        : success(success), data(data), errorMessage(error_message) {}
    Result(bool success, const std::string& error_message = "")
        : success(success), errorMessage(error_message) {}

};


#endif