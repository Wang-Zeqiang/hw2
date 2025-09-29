#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include "book.h"
#include "product.h"
#include "util.h"

using namespace std;

Book::Book(const string category, const string name, 
           double price, int qty, const string ISBN, 
           const string author_name):Product(category, name, price, qty)
{
  ISBN_ = ISBN;
  author_name_ = author_name;
}

set<string> Book::keywords() const{
  set<string> key1 = parseStringToWords(name_);
  set<string> key2 = parseStringToWords(author_name_);
  set<string> key = setUnion(key1, key2);
  key.insert(ISBN_);
  return key;
}

string Book::displayString() const{
  string s1 = name_ + '\n';
  string s2 = "Author: " + author_name_ + " ISBN: " + ISBN_ + '\n';
  string s3 = to_string(price_) + " " + to_string(qty_) + " left." + '\n';
  return s1+s2+s3;
}

void Book::dump(ostream& os) const{
  os << "book" << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << ISBN_ << endl;
  os << author_name_ << endl;
}
