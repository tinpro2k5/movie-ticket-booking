/**
 * @file Result.h
 * @brief Defines the Result struct template for encapsulating operation outcomes in the repository and service layers.
 *
 * The Result struct is a generic wrapper used to represent the outcome of operations,
 * including success status, returned data (if any), and error messages.
 *
 * Architecture overview:
 * - Result<T> is used throughout repositories and services to standardize the way results and errors are handled.
 * - It supports both operations that return data (Result<T>) and those that do not (Result<void> specialization).
 * - This pattern improves error handling, debugging, and code clarity by making operation outcomes explicit.
 */

/**
 * @struct Result
 * @brief Template struct to encapsulate the result of an operation.
 *
 * @tparam T The type of data returned by the operation.
 *
 * @var Result::success
 * Indicates whether the operation was successful.
 * @var Result::data
 * The data returned by the operation (if any).
 * @var Result::error_message
 * Error message describing the failure, if any.
 */
#ifndef _RESULT_H
#define _RESULT_H

#include <optional>
#include <string>

template<typename T>
struct Result {
    bool success;                ///< Operation success status.
    T data;                      ///< Data returned by the operation.
    std::string error_message;   ///< Error message if the operation failed.

    /**
     * @brief Default constructor.
     */
    Result() {}

    /**
     * @brief Constructor with success status, data, and optional error message.
     * @param success Whether the operation was successful.
     * @param data The data returned by the operation.
     * @param error_message Optional error message.
     */
    Result(bool success, T data, const std::string& error_message = "")
        : success(success), data(data), error_message(error_message) {}

    /**
     * @brief Constructor with success status and optional error message.
     * @param success Whether the operation was successful.
     * @param error_message Optional error message.
     */
    Result(bool success, const std::string& error_message = "")
        : success(success), error_message(error_message) {}
};

/**
 * @struct Result<void>
 * @brief Specialization of Result for operations that do not return data.
 *
 * @var Result<void>::success
 * Indicates whether the operation was successful.
 * @var Result<void>::error_message
 * Error message describing the failure, if any.
 */
template<>
struct Result<void> {
    bool success;                ///< Operation success status.
    std::string error_message;   ///< Error message if the operation failed.

    /**
     * @brief Default constructor.
     */
    Result() {}

    /**
     * @brief Constructor with success status and optional error message.
     * @param success Whether the operation was successful.
     * @param error_message Optional error message.
     */
    Result(bool success, const std::string& error_message = "")
        : success(success), error_message(error_message) {}
};

#endif