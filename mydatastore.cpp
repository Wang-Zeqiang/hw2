#include <string>
#include <set>
#include <vector>
#include <map>
#include <ostream>
#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore() {
  for(size_t i = 0; i < products_.size(); i++) {
      delete products_[i];
  }
  for(size_t i = 0; i < users_.size(); i++) {
      delete users_[i];
  }
}


void MyDataStore::addUser(User* u){
  users_.push_back(u);
}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);
  set<string> product_key = p->keywords();
  set<string>::iterator it;
  for(it = product_key.begin(); it != product_key.end(); ++it){
    product_map[convToLower(*it)].insert(p);
  }
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type){
  
  vector<Product*> result_vec;
  set<Product*> result;
  bool initialized = false;

  if(terms.empty()){
    return result_vec;
  }

  if(type == 0){
    // AND Search
    for(size_t i = 0; i < terms.size(); i++){
      map<string, set<Product*>>::iterator it = product_map.find(convToLower(terms[i]));
      if(it != product_map.end()){
        if(!initialized){
          result = it->second;
          initialized = true;
        }
        else{
          result = setIntersection(result, it->second);
        }
      }
    }
  }
  else if(type == 1){
    // OR Search
    for(size_t i = 0; i < terms.size(); i++){
      map<string, set<Product*>>::iterator it = product_map.find(convToLower(terms[i]));
      if(it != product_map.end()){
        if(!initialized){
          result = it->second;
          initialized = true;
        }
        else{
          result = setUnion(result, it->second);
        }
      }
    }
  }

  set<Product*>::iterator it2;
  for(it2 = result.begin(); it2 != result.end(); ++it2){
    result_vec.push_back(*it2);
  }

  return result_vec;
}

void MyDataStore::dump(ostream& ofile){
  ofile << "<products>" << endl;
  for(size_t i = 0; i < products_.size(); i++){
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for(size_t i = 0 ; i < users_.size(); i++){
    users_[i]->dump(ofile);
  }
  ofile << "</users>" << endl;
}

void MyDataStore::addCart(const string& username, Product* p){
  users_cart[username].push_back(p);
}

vector<User*> MyDataStore::getUsers() const{
  return users_;
}

vector<Product*> MyDataStore::getCarts(const string& username) const{
  if(users_cart.find(username) != users_cart.end()){
    return users_cart.find(username)->second;
  }
  return vector<Product*>();
}

void MyDataStore::buyCart(const string& username){
  User* customer = nullptr;
  for(size_t i = 0; i < users_.size(); i++){
    if(username == convToLower(users_[i]->getName())){
      customer = users_[i];
      break;
    }
  }

  vector<Product*> Cart_After_Purchase;
  for(size_t i = 0; i < users_cart[username].size(); i++){
    Product* pd = users_cart[username][i];
    if(pd->getQty() > 0 && customer->getBalance() >= pd->getPrice()){
      pd->subtractQty(1);
      customer->deductAmount(pd->getPrice());
    }
    else{
      Cart_After_Purchase.push_back(pd);
    }
  }

  users_cart[username] = Cart_After_Purchase;
}

