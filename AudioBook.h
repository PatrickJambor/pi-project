#pragma once // to prevent multiple imports
#include <string>
#include "product.h"

class AudioBook : public Product {
private:
    float lengthHours;
    bool hasMultipleNarrators;
    bool isAiNarrated;
    bool hasSoundEffects;

public:
    AudioBook(
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
    ) : Product(id, title, author, genre, price, amount) {}

    ~AudioBook() {}

    void compare(const Product& p) override;

    std::string toString() override;

    float getLengthHours();
    bool getHasMultipleNarrators();
    bool getIsAiNarrated();
    bool getHasSoundEffects();
};


