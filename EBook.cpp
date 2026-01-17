#include "EBook.h"
#include "EnumConvert.h"

void EBook::compare(const Product& p) {
}

float EBook::getFileSizeMB() {
    return fileSizeMB;
}

Format EBook::getFormat() {
    return format;
}

std::string EBook::toString() {
    return "A;" + std::to_string(id) + ";"
    + title + ";"
    + author + ";"
    + std::to_string(price) + ";"
    + std::to_string(amount) + ";"
    + EnumConvert::genreToString(genre) + ";"
    + std::to_string(fileSizeMB) + ";"
    + EnumConvert::formatToString(format) + ";";
}
