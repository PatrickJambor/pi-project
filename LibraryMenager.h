#include <vector>
#include <string>

#include "Product.h"

class LibraryMenager {
private:
    std::vector<Product*> products;

public:
    bool hasUnsavedChanges = false;

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

    void saveAll();
};
