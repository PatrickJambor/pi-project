#include "PaperBook.h"
#include "EnumConvert.h"

void PaperBook::compare(const Product& p) {
}

int PaperBook::getPageCount() {
    return pageCount;
}

CoverType PaperBook::getCoverType() {
    return coverType;
}

bool PaperBook::getHasIllustrations() {
    return hasIllustrations;
}

std::string PaperBook::toString() {
    std::string illustrations = hasIllustrations ? "true" : "false";

    return "A;" + std::to_string(id) + ";"
    + title + ";"
    + author + ";"
    + std::to_string(price) + ";"
    + std::to_string(amount) + ";"
    + EnumConvert::genreToString(genre) + ";"
    + std::to_string(pageCount) + ";"
    + EnumConvert::coverTypeToString(coverType) + ";"
    + illustrations + ";";
}
