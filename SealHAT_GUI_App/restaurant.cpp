/*
* restaurants.cpp
*
*  Created on: Feb 15, 2016
*      Author: krystine
*/

#include "restaurant.h"

//CONSTRUCTORS AND DESTRUCTOR

//Default Constructor
Restaurant::Restaurant()
{
    _restaurantName         = "";
    _restaurantID           = 0;
    _distanceFromSaddleback = 0;
}

//Non-default constructor
Restaurant::Restaurant(int newRestaurantID, QString newRestaurantName, double newDistance)
{
    _restaurantName         = newRestaurantName;
    _restaurantID           = newRestaurantID;
    _distanceFromSaddleback = newDistance;
}

//Destructor
Restaurant::~Restaurant()
{

    if(_menu.size() != 0)
        _menu.clear();
}

//MUTATORS

/*************************************************************
 * setRestaurantID
 * ----------------------------------------------------------
 * Sets restaurant ID attribute. Each restaurant has a
 * specific index number assigned to it by Jerry
 ************************************************************/
void Restaurant::setRestaurantID(int newRestaurantID)
{
    _restaurantID = newRestaurantID;
}

/*************************************************************
 * setMenu
 * ----------------------------------------------------------
 * Contains a list of food items for the current restaurant.
 * A food item object consists of: name, price and
 * quantity.
 ************************************************************/
void Restaurant::setMenu(list<FoodItem*> newMenu)
{
    _menu = newMenu;
}


/*************************************************************
 * setDistance
 * ----------------------------------------------------------
 * Sets the distance to the restaurant from Saddleback
 * College.
 ************************************************************/
void Restaurant::setDistance(int newDistance)
{
    _distanceFromSaddleback = newDistance;
}



/*************************************************************
 * addMenuItem
 * ----------------------------------------------------------
 * Adds a new menu item along with its corresponding price
 * to the appropriate lists. Both the menu items and the
 * menu prices lists are updated.
 ************************************************************/
void Restaurant::addMenuItem(QString fromWhere, QString nameOfItem, float priceOfItem)
{
    _menu.push_back((new FoodItem(fromWhere, nameOfItem, priceOfItem, 0)));
}


//ACCESSORS
QString Restaurant::getRestaurantName() {
    return _restaurantName;
}

int Restaurant::getRestaurantID()const
{
    return _restaurantID;
}

list<FoodItem*> Restaurant::getMenu()const
{
    return _menu;
}

double Restaurant::getDistance() const
{
    return _distanceFromSaddleback;
}

void Restaurant::addDistanceToRestaurant(QString name, double distance) {
    _distanceToRestaurants.insert(pair<QString, double>(name, distance));
}

map<QString, double> Restaurant::getDistancesToRestaurants() const {
    return _distanceToRestaurants;
}
