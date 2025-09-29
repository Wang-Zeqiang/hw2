#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include "movie.h"
#include "product.h"
#include "util.h"

using namespace std;

Movie::Movie(const string category, const string name, 
             double price, int qty, const string genre, const string rating)
            :Product(category, name, price, qty)
{
  genre_ = genre;
  rating_ = rating;
}

set<string> Movie::keywords() const{
  set<string> key = parseStringToWords(name_);
  key.insert(convToLower(genre_));
  key.insert(convToLower(rating_));
  return key;
}

string Movie::displayString() const{
  string s1 = name_ + '\n';
  string s2 = "Genre: " + genre_ + " Rating: " + rating_ + '\n';
  string s3 = to_string(price_) + " " + to_string(qty_) + " left." + '\n';
  return s1+s2+s3;
}

void Movie::dump(ostream& os) const{
  os << "movie" << endl;
  os << name_ << endl;
  os << price_ << endl;
  os << qty_ << endl;
  os << genre_ << endl;
  os << rating_ << endl;
}
