#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

class MyDataStore : public DataStore
{
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product *p) override;
    void addUser(User *u) override;
    std::vector<Product *> search(std::vector<std::string> &terms, int type) override;
    void dump(std::ostream &ofile) override;

    void addToCart(std::string &username, int hitResultIndex);
    void viewCart(const std::string &username);
    void buyCart(std::string &username);

private:
    std::vector<Product *> products;
    std::unordered_map<std::string, User *> users;
    std::unordered_map<std::string, std::vector<Product *>> keywordMap;
    std::unordered_map<std::string, std::list<Product *>> userCarts;
    std::vector<Product *> hits;
    // Helper methods
    void addToKeywordMap(Product *p);
};

#endif
