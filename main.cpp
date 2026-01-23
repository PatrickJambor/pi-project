#include <stdexcept>
#include <iostream>
#include <windows.h>

#include "Product.h"
#include "AudioBook.h"
#include "EBook.h"
#include "PaperBook.h"
#include "LibraryMenager.h"
#include "EnumConvert.h"
#include "Utils.h"

const std::string DB_FILE_PATH = "db.txt";

void displayMainMenu() {
    std::cout << std::endl;
    std::cout << "###SYSTEM ZARZADZANIA KSIEGARNIA###" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "***MENU GLOWNE***" << std::endl;

    std::cout << "1: Wyszukiwanie" << std::endl;
    std::cout << "2: Zarzadzanie stanem" << std::endl;
    std::cout << "3: Raporty" << std::endl;
    std::cout << "4: Wyswietl dane wszystkich ksiazkek" << std::endl;
    std::cout << "5: Zapisz aktualny stan do bazy" << std::endl;

    std::cout << ">";
}

void handleSearchMenu(LibraryMenager& menager) {
    while(true) {
        char choice;
        std::cout << std::endl;
        std::cout << "***WYSZUKIWANIE KSIAZEK***" << std::endl;
        std::cout << "1: Po id" << std::endl;
        std::cout << "2: Po tytule" << std::endl;
        std::cout << "3: Po autorze" << std::endl;
        std::cout << "4: Po zakresie cenowym" << std::endl;
        std::cout << "5: Menu glowne" << std::endl;

        std::cout << ">";
        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        switch(choice) {
        case '1': {
            int id = Utils::enforceValidIntInput("Podaj id");
            menager.searchBooksById(id);
            break;
        }
        case '2': {
            std::string title;
            std::cout << "Podaj tytul" << std::endl;
            std::cout << ">";
            getline(std::cin, title);

            menager.searchBooksByTitle(title);
            break;
        }
        case '3': {
            std::string author;
            std::cout << "Podaj autora" << std::endl;
            std::cout << ">";
            std::getline(std::cin, author);

            menager.searchBooksByAuthor(author);
            break;
        }
        case '4': {
            int minPrice = Utils::enforceValidIntInput("Podaj minimalna cene");
            int maxPrice = Utils::enforceValidIntInput("Podaj maksymalna cene");
            menager.searchByPriceRange(minPrice, maxPrice);
            break;
        }
        }
        if(choice == '5') break;
    }
}

void handleBookSell(LibraryMenager& menager) {
    int id = Utils::enforceValidIntInput("Podaj id");
    int amountToSell = Utils::enforceValidIntInput("Ile Chcesz sprzedac");
    menager.sellBookById(id, amountToSell);
}

void handleRestock(LibraryMenager& menager) {
    int id = Utils::enforceValidIntInput("Podaj id");
    int amountToRestock = Utils::enforceValidIntInput("Ilosc ksiazek w dostawie");
    menager.restockBookById(id, amountToRestock);
}

void handleMassRestock(LibraryMenager& menager) {
    menager.massRestock();
}

