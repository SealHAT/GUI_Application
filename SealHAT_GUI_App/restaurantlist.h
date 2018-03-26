#ifndef RESTAURANTLIST_H
#define RESTAURANTLIST_H

#include "restaurant.h"
#include <list>
#include <iterator>
class RestaurantList{
public:
    list<Restaurant*> restaurants;

    RestaurantList();
    ~RestaurantList();

    bool addRestaurant(Restaurant* r);
    bool addRestaurant(int id,
                      QString name,
                      double distance);
    bool deleteRestaurant(QString delName);
    bool push(Restaurant* r);
    Restaurant* front() { return restaurants.front(); };
    void popFront() { restaurants.pop_front(); };
    void pushBack(Restaurant* r) { restaurants.push_back(r); };
    bool isEmpty();
    Restaurant* findRestaurantByName(QString name);
    Restaurant* findRestaurantByID(int ID);


};


#endif // RESTAURANTLIST_H

