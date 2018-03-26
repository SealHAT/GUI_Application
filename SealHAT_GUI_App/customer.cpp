#include "customer.h"

/*  CONSTRUCTOR & DESTRUCTORS  */
Customer::Customer() {

}

Customer::Customer(int id, QString user, QString pass) : Account(user, pass) {
    _ID = id;
}

Customer::Customer(QString user, QString pass) : Account(user, pass) {

}

Customer::~Customer() {

}

/*  MUTATORS  */
void Customer::displayCustomer() const {

}

/* ACCESSORS */
QString Customer::getUsername() const {
    return _username;
}
QString Customer::getPasword() const {
    return _password;
}

list<FoodItem*> Customer::getPurchaseList() const {
    return _purchaseList;
}
list<FoodItem*> Customer::getShoppingCart() const {
    return _shoppingCart;
}

void Customer::addPurchase(FoodItem* pro) {

}

void Customer::addToCart(FoodItem* pro) {

}

bool Customer::removeCart(QString removeFoodItem) {

}

bool Customer::purchase() {

}

void Customer::setID(unsigned short ID)
{
    _ID = ID;
}

unsigned short Customer::getID() const
{
    return _ID;
}

