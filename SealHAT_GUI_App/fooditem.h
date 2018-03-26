/*
 * restaurants.h
 *
 *  Created on: Feb 15, 2016
 *  Author: oz
 */

#ifndef FOODITEM_H
#define FOODITEM_H

#include <QString>
using namespace std;

class FoodItem
{
public:
    //CONSTRUCTORS AND DESTRUCTOR
    FoodItem();
    FoodItem(QString newName, double newPrice, unsigned short newQuantity);
    FoodItem(int id,QString newName, double newPrice, unsigned short newQuantity);
    FoodItem(QString newFromWhere,QString newName, float newPrice, unsigned short newQuantity);
    ~FoodItem();

    // ACCESSORS - Retrieves attributes
    QString getName() const;
    double getPrice() const;
    unsigned short getQuantity() const;
    QString getFromWhere() const;
    int getAccountID() const;

    // MUTATORS - Sets all attributes
    void setFromWhere(QString newFromWhere);
    void setPrice(double newPrice);
    void setName(QString newName);
    void setQuantity(unsigned short newQuantity);


private:
    int            _account_ID;
    QString        _fromWhere;
    QString        _name;
    double         _price;
    unsigned short _quantity;

};

#endif // FOODITEM_H

