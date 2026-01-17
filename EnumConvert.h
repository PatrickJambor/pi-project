#pragma once

#include <string>
#include "enum.h"

namespace EnumConvert {
    Genre stringToGenre(const std::string& strGenre);
    CoverType stringToCoverType(const std::string& strCover);
    Format stringToFormat(const std::string& strFormat);

    std::string genreToString(const Genre& genre);
    std::string coverTypeToString(const CoverType& coverType);
    std::string formatToString(const Format& format);
}