void handleBookAddition(LibraryMenager& menager) {
    std::string bookType;
    char type;

    while (type != '1' && type != '2' && type != '3') {
        std::cout << "Podaj typ ksiazki" << std::endl;
        std::cout << "1: AudioBook" << std::endl;
        std::cout << "2: EBook" << std::endl;
        std::cout << "3: Papierowa" << std::endl;

        std::cout << ">";

        std::cin >> type;
        std::cin.ignore(1000, '\n');

    }

    switch(type) {
        case '1': {
            bookType = "AudioBook";
            break;
        case '2':
            bookType = "EBook";
            break;
        case '3':
            bookType = "PaperBook";
            break;
        }
    }

    int id = Utils::enforceValidIntInput("Podaj id");

    if (menager.idAlreadExists(id)) {
        std::cout << "BLAD: Ksiazka o podanym id juz istnieje w bazie." << std::endl;
        return;
    }

    std::string title;
    std::string author;
    float price = Utils::enforceValidFloatInput("Podaj cene");
    int amount = Utils::enforceValidIntInput("Podaj ilosc");
    Genre genre;

    std::cout << "Podaj tytul" << std::endl;
    std::cout << ">";
    std::cin >> title;
    std::cin.ignore(1000, '\n');

    std::cout << "Podaj autora" << std::endl;
    std::cout << ">";
    std::cin >> author;
    std::cin.ignore(1000, '\n');

    std::string strGenre;

    char cGenre;

    while (cGenre != '1' && cGenre != '2' && cGenre != '3' && cGenre != '4' && cGenre != '5') {
        std::cout << "Podaj gatunek" << std::endl;
        std::cout << "1: fantasy" << std::endl;
        std::cout << "2: scienceFiction" << std::endl;
        std::cout << "3: horror" << std::endl;
        std::cout << "4: crime" << std::endl;
        std::cout << "5: romance" << std::endl;
        std::cout << ">";

        std::cin >> cGenre;
        std::cin.ignore(1000, '\n');

    }

    switch(cGenre) {
        case '1': {
            strGenre = "fantasy";
            break;
        case '2':
            strGenre = "scienceFiction";
            break;
        case '3':
            strGenre = "horror";
            break;
        case '4':
            strGenre = "crime";
            break;
        case '5':
            strGenre = "romance";
            break;
        }
    }

    genre = EnumConvert::stringToGenre(strGenre);

    if (bookType == "AudioBook") {
        float lengthHours = Utils::enforceValidFloatInput("Podaj dlugosc w godzinach");
        bool hasMultipleNarrators;
        bool isAiNarrated;
        bool hasSoundEffects;

        std::string narrators;
        std::cout << "Ma wielu narratorow? (T/N)" << std::endl;
        std::cout << ">";
        std::cin >> narrators;
        std::cin.ignore(1000, '\n');

        hasMultipleNarrators = narrators == "T" ? true : false;

        std::string aiNarration;
        std::cout << "Ma narracje AI? (T/N)" << std::endl;
        std::cout << ">";
        std::cin >> aiNarration;
        std::cin.ignore(1000, '\n');

        isAiNarrated = aiNarration == "T" ? true : false;

        std::string soundEffects;
        std::cout << "Ma efekty dzwiekowe? (T/N)" << std::endl;
        std::cout << ">";
        std::cin >> soundEffects;
        std::cin.ignore(1000, '\n');

        isAiNarrated = soundEffects == "T" ? true : false;

        menager.addAudioBook(id,title,author,price,amount,genre,lengthHours,hasMultipleNarrators,isAiNarrated,hasSoundEffects);
        if(!menager.getHasUnsavedChanges()) menager.setHasUnsavedChanges(true);
        return;

    } else if (bookType == "EBook") {
        float fileSizeMB = Utils::enforceValidFloatInput("Podaj rozmiar pliku w MB");
        Format format;

        std::string strFormat;

        char cFormat;

        while (cFormat != '1' && cFormat != '2' && cFormat != '3') {
            std::cout << "Podaj format" << std::endl;
            std::cout << "1: PDF" << std::endl;
            std::cout << "2: EPUB" << std::endl;
            std::cout << ">";

            std::cin >> cFormat;
            std::cin.ignore(1000, '\n');

        }

        switch(cFormat) {
            case '1': {
                strFormat = "PDF";
                break;
            case '2':
                strFormat = "EPUB";
                break;
            }
        }

        format = EnumConvert::stringToFormat(strFormat);

        menager.addEBook(id,title,author,price,amount,genre,fileSizeMB,format);
        if(!menager.getHasUnsavedChanges()) menager.setHasUnsavedChanges(true);

        return;
    } else if (bookType == "PaperBook") {
        int pageCount = Utils::enforceValidIntInput("Podaj ilosc stron");
        CoverType coverType;
        bool hasIllustrations;

        char cCover;
        std::string strCover;

        while (cCover != '1' && cCover != '2' && cCover != '3') {
            std::cout << "Podaj typ okladki" << std::endl;
            std::cout << "1: Twarda" << std::endl;
            std::cout << "2: Miekka" << std::endl;
            std::cout << ">";

            std::cin >> cCover;
            std::cin.ignore(1000, '\n');

        }
        switch(cCover) {
            case '1': {
                strCover = "hardCover";
                break;
            case '2':
                strCover = "paperBack";
                break;
            }
        }

        coverType = EnumConvert::stringToCoverType(strCover);

        std::string illus;
        std::cout << "Ma ilustracje? (T/N)" << std::endl;
        std::cout << ">";
        std::cin >> illus;
        std::cin.ignore(1000, '\n');

        hasIllustrations = illus == "T" ? true : false;
        menager.addPaperBook(id,title,author,price,amount,genre,pageCount,coverType,hasIllustrations);
        if(!menager.getHasUnsavedChanges()) menager.setHasUnsavedChanges(true);
    }
}

