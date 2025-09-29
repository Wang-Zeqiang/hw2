#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include "clothing.h"
#include "product.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const string category, const string name, double price, 
                   int qty, const string brand_name, const string size)
                  :Product(category, name, price, qty)
{
  brand_name_ = brand_name;
  size_ = size;
}

set<string> Clothing::keywords() const{
  set<string> key1 = parseStringToWords(name_);
  set<string> key2 = parseStringToWords(brand_name_);
  set<string> key = setUnion(key1, key2);
  return key;
}

string Clothing::displayString() const{
  string s1 = name_ + '\n';
  string s2 = "Size: " + size_ + " Brand: " + brand_name_ + '\n';
  string s3 = to_string(price_) + " " + to_string(qty_) + " left." + '\n';
  return s1+s2+s3;
}

void Clothing::dump(ostream& os) const{
  os << "clothing" << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << size_ << endl;
  os << brand_name_ << endl;
}
