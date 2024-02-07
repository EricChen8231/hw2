#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

std::set<std::string> parseStringToWords(std::string line)
{
    std::set<std::string> words;
    std::stringstream ss(line);
    std::string word;
    char c;
    while (ss.get(c))
    {
        if (std::isalnum(c) || c == '-')
        {
            word += c;
        }
        else if (!word.empty())
        {
            if (word.size() >= 2)
            {
                word = convToLower(word);
                words.insert(word);
            }
            word.clear();
        }
        if (std::ispunct(c))
        {
            if (!word.empty() && word.size() >= 2)
            {
                word = convToLower(word);
                words.insert(word);
            }
            word.clear();
        }
    }
    if (!word.empty() && word.size() >= 2)
    {
        word = convToLower(word);
        words.insert(word);
    }
    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
