#pragma once // to prevent multiple imports
#include <string>
#include "product.h"

class EBook : public Product {
private:
    float fileSizeMB;
    Format format;

public:
    EBook(
    const int& id,
    const std::string& title,
    const std::string& author,
    const float& price,
    const int& amount,
    const Genre& genre,
    const float& fileSizeMB,
    const Format& format
    ) : Product(id, title, author, genre, price, amount) {}

    ~EBook() {}

    void compare(const Product& p) override;

    std::string toString() override;

    float getFileSizeMB();
    Format getFormat();

};


