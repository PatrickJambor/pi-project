#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <string>
#include <algorithm>

#include "LibraryMenager.h"
#include "AudioBook.h"
#include "EBook.h"
#include "PaperBook.h"
#include "EnumConvert.h"
#include "Utils.h"

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

    for(Product* p : products) {
        if(p->getId() == id) {
            std::cout << "BLAD: Ksiazka o tytule " << title << " ma id ktore zostalo juz zaladowane. Sprawdz baze danych." << std::endl;
            return;
        }
    }

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
        std::ofstream stream("db.txt");
        return;
    }

    std::string line;

    while (std::getline(db, line)) {
        std::vector<std::string> bookInfo = splitLine(line, ';');
        char bookType = bookInfo.front()[0];
        loadBookFromDb(bookType,bookInfo);
    }
    db.close();
}

void LibraryMenager::searchBooksById(const int& id) {
    int results = 0;
    for (Product* p : products) {

        if(p->getId() == id) {
            results++;
            p->displayInfo();
        }
    }
    std::cout << "Liczba wynikow: " << results << std::endl;
}

void LibraryMenager::searchBooksByTitle(const std::string& title) {
    int results = 0;
    for (Product* p : products) {

        if(p->getTitle() == title) {
            results++;
            p->displayInfo();
        }
    }
    std::cout << "Liczba wynikow: " << results << std::endl;
}

void LibraryMenager::searchBooksByAuthor(const std::string& author) {
    int results = 0;
    for (Product* p : products) {

        if(p->getAuthor() == author) {
            results++;
            p->displayInfo();
        }
    }
    std::cout << "Liczba wynikow: " << results << std::endl;
}

void LibraryMenager::searchByPriceRange(const int& minPrice, const int& maxPrice) {
    int results = 0;
    for (Product* p : products) {

        if(p->getPrice() >= minPrice && p->getPrice() <= maxPrice) {
            results++;
            p->displayInfo();
        }
    }
    std::cout << "Liczba wynikow: " << results << std::endl;
}

void LibraryMenager::sellBookById(const int& id, const int& sellAmount) {
    bool soldSomething = false;
    bool insufficientAmount = false;

    for (Product* p : products) {
        if(p->getId() == id) {
            if (p->getAmount() >= sellAmount) {
                p->sell(sellAmount);
                soldSomething = true;
                if(!hasUnsavedChanges) hasUnsavedChanges = true;
            } else insufficientAmount = true;
        }
    }
    if(insufficientAmount) {
        std::cout << "BLAD: Niewystarczajaca ilosc ksiazek na stanie aby wykonac operacje" << std::endl;
        return;
    }
    if(soldSomething) std::cout << "Operacja wykonana pomyslnie." << std::endl;
    else std::cout << "Operacja nie powiodla sie. Nie znaleziono ksiazki o podanym id." << std::endl;
}

void LibraryMenager::restockBookById(const int& id, const int& restockAmount) {
    bool restockSuccessful = false;
    for (Product* p : products) {
        if(p->getId() == id) {
            p->restock(restockAmount);
            restockSuccessful = true;
            if(!hasUnsavedChanges) hasUnsavedChanges = true;
        }
    }
    if(restockSuccessful) std::cout << "Operacja wykonana pomyslnie." << std::endl;
    else std::cout << "Operacja nie powiodla sie. Nie znaleziono ksiazki o podanym id." << std::endl;
}


void LibraryMenager::removeBookById(const int& id) {
    int sizeBefore = products.size();
    auto it = std::remove_if(products.begin(), products.end(), [&id](Product* p){
        return p->getId() == id;
    });

    if (it != products.end()) {
        delete *it;
        products.erase(it);

        if(!hasUnsavedChanges) hasUnsavedChanges = true;

        std::cout << "Operacja wykonana pomyslnie." << std::endl;
    } else {
        std::cout << "Operacja nie powiodla sie. Nie znaleziono ksiazki o podanym id." << std::endl;
    }
}

void LibraryMenager::changeBookPriceById(const int& id, const float& newPrice) {
    bool success = false;
    for (Product* p : products) {
        if (p->getId() == id) {
            p->changePrice(newPrice);
            success = true;
        }
    }
    if(success) {
        std::cout << "Operacja wykonana pomyslnie" << std::endl;
        if(!hasUnsavedChanges) hasUnsavedChanges = true;
    }
    else std::cout << "Operacja nie powiodla sie. Nie znaleziono ksiazki o podanym id." << std::endl;
}

int LibraryMenager::getAllBookCount() {
    int bCount = 0;
    for (Product* p : products) {
        if(p->getAmount() > 0) bCount+= p->getAmount();
    }
    return bCount;
}

int LibraryMenager::getAllBookValue() {
    int value = 0;
    for (Product* p : products) {
        value += p->getPrice();
    }
    return value;
}

void LibraryMenager::displayShortage() {
    int results = 0;
    for (Product* p : products) {
        if (p->getAmount() < 5) {
            p->displayInfo();
            results++;
        }
    }
    std::cout << "Ilosc wynikow: " << results << std::endl;
}

void LibraryMenager::saveAll() {
    if (hasUnsavedChanges) {

        std::ofstream stream("db.txt");

        std::sort(products.begin(), products.end(), [](Product* p1, Product* p2){
            return p1->getId() < p2->getId();
        });

        for (Product* p : products) {
            stream << p->toString() << std::endl;
        }
        hasUnsavedChanges = false;
        std::cout << std::endl;
        std::cout << "Dokonano zapisu" << std::endl;

    } else {
        std::cout << "Nie dokonano zapisu. Baza danych ma aktualne informacje." << std::endl;
    }
}

void LibraryMenager::setHasUnsavedChanges(bool unsavedChanges) {
    hasUnsavedChanges = unsavedChanges;
}

bool LibraryMenager::getHasUnsavedChanges() {
    return hasUnsavedChanges;
}

bool LibraryMenager::idAlreadExists(const int& id) {
    for (Product* p : products) {
        if (p->getId() == id) {
            return true;
        }
    }
    return false;
}

void LibraryMenager::displayAll() {
    int results = 0;
    for (Product* p : products) {
        p->displayInfo();
        results++;
    }
    std::cout << std::endl;
    std::cout << "Liczba wynikow: " << results << std::endl;
}

void LibraryMenager::massRestock() {
    std::ifstream f("massRestock.txt");

    if(!f.is_open()) {
        std::cout << "Nie znaleziono pliku z dostawa. Zostanie utworzony pusty plik." << std::endl;
        std::ofstream f("massRestock.txt");
        return;
    }

    std::string line;


    while(std::getline(f,line)) {
        std::vector<std::string> restockInfo = splitLine(line,';');
        int id = std::stoi(restockInfo.front());
        int restockAmount = std::stoi(restockInfo.back());

        restockBookById(id, restockAmount);
    }

}
