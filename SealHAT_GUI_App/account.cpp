
#include "account.h"

/**
 * @brief Account::Account
 */
Account::Account()
{
    _username = "";
    _password = "";
}

/**
 * @brief Account::Account
 * @param user
 * @param pass
 */
Account::Account(QString user, QString pass) {
    _username = user;
    _password = pass;
}

/**
 * @brief Account::~Account
 */
Account::~Account() {
    _username = "";
    _password = "";
}

/**
 * @brief Account::validLogin
 * @param tempUser
 * @param tempPass
 * @return if username and password match
 */
bool Account::validLogin(QString tempUser, QString tempPass) {

    return usernameMatch(tempUser) && passwordMatch(tempPass);
}

/**
 * @brief Account::usernameMatch
 * @param tempUser
 * @return if username match
 */
bool Account::usernameMatch(QString tempUser) {
    return _username == tempUser;
}

/**
 * @brief Account::passwordMatch
 * @param tempPass
 * @return if password match
 */
bool Account::passwordMatch(QString tempPass) {
    return _password == tempPass;
}

/**
 * @brief Account::getPassword
 * @return attribute: _password
 */
QString Account::getPassword() const {
    return _password;
}

/**
 * @brief Account::getUsername
 * @return attribute: _username
 */
QString Account::getUsername() const {
    return _username;
}


/**
 * @brief Account::getPurchaseList
 * @return
 */
list<FoodItem*> Account::getPurchaseList() const {
    list<FoodItem*> null;
    return null;
}
