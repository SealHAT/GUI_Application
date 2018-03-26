#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <QString>
#include <QDebug>
#include "fooditem.h"

using namespace std;

class Account
{
public:
    Account();
    Account(QString user, QString pass);
    virtual ~Account();

    /****************
     *   ACCESSORS
     ***************/
    QString getUsername() const;
    QString getPassword() const;
    virtual list<FoodItem*> getPurchaseList() const;


    // Used to access customers attributes


    /**************************
     *        MUTATORS
     *************************/

    // Validfying login in
    bool validLogin(QString tempUser, QString tempPass);

protected:
    bool usernameMatch(QString tempUser);
    bool passwordMatch(QString tempPass);

    // Attributes
    QString _username;
    QString _password;
};
#endif // ACCOUNT_H
