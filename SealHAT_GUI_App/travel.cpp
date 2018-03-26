#include "travel.h"

Travel::Travel()
{
    _typeOfTrip = "NONE";
    _totalDistanceTraveled = 0;
    _numberOfRestaurants = 0;
    _takenTrip = false;

}

Travel::Travel(QString username, QString type, double total, list<Restaurant*> restaurants) {
    _username = username;
    _typeOfTrip = type;
    _totalDistanceTraveled = total;
    _travelRestaurants = restaurants;
    _takenTrip = false;
}

QString Travel::getType() {
    return _typeOfTrip;
}

double Travel::getTotalDistanceTraveled() {
    return _totalDistanceTraveled;
}

list<Restaurant*> Travel::getTravelRestaurants() {
    return _travelRestaurants;
}

int Travel::getNumberOfRestaurants() {
    return _travelRestaurants.size();
}

bool Travel::getTakenTrip() {
    return _takenTrip;

}

void Travel::setTotalDistanceTraveled(double newDistance) {
    _totalDistanceTraveled = newDistance;
}

void Travel::setTakenTrip(bool newTripTaken) {
    _takenTrip = newTripTaken;
}
