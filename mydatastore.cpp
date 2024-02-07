#include "mydatastore.h"
#include <iterator>
#include <list>

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    for (std::vector<Product *>::iterator it = products.begin(); it != products.end(); it++)
    {
        delete *it;
    }
    
    for (std::unordered_map<std::string, User *>::iterator it = users.begin(); it != users.end(); it++)
    {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product *p)
{
    products.push_back(p);
    addToKeywordMap(p);
}

void MyDataStore::addUser(User *u)
{
    users[u->getName()] = u;
}

std::vector<Product *> MyDataStore::search(std::vector<std::string> &terms, int type)
{
    std::set<Product *> resultSet;
    if (!terms.empty())
    {
        resultSet = std::set<Product *>(keywordMap[terms[0]].begin(), keywordMap[terms[0]].end());

        for (size_t i = 1; i < terms.size(); i++)
        {
            const std::set<Product *> &currentSet = std::set<Product *>(keywordMap[terms[i]].begin(), keywordMap[terms[i]].end());
            std::set<Product *> tempResult;

            if (type == 0)
            {
                tempResult = setIntersection(resultSet, currentSet);
            }
            else
            {
                tempResult = setUnion(resultSet, currentSet);
            }

            resultSet = tempResult;
        }
    }
    hits.clear();
      for (std::set<Product *>::iterator it = resultSet.begin(); it != resultSet.end(); it++)
    {
        if (*it)
        {
            hits.push_back(*it);
        }
        else
        {
            std::cerr << "Nullptr encountered while copying to hits!" << std::endl;
        }
    }
    return hits;
}

void MyDataStore::dump(std::ostream &ofile)
{
    ofile << "<products>" << std::endl;
    for (Product *product : products)
    {
        product->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    
    for (const std::pair<std::string, User *> &userPair : users)
    {
        User *user = userPair.second;
        user->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(std::string &username, int hitResultIndex)
{
    if (users.find(username) == users.end())
    {
        std::cout << "Invalid Request" << std::endl;
        return;
    }

    if (hitResultIndex < 0 || static_cast<size_t>(hitResultIndex) >= products.size())
    {
        std::cout << "Error in search: invalid hitResultIndex" << std::endl;
        return;
    }
    Product *productToAdd = hits[hitResultIndex];
    userCarts[username].push_back(productToAdd);
}

void MyDataStore::viewCart(const std::string &username)
{
    std::unordered_map<std::string, User *>::iterator userIterator = users.find(username);
    if (userIterator == users.end())
    {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    std::list<Product *> &cart = userCarts[username];
    int index = 1;
    for (std::list<Product *>::iterator it = cart.begin(); it != cart.end(); ++it)
    {
        Product *product = *it;
        std::cout << "Index: "<< index <<std::endl;
        std::cout << product->displayString() << std::endl;
        index++;
    }
}
void MyDataStore::buyCart(std::string &username)
{
    std::unordered_map<std::string, User *>::iterator userIterator = users.find(username);

    if (userIterator == users.end())
    {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    std::list<Product *> &cart = userCarts[username];
    for (std::list<Product *>::iterator it = cart.begin(); it != cart.end();)
    {
        Product *product = *it;

        if (product->getQty() > 0)
        {
            double itemCost = product->getPrice();
            if (itemCost <= userIterator->second->getBalance())
            {
                product->subtractQty(1);
                userIterator->second->deductAmount(itemCost);
                it = cart.erase(it);
            }
            else
            { 
                it++;
            }
        }
        else{
            it++;
        }
    }
}

void MyDataStore::addToKeywordMap(Product *p)
{
    std::set<std::string> keywords = p->keywords();
    for (const std::string &keyword : keywords)
    {
        keywordMap[keyword].push_back(p);
    }
}

