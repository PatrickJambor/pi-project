#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>

namespace Utils {
    std::string getFloatWithPrecision(const float& val, const int& precision);

    std::string getFormalBookType(const char& bookType);

    std::string getFormalCoverType(const std::string& coverType);

    std::string boolToPolish(bool b);

    std::string engTextBoolToPolish(std::string engBool);

    bool isInt(const std::string& input);

    bool isFloat(const std::string& input);

    int enforceValidIntInput(const std::string& message);
    float enforceValidFloatInput(const std::string& message);

}
