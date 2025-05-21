#ifndef CULTURE_FORMATTER_H
#define CULTURE_FORMATTER_H


#include <string>
#include <map>
#include <iostream>

using std::string;
using std::map;

struct CultureInfo {

private:
    static CultureInfo* systemCulture;
public:
    CultureInfo() = default;
    CultureInfo(std::string thousandSeparator, std::string decimalSeparator, std::string currency, std::string time_zone);
    std::string thousandSeparator; // . ,
    std::string decimalSeparator; // , .
    std::string currency; // vnđ $
    std::string time_zone; // GMT+7

    static CultureInfo vi;
    static CultureInfo en;
    
    static CultureInfo get(string locale);
    static CultureInfo get();
    static void setCulture(string locale);
};

class NumberFormatter {

public:
    static string formatNumber(double number, CultureInfo culture);

};
#endif