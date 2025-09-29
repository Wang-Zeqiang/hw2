#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <ostream>
#include "datastore.h"

class MyDataStore : public DataStore{

  public:

  MyDataStore();
  ~MyDataStore();

  void addUser(User* u);
  void addProduct(Product* p);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);
  void addCart(const std::string& username, Product* p);
  std::vector<User*> getUsers() const;
  std::vector<Product*> getCarts(const std::string& username) const;
  void buyCart(const std::string& username);

  private:

  std::vector<Product*> products_;
  std::vector<User*> users_;
  std::map<std::string, std::set<Product*>> product_map;
  std::map<std::string, std::vector<Product*>> users_cart;
};


#endif