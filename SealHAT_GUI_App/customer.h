#ifndef CUSTOMER_H
#define CUSTOMER_H

/**
 * @file  Customer.h
 * @class Customer
 *
 * @brief Customer class inherits from Account class
 * @author Sarah Singletary
 * @date	05NOV2015
 */

/* PRE-PROCESSOR INCLUDES */
#include "account.h"
#include "fooditem.h"
#include "travel.h"
#include <list>

class Customer : public Account
{

    public:
        /*  CONSTRUCTOR & DESTRUCTORS  */
        Customer();
        virtual ~Customer();
        Customer(QString user, QString pass);
        Customer (int id, QString user, QString pass);

        /*  MUTATORS  */
        void displayCustomer()const;
        void setID(unsigned short ID);


        /* ACCESSORS */
        QString getUsername() const;
        QString getPasword() const;
        list<FoodItem*> getPurchaseList() const;
        list<FoodItem*> getShoppingCart() const;

        void addPurchase(FoodItem* pro);
        void addToCart(FoodItem* pro);
        bool removeCart(QString removeFoodItem);
        unsigned short getID()const;
        bool purchase();


    private:
        int _ID;
        list<FoodItem*> _shoppingCart;
        list<FoodItem*> _purchaseList;
        list<Travel*> _travelLog;
};


#endif // CUSTOMER_H
