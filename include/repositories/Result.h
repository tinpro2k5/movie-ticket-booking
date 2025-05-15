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
        : success(success), data(data), error_message(error_message) {}
    Result(bool success, const std::string& error_message = "")
        : success(success), error_message(error_message) {}

};

template<>
struct Result<void> {
    bool success;
    std::string error_message;

    Result() {}
    Result(bool success, const std::string& error_message = "")
        : success(success), error_message(error_message) {}
};

#endif