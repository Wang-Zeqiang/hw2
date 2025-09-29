#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "util.h"

class Book: public Product{
  public:

  Book(const std::string category, const std::string name, double price, 
       int qty, const std::string ISBN, const std::string author_name);
       
  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream& os) const;

  private:
  std::string ISBN_;
  std::string author_name_;
};

#endif