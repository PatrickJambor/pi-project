#pragma once // to prevent multiple imports
#include <string>

#include "enum.h"

class Product {
protected:
    int id;
    std::string title;
    std::string author;
    float price;
    int amount;
    Genre genre;

public:
    Product(
        const int& id,
        const std::string& title,
        const std::string& author,
        const Genre& genre,
        const float& price,
        const int& amount
    );

    virtual ~Product() {}

    virtual void compare(const Product& p) = 0;

    virtual std::string toString() = 0;

    void sell();

    void changePrice(const float& newPrice);

    int getId();
    std::string getTitle();
    std::string getAuthor();
    float getPrice();
    int getAmount();
    Genre getGenre();
};

