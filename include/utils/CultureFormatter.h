#ifndef CULTURE_FORMATTER_H
#define CULTURE_FORMATTER_H

#include <string>
#include <map>
#include <iostream>

using std::string;
using std::map;

/**
 * @struct CultureInfo
 * @brief Stores culture-specific formatting information.
 *
 * Contains information such as thousand separator, decimal separator, currency symbol, and time zone.
 * Provides static methods to get and set the current culture.
 */
struct CultureInfo {

private:
    static CultureInfo* systemCulture; /**< Pointer to the current system culture */
public:
    /**
     * @brief Default constructor.
     */
    CultureInfo() = default;

    /**
     * @brief Parameterized constructor.
     * @param thousandSeparator Separator for thousands (e.g., "," or ".")
     * @param decimalSeparator Separator for decimals (e.g., "." or ",")
     * @param currency Currency symbol (e.g., "vnđ", "$")
     * @param time_zone Time zone string (e.g., "GMT+7")
     */
    CultureInfo(std::string thousandSeparator, std::string decimalSeparator, std::string currency, std::string time_zone);

    std::string thousandSeparator; /**< Separator for thousands */
    std::string decimalSeparator;  /**< Separator for decimals */
    std::string currency;          /**< Currency symbol */
    std::string time_zone;         /**< Time zone string */

    static CultureInfo vi;         /**< Vietnamese culture info */
    static CultureInfo en;         /**< English culture info */
    
    /**
     * @brief Get a CultureInfo object by locale.
     * @param locale Locale string (e.g., "vi", "en")
     * @return Corresponding CultureInfo object
     */
    static CultureInfo get(string locale);

    /**
     * @brief Get the current system culture.
     * @return Current CultureInfo object
     */
    static CultureInfo get();

    /**
     * @brief Set the system culture by locale.
     * @param locale Locale string
     */
    static void setCulture(string locale);
};

/**
 * @class NumberFormatter
 * @brief Provides static methods for formatting numbers according to culture.
 */
class NumberFormatter {

public:
    /**
     * @brief Format a number according to the specified culture.
     * @param number The number to format
     * @param culture The CultureInfo to use for formatting
     * @return Formatted number as a string
     */
    static string formatNumber(double number, CultureInfo culture);

};
#endif