#ifndef TRAVEL_H
#define TRAVEL_H

#include <list>
#include "restaurant.h"

class Travel
{
public:
    Travel();
    Travel(QString username, QString _type, double total, list<Restaurant*> restaurants);

    double getTotalDistanceTraveled();
    list<Restaurant*> getTravelRestaurants();
    int getNumberOfRestaurants();
    bool getTakenTrip();
    QString getType();

    void setTotalDistanceTraveled(double newDistance);
    void setTakenTrip(bool newTripTaken);

private:
    QString _username;
    QString _typeOfTrip;
    double _totalDistanceTraveled;
    bool _takenTrip;
    int _numberOfRestaurants;
    list<Restaurant*> _travelRestaurants;
};

#endif // TRAVEL_H
