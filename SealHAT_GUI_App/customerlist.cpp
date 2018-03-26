#include "customerlist.h"
#include <QtDebug>
#include <iostream>


/**********************************
 **   CONSTRUCTOR & DESTRUCTOR   **
 **********************************/
/**
* @brief Default Constructor - does nothing in particular
* @return Void
*/
CustomerList::CustomerList()
{}

/**
* @brief Default Destructor - does nothing in particular
* @return Void
*/
CustomerList::~CustomerList()
{}


/**********************************
 **          MUTATORS            **
 **********************************/

/**
 * @brief CustomerList::AddCustomer
 * @param pointer to a customer object
 * @return true or false if the customer was added successfully
 */
bool CustomerList::addCustomer(Customer* c)
{
   return addCustomer(c->getUsername(),c->getPasword());
}

/**
* @brief Adds a customer object to the list (public)
* @param [in] name            A string to set customer's company name
* @param [in] address         A string to set customer's company address
* @param [in] customersRating A string of the rating of a customer
* @param [in] keyCustomer     A bool if a customer is key or nice to have
* @param [in] pamphletSent    A bool comfirming if a pamphlet was sent or not
* @param [in] year    An unsigned short to set member's expiration date
* @param [in] total   A double to set member's total spent
* @return TRUE if successful
*/
bool CustomerList::addCustomer(QString         username,
                               QString         password)
{

    Account  *newAcct      = NULL;
    Customer *newCustomer  = NULL;

    newCustomer = new Customer(username, password);
    newAcct = newCustomer;

    return push(newAcct);
}

bool CustomerList::push(Account *newAcct)
{
    _accountList.push_front(newAcct);
    return true;
}

/**
* @brief Deletes a customer object to in list by customer name
* @param [in] delName The customer number of the customer to delete
* @return TRUE if successful
*/
bool CustomerList::deleteCustomer(QString delName)
{
    bool found = false;
    list<Account*>::iterator it = _accountList.begin();
    while (it != _accountList.end() && !found) {
        if(delName != (*it)->getUsername()) {
            ++it;
        }
    else {
        found = true;
        }
    }
    if(found){
        _accountList.erase(it);
    }
    return found;
}


/**
 * @brief CustomerList::FindCustomerByUsername
 * @param userName
 * @return a pointer to Account
 */
Account* CustomerList::findCustomerByUsername(QString userName) {
    bool found = false;
    Account* foundAccount = NULL;

    list<Account*>::iterator it = _accountList.begin();
    while (it != _accountList.end() && !found) {
        if(userName != (*it)->getUsername()) {
            ++it;
        }
        else {
        found = true;
        foundAccount = (*it);
        }
    }
    return foundAccount;
}

/**
 * @brief CustomerList::ValidAccount
 * @param [in] tempUser
 * @param [in] tempPass
 * @return the valid account
 */
Account* CustomerList::validAccount(QString tempUser, QString tempPass) {

    Account* loginAccount = NULL;
    bool found = false;

    list<Account*>::iterator it = _accountList.begin();
    while (it != _accountList.end() && !found) {
        QString capitalUsername = (*it)->getUsername();
        if(tempUser.toUpper() != capitalUsername.toUpper()) {
            ++it;
        }
        else {
            if(tempPass == (*it)->getPassword()) {
                found = true;
                loginAccount = (*it);
            }
            else {
                ++it;
            }
        }
    }

    return loginAccount;
}

/**
 * @brief CustomerList::isUniqueUsername
 * @param username
 * @return isUnique: boolean true or false
 */
bool CustomerList::isUniqueUsername(QString username) {
    bool isUnique = false;

    list<Account*>::iterator it = _accountList.begin();
    while (it != _accountList.end() && !isUnique) {
        if(username == (*it)->getUsername()) {
           isUnique = true;
        }
        else {
           it++;
        }
    }

    return isUnique;
}

bool CustomerList::pop_front() {
    _accountList.pop_front();
    return true;
}

Account* CustomerList::front() {
    return _accountList.front();
}

