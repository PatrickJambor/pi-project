#include <stdexcept>

#include "EnumConvert.h"

Genre EnumConvert::stringToGenre(const std::string& strGenre) {
    if (strGenre == "fantasy") return Genre::fantasy;
    if (strGenre == "scienceFiction") return Genre::scienceFiction;
    if (strGenre == "horror") return Genre::horror;
    if (strGenre == "crime") return Genre::crime;
    if (strGenre == "romance") return Genre::romance;
    throw std::runtime_error("ERROR: INCORRECT BOOK GENRE IN DATABASE.");
}

CoverType EnumConvert::stringToCoverType(const std::string& strCover) {
    if (strCover == "hardCover") return CoverType::hardCover;
    if (strCover == "paperBack") return CoverType::paperBack;
    throw std::runtime_error("ERROR: INCORRECT BOOK COVER TYPE IN DATABASE.");
}

Format EnumConvert::stringToFormat(const std::string& strFormat) {
    if (strFormat == "PDF") return Format::PDF;
    if (strFormat == "EPUB") return Format::EPUB;
    throw std::runtime_error("ERROR: INCORRECT BOOK FORMAT IN DATABASE.");
}

std::string EnumConvert::genreToString(const Genre& genre) {
    switch(genre) {
    case Genre::crime:
        return "crime";

    case Genre::fantasy:
        return "fantasy";

    case Genre::horror:
        return "horror";

    case Genre::romance:
        return "romance";

    case Genre::scienceFiction:
        return "scienceFiction";

    }
}

std::string EnumConvert::coverTypeToString(const CoverType& coverType) {
    switch(coverType) {
    case CoverType::hardCover:
        return "hardCover";

    case CoverType::paperBack:
        return "paperBack";
    }
}

std::string EnumConvert::formatToString(const Format& format) {
    switch(format) {
    case Format::EPUB:
        return "EPUB";

    case Format::PDF:
        return "PDF";
    }
}