void handleBookRemoval(LibraryMenager& menager) {
    int id = Utils::enforceValidIntInput("Podaj id");
    menager.removeBookById(id);
}

void handlePriceChange(LibraryMenager& menager) {
    int id = Utils::enforceValidIntInput("Podaj id");
    float newPrice = Utils::enforceValidFloatInput("Podaj nowa cene");
    menager.changeBookPriceById(id, newPrice);
}

void handleManagementMenu(LibraryMenager& menager) {
    while(true) {
        char choice;
        std::cout << std::endl;
        std::cout << "***ZARZADZANIE STANEM***" << std::endl;
        std::cout << "1: Sprzedaz po id" << std::endl;
        std::cout << "2: Dostawa ksiazki" << std::endl;
        std::cout << "3: Masowa dostawa ksiazek z pliku" << std::endl;
        std::cout << "4: Dodaj ksiazke" << std::endl;
        std::cout << "5: Usun ksiazke" << std::endl;
        std::cout << "6: Zmien cene ksiazki po id" << std::endl;
        std::cout << "7: Menu glowne" << std::endl;

        std::cout << ">";

        std::cin >> choice;
        std::cin.ignore(1000, '\n');

        switch(choice) {
            case '1': {
                handleBookSell(menager);
                break;
            }
            case '2': {
                handleRestock(menager);
                break;
            }
            case '3': {
                handleMassRestock(menager);
                break;
            }
            case '4': {
                handleBookAddition(menager);
                break;
            }
            case '5': {
                handleBookRemoval(menager);
                break;
            }
            case '6': {
                handlePriceChange(menager);
                break;
            }
        }
        if(choice == '7') break;
    }
}

void handleBookCount(LibraryMenager& menager) {
    int bookCount = menager.getAllBookCount();
    std::cout << "Ilosc wszystkich ksiazek (szt): " << bookCount << std::endl;
}

void handleBookValue(LibraryMenager& menager) {
    int allBookValue = menager.getAllBookValue();
    std::cout << "Wartosc wszystkich ksiazek: " << allBookValue << std::endl;
}

void handleBookShortage(LibraryMenager& menager) {
    menager.displayShortage();
}

void handleStatsMenu(LibraryMenager& menager) {
    while(true) {
        char choice;
        std::cout << std::endl;
        std::cout << "***STATYSTYKI KSIEGARNI***" << std::endl;
        std::cout << "1: Ilosc wszystkich ksiazek" << std::endl;
        std::cout << "2: Wartosc wszystkich ksiazek" << std::endl;
        std::cout << "3: Wszystkie ksiazki gdzie ilosc mniejsza niz 5" << std::endl;
        std::cout << "4: Menu glowne" << std::endl;

        std::cout << ">";
        std::cin.ignore(1000, '\n');

        std::cin >> choice;

        switch(choice) {
            case '1': {
                handleBookCount(menager);
                break;
            }
            case '2': {
                handleBookValue(menager);
                break;
            }
            case '3': {
                handleBookShortage(menager);
                break;
            }
        }
        if (choice == '4') break;
    }
}

void handleBookDisplay(LibraryMenager& menager) {
    menager.displayAll();
}

void handleDataBaseSave(LibraryMenager& menager) {
    menager.saveAll();
}

int main()
{
    try {
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);
        LibraryMenager menager(DB_FILE_PATH);

        while(true) {
            char uiChoice;
            displayMainMenu();
            std::cin >> uiChoice;

            switch (uiChoice) {
            case '1':
                try {
                    handleSearchMenu(menager);
                } catch(std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case '2':
                try {
                    handleManagementMenu(menager);
                } catch(std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case '3':
                try {
                    handleStatsMenu(menager);
                } catch(std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case '4':
                try {
                    handleBookDisplay(menager);
                } catch(std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case '5':
                try {
                    handleDataBaseSave(menager);
                } catch(std::runtime_error& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            }
        }
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
