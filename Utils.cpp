#include "Utils.h"

std::string Utils::getFloatWithPrecision(const float& val, const int& precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << val;
    return ss.str();
}

std::string Utils::getFormalBookType(const char& bookType) {
    switch(bookType) {
        case 'A': return "Audio Book";
        case 'E': return "Ebook";
        case 'P': return "Ksiazka";
    }
    return "Produkt";
}

std::string Utils::getFormalCoverType(const std::string& coverType) {
    if (coverType == "hardCover") return "Twarda";
    else if (coverType == "paperBack") return "Miekka";
    return "NULL";
}

std::string Utils::boolToPolish(bool b) {
    switch(b) {
    case true:
        return "TAK";
    default: return "NIE";
    }
    return "NIE";
}

std::string Utils::engTextBoolToPolish(std::string engBool) {
    if (engBool == "true") return "TAK";
    else return "NIE";
}

bool Utils::isInt(const std::string& input) {
    const char ns[10] = {'0','1','2','3','4','5','6','7','8','9'};

    if (input == "") return false; // na

    if (input.size() > 9) {
        std::cout << "Nieprawidlowe dane. Oczekiwano liczby calkowitej (0-999999999)" << std::endl;
        return false;
    }
    for (const char& c : input) {

        bool isInt = false;
        for (const char& n : ns) {
            if (c == n) {
                isInt = true;
                break;
            }
        }
        if (!isInt) {
            std::cout << "Nieprawidlowe dane. Oczekiwano liczby calkowitej (0-999999999)" << std::endl;
            return false;
        }
    }
    return true;
}

bool Utils::isFloat(const std::string& input) {
    if (input == "") return false;

    try {
        float f = std::stof(input);
        return true;
    } catch (std::exception& e) {
        std::cout << "Nieprawidlowe dane. Oczekiwano liczby" << std::endl;
    }
    return false;
}

int Utils::enforceValidIntInput(const std::string& message) {
    int n;
    std::string s = "";

    while (!Utils::isInt(s)) {
        std::cout << message << std::endl;
        std::cout << ">";
        std::cin >> s;
        std::cin.ignore(1000, '\n');
    }
    return std::stoi(s);
}

float Utils::enforceValidFloatInput(const std::string& message) {
    float f;
    std::string s = "";

    while (!Utils::isFloat(s)) {
        std::cout << message << std::endl;
        std::cout << ">";
        std::cin >> s;
        std::cin.ignore(1000, '\n');
    }
    return std::stof(s);
}
