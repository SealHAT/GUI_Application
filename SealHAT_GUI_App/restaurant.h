/*
 * restaurant.h
 *
 *  Created on: Feb 15, 2016
 *  Author: krystine
 */

#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <list>
#include <string>
#include <sstream>
#include "fooditem.h"
#include <QString>
#include <map>
using namespace std;

class Restaurant
{
public:
    //CONSTRUCTORS AND DESTRUCTOR
    Restaurant();
    Restaurant (int newRestaurantID, QString newRestaurantName, double newDistance);
    ~Restaurant();

    //MUTATORS - see definition for more detailed descriptions
    void setRestaurantName(QString newRestaurantName);
    void setRestaurantID(int newRestaurantID);
    void setMenu(list<FoodItem*> newMenu);
    void setDistance(int newDistance);
    void changeMenuPrice(QString nameOfItem, float newPrice);
    void addMenuItem(QString fromWhere, QString nameOfItem, float priceOfItem);
    void addDistanceToRestaurant(QString name, double distance);
    bool deleteMenuItem(QString nameOfItem);

    //ACCESSORS - see definition for more detailed descriptions
    QString          getRestaurantName();
    int              getRestaurantID()const;
    list<FoodItem*>  getMenu()const;
    double           getDistance()const;
    string           print()const;
    map<QString, double> getDistancesToRestaurants() const;

private:
    int                  _restaurantID;			    //ID based of SQL db
    QString              _restaurantName;           //The name of the restaurant
    list<FoodItem*>      _menu;				        //All the menu items associated with this restaurant
    double               _distanceFromSaddleback;	//Self explanatory
    map<QString, double> _distanceToRestaurants;

};

#endif /* RESTAURANT_H_ */
