#include "restaurantlist.h"
#include <QtDebug>
#include <iostream>


/**********************************
 **   CONSTRUCTOR & DESTRUCTOR   **
 **********************************/
/**
* @brief Default Constructor - does nothing in particular
* @return Void
*/
RestaurantList::RestaurantList()
{}

/**
* @brief Default Destructor - does nothing in particular
* @return Void
*/
RestaurantList::~RestaurantList()
{}


/**********************************
 **          MUTATORS            **
 **********************************/

/**
 * @brief RestaurantList::RestaurantList
 * @param pointer to a customer object
 * @return true or false if the customer was added successfully
 */
bool RestaurantList::addRestaurant(Restaurant* r)
{
   return addRestaurant(r->getRestaurantID(), r->getRestaurantName(), r->getDistance());
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
bool RestaurantList::addRestaurant(int id, QString name, double distance)
{

    Restaurant  *newRestaurant      = NULL;

    newRestaurant = new Restaurant(id, name, distance);

    return push(newRestaurant);
}

bool RestaurantList::push(Restaurant *newRestaurant)
{
    restaurants.push_front(newRestaurant);
    return true;
}

///**
//* @brief Deletes a customer object to in list by customer name
//* @param [in] delName The customer number of the customer to delete
//* @return TRUE if successful
//*/
//bool CustomerList::deleteCustomer(QString delName)
//{
//    bool found = false;
//    list<Account*>::iterator it = _accountList.begin();
//    while (it != _accountList.end() && !found) {
//        if(delName != (*it)->getUsername()) {
//            ++it;
//        }
//    else {
//        found = true;
//        }
//    }
//    if(found){
//        _accountList.erase(it);
//    }
//    return found;
//}


Restaurant* RestaurantList::findRestaurantByName(QString name) {
    bool found = false;
    Restaurant* foundRestaurant = NULL;

    list<Restaurant*>::iterator it = restaurants.begin();
    while (it != restaurants.end() && !found) {
        if(name != (*it)->getRestaurantName()) {
            ++it;
        }
        else {
            found = true;
            foundRestaurant = (*it);
        }
    }
    return foundRestaurant;
}

Restaurant* RestaurantList::findRestaurantByID(int ID) {
    bool found = false;
    Restaurant* foundRestaurant = NULL;

    list<Restaurant*>::iterator it = restaurants.begin();
    while (it != restaurants.end() && !found) {
        if(ID != (*it)->getRestaurantID()) {
            ++it;
        }
        else {
            found = true;
            foundRestaurant = (*it);
        }
    }
    return foundRestaurant;
}

bool RestaurantList::isEmpty() {
        return restaurants.empty();
}
