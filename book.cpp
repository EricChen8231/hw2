#include "book.h"
#include "util.h"
#include <iomanip>
#include <sstream>

Book::Book(const std::string &category, const std::string &name, double price, int qty,
           const std::string &isbn, const std::string &author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

Book::~Book() {}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> authorKeywords = parseStringToWords(author_);
    keys.insert(authorKeywords.begin(), authorKeywords.end());
    keys.insert(isbn_);
    return keys;
}

std::string Book::displayString() const
{
    std::ostringstream oss;
    oss << name_ << "\n";
    oss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    oss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Book::dump(std::ostream &os) const
{
    os << "book" << std::endl;
    os << name_ << std::endl;
    os << std::fixed << std::setprecision(2) << price_ << std::endl;
    os << qty_ << std::endl;
    os << isbn_ << std::endl;
    os << author_ << std::endl;
}