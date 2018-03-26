#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H

/* PRE-PROCESSOR INCLUDES */
#include <list>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "customer.h"


class CustomerList
{
public:
    list<Account*> _accountList;

    /*  CONSTRUCTOR & DESTRUCTORS  */
    CustomerList();
    ~CustomerList();

    /* MUTATORS */
    bool addCustomer(Customer* c);
    bool addCustomer(QString         username,
                     QString         password);
    bool deleteCustomer(QString delName);
    bool pop_front();
    Account* front();

    /* ACCESSORS */
    bool isEmpty() const { return _accountList.empty(); }
    Account* findCustomerByUsername(QString userName);
    Account* validAccount(QString tempUser, QString tempPass);
    bool isUniqueUsername(QString username);

protected:
    bool push(Account *newAcct);
};

#endif // CUSTOMERLIST_H
