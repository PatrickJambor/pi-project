#include "Product.h"

Product::Product(
    const int& id,
    const std::string& title,
    const std::string& author,
    const Genre& genre,
    const float& price,
    const int& amount) :
    id(id),
    title(title),
    author(author),
    price(price),
    amount(amount) {}

void Product::sell() {
    amount--;
}

void Product::changePrice(const float& newPrice) {
    price = newPrice;
}

int Product::getId() {
    return id;
}

std::string Product::getTitle() {
    return title;
}

std::string Product::getAuthor() {
    return author;
}

float Product::getPrice() {
    return price;
}

int Product::getAmount() {
    return amount;
}

Genre Product::getGenre() {
    return genre;
}
