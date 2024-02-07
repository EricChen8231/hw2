#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>
Movie::Movie(const std::string &category, const std::string &name, double price, int qty,
             const std::string &genre, const std::string &rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> genreWords = parseStringToWords(genre_);
    keys.insert(genreWords.begin(), genreWords.end());
    return keys;
}

std::string Movie::displayString() const
{
    std::ostringstream oss;
    oss << name_ << "\n";
    oss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    oss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Movie::dump(std::ostream &os) const
{
    os << "movie" << std::endl;
    os << name_ << std::endl;
    os << std::fixed << std::setprecision(2) << price_ << std::endl;
    os << qty_ << std::endl;
    os << genre_ << std::endl;
    os << rating_ << std::endl;
}
