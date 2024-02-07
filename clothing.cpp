#include "clothing.h"
#include "util.h"
#include <iomanip>
#include <sstream>

Clothing::Clothing(const std::string &category, const std::string &name, double price, int qty,
                   const std::string &size, const std::string &brand)
    : Product(category, name, price, qty), size_(size), brand_(brand) {}

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> brandKeywords = parseStringToWords(brand_);
    keys.insert(brandKeywords.begin(), brandKeywords.end());
    return keys;
}

std::string Clothing::displayString() const
{
    std::ostringstream oss;
    oss << name_ << "\n";
    oss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    oss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Clothing::dump(std::ostream &os) const
{
    os << "clothing" << std::endl;
    os << name_ << std::endl;
    os << std::fixed << std::setprecision(2) << price_ << std::endl;
    os << qty_ << std::endl;
    os << size_ << std::endl;
    os << brand_ << std::endl;
}
