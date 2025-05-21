#include "../../include/utils/CultureFormatter.h"
CultureInfo* CultureInfo::systemCulture = nullptr;
CultureInfo::CultureInfo(std::string thousandSeparator, std::string decimalSeparator, std::string currency, std::string time_zone)
    : thousandSeparator(thousandSeparator), decimalSeparator(decimalSeparator), currency(currency), time_zone(time_zone) {}

CultureInfo CultureInfo::vi = CultureInfo{".", ",", "vnđ", "GMT+7"};
CultureInfo CultureInfo::en = CultureInfo{",", ".", "$", "GMT+7"};

CultureInfo CultureInfo::get() {
    if (!systemCulture) {
        // Default to Vietnamese if not set
        return CultureInfo::vi;
    }
    return *systemCulture;
}



void CultureInfo::setCulture(string locale) {
    if (locale == "vi-VN") {
        systemCulture = &CultureInfo::vi;
    } else if (locale == "en-US") {
        systemCulture = &CultureInfo::en;
    } else {
        systemCulture = &CultureInfo::vi; // default
    }
}

string NumberFormatter::formatNumber(double number, CultureInfo culture) {
    std::string str = std::to_string(number);
    size_t dotPos = str.find('.');
    if (dotPos != std::string::npos) {
        str[dotPos] = culture.decimalSeparator[0];
    }
    
    for (int i = dotPos - 3; i > 0; i -= 3) {
        str.insert(i, culture.thousandSeparator);
    }
    // giới 2 chữ số sau dấu phẩy
    if (dotPos != std::string::npos) {
        str = str.substr(0, dotPos + 3);
    }
    
    
    return str;
}