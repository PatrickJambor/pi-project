#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <string>

#include "LibraryMenager.h"
#include "AudioBook.h"
#include "EBook.h"
#include "PaperBook.h"
#include "EnumConvert.h"

std::vector<std::string> LibraryMenager::splitLine(const std::string& line, const char& delimiter) {
    std::vector<std::string> v;
    std::stringstream sstream(line);
    std::string part;

    while (std::getline(sstream, part, delimiter)) {
        v.push_back(part);
    }

    return v;
}

void LibraryMenager::addAudioBook(
        const int& id,
        const std::string& title,
        const std::string& author,
        const float& price,
        const int& amount,
        const Genre& genre,
        const float& lengthHours,
        const bool& hasMultipleNarrators,
        const bool& isAiNarrated,
        const bool& hasSoundEffects
)
{
    AudioBook* ab = new AudioBook(id, title, author, price, amount,
    genre, lengthHours, hasMultipleNarrators, isAiNarrated, hasSoundEffects);

    products.push_back(ab);
}

void LibraryMenager::addEBook(
        const int& id,
        const std::string& title,
        const std::string& author,
        const float& price,
        const int& amount,
        const Genre& genre,
        const float& fileSizeMB,
        const Format& format
)
{
    EBook* ebook = new EBook(id, title, author, price, amount,
    genre, fileSizeMB, format);

    products.push_back(ebook);
}

void LibraryMenager::addPaperBook(
        const int& id,
        const std::string& title,
        const std::string& author,
        const float& price,
        const int& amount,
        const Genre& genre,
        const int& pageCount,
        const CoverType& coverType,
        const bool& hasIllustrations
)
{
    PaperBook* pb = new PaperBook(id, title, author, price, amount,
    genre, pageCount, coverType, hasIllustrations);

    products.push_back(pb);
}

void LibraryMenager::loadBookFromDb(const char& bookType, const std::vector<std::string>& bookInfo) {
    int id = std::stoi(bookInfo.at(1));
    std::string title = bookInfo.at(2);
    std::string author = bookInfo.at(3);
    float price = std::stof(bookInfo.at(4));
    int amount = std::stoi(bookInfo.at(5));
    Genre genre = EnumConvert::stringToGenre(bookInfo.at(6));

    switch(bookType) {
        case 'A': {
            float lengthHours = std::stof(bookInfo.at(7));
            bool hasMultipleNarrators = bookInfo.at(8) == "true";
            bool isAiNarrated = bookInfo.at(9) == "true";
            bool hasSoundEffects = bookInfo.at(10) == "true";

            addAudioBook(id,title,author,price,amount,genre,lengthHours,hasMultipleNarrators,isAiNarrated,hasSoundEffects);
            break;
        }
        case 'E': {
            float fileSizeMB = std::stof(bookInfo.at(7));
            Format format = EnumConvert::stringToFormat(bookInfo.at(8));

            addEBook(id,title,author,price,amount,genre,fileSizeMB,format);
            break;
        }
        case 'P': {
            int pageCount = std::stoi(bookInfo.at(7));
            CoverType cover = EnumConvert::stringToCoverType(bookInfo.at(8));
            bool hasIllustrations = bookInfo.at(9) == "true";

            addPaperBook(id,title,author,price,amount,genre,pageCount,cover,hasIllustrations);
            break;
        }
    }
}

LibraryMenager::LibraryMenager(const std::string& dbFile) {
    std::ifstream db(dbFile);

    if (!db.is_open()) {
        throw std::runtime_error("ERROR: DATABASE COULD NOT BE LOADED.");
    }

    std::string line;

    while (std::getline(db, line)) {
        std::vector<std::string> bookInfo = splitLine(line, ';');
        char bookType = bookInfo.front()[0];
        loadBookFromDb(bookType,bookInfo);
    }
    db.close();
}

