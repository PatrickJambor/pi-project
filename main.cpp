#include <stdexcept>
#include <iostream>

#include "Product.h"
#include "AudioBook.h"
#include "EBook.h"
#include "PaperBook.h"
#include "LibraryMenager.h"

const std::string DB_FILE_PATH = "db.txt";

void displayMainMenu() {
    std::cout << "***SYSTEM ZARZADZANIA KSIEGARNIA***" << std::endl;
    std::cout << std::endl;
    std::cout << "***MENU GLOWNE***" << std::endl;

    std::cout << "1: Wyszukiwanie" << std::endl;
    std::cout << "2: Zarzadzanie stanem" << std::endl;
    std::cout << "3: Raporty" << std::endl;

    std::cout << ">>";
}

void handleSearchMenu() {
    std::cout << "***WYSZUKIWANIE KSIAZEK***" << std::endl;
    std::cout << "1: Po id" << std::endl;
    std::cout << "2: Po tytule" << std::endl;
    std::cout << "3: Po autorze" << std::endl;
    std::cout << "4: Po gatunku" << std::endl;
    std::cout << "5: Po typie" << std::endl;
    std::cout << "6: Po zakresie cenowym" << std::endl;
    std::cout << "7: MENU GLOWNE" << std::endl;
}

void handleManagementMenu() {
    std::cout << "***ZARZADZANIE STANEM***" << std::endl;
    std::cout << "1: Sprzedaz po id" << std::endl;
    std::cout << "2: Dostawa ksiazki" << std::endl;
    std::cout << "3: Masowa dostawa" << std::endl;
    std::cout << "4: Zmiany ceny ksiazki" << std::endl;
    std::cout << "5: Promocja na gatunek" << std::endl;
    std::cout << "6: Promocja na typ ksiazek" << std::endl;
    std::cout << "7: MENU GLOWNE" << std::endl;
}

void handleStatsMenu() {
    std::cout << "***WYSZUKIWANIE KSIAZEK***" << std::endl;
    std::cout << "1: Po id" << std::endl;
    std::cout << "2: Po tytule" << std::endl;
    std::cout << "3: Po autorze" << std::endl;
    std::cout << "4: Po gatunku" << std::endl;
    std::cout << "5: Po typie" << std::endl;
    std::cout << "6: Po zakresie cenowym" << std::endl;
    std::cout << "7: MENU GLOWNE" << std::endl;
}

int main()
{
    try {
        LibraryMenager menager(DB_FILE_PATH);

        while(true) {
            char uiChoice;
            displayMainMenu();
            std::cin >> uiChoice;

            switch (uiChoice) {
            case 1:
                handleSearchMenu();
                break;
            case 2:
                handleManagementMenu();
                break;
            case 3:
                handleStatsMenu();
                break;
            }
        }

    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
