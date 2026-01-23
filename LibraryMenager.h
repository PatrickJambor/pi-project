#include <vector>
#include <string>

#include "Product.h"

class LibraryMenager {
private:
    std::vector<Product*> products;
    bool hasUnsavedChanges = false;

public:
    std::vector<std::string> splitLine(const std::string& line, const char& delimiter);

    LibraryMenager(const std::string& dbFile);

    void loadBookFromDb(const char& bookType, const std::vector<std::string>& bookInfo);

    void addAudioBook(
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
    );

    void addEBook(
        const int& id,
        const std::string& title,
        const std::string& author,
        const float& price,
        const int& amount,
        const Genre& genre,
        const float& fileSizeMB,
        const Format& format
    );

    void addPaperBook(
        const int& id,
        const std::string& title,
        const std::string& author,
        const float& price,
        const int& amount,
        const Genre& genre,
        const int& pageCount,
        const CoverType& coverType,
        const bool& hasIllustrations
    );

    void searchBooksById(const int& id);
    void searchBooksByTitle(const std::string& title);
    void searchBooksByAuthor(const std::string& author);
    void searchByPriceRange(const int& minPrice, const int& maxPrice);

    void sellBookById(const int& id, const int& sellAmount);

    void restockBookById(const int& id, const int& restockAmount);

    void removeBookById(const int& id);

    void changeBookPriceById(const int& id, const float& newPrice);

    int getAllBookCount();

    int getAllBookValue();

    void displayShortage();

    void saveAll();
    void displayAll();

    void setHasUnsavedChanges(bool unsavedChanges);

    bool getHasUnsavedChanges();

    bool idAlreadExists(const int& id);

    void massRestock();

};
