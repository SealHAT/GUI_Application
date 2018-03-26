#ifndef SQL_H
#define SQL_H


#include "customerlist.h"
#include "restaurantlist.h"
#include "fooditem.h"
#include "travel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class SQL
{
public:
    SQL();
    ~SQL();

     /***ADD***/
    bool addAccount(Account *a);
    bool addAccount(QString username,QString password);
    bool addPurchase(Account *a);
    bool addPurchase(unsigned short ID,QString restaurant_ID,QString item,unsigned short quantity);
    bool addTravel(Account *a);
    bool addTravel(Travel &travel);

     /***DELETE***/
    bool deleteAccount(const QString &username);
    bool deleteAccount(unsigned short ID);

    /***ACCESSORS***/
    bool receiveAccount(std::list<Customer>& customerList);
    bool receiveAccount(const QString &username,std::list<Customer>& customerList);
    bool receiveAccount(unsigned short ID,std::list<Customer>& customerList);
    bool receiveAccount(CustomerList& customerList);
    bool receivePurchases(std::list<FoodItem> purchaseList);


     /***DISPLAY***/
    void displayAccount();
    void displayAll(QString tablename);
    bool isEmpty();

     /***UPDATE***/
    bool changeDistance(QString username,double newDistance);
    bool changeDistance(int ID,double newDistance);
    /*TRANSFORM*/
    int CustomerList_to_SQL(CustomerList& customerList);
    int SQL_to_CustomerList(CustomerList& customerList);
    int SQL_to_RestaurantList(RestaurantList& restaurantList);
    void RestaurantList_to_SQL(RestaurantList& restaurantList);
    void FoodItem_to_SQL(FoodItem& restaurantList);
    void Travel_to_SQL(Travel& travel);
    /*DISTANCES*/
    QString get_distances();
    void setDistances(const QString& d);


    /*Accessors*/
    void get_FoodItemsWhereID(const int food_ID, std::list<FoodItem> &FoodItemList);
    void get_FoodItems(std::list<FoodItem>& FoodItemList);
    void get_Resurants(std::list<Restaurant>& RestaurantList);
    void get_Resurants(std::vector<QString> &RestaurantList);
    void get_Resurants(RestaurantList &restaurantList);
    void get_ResurantsWhereID(const int res_ID,std::list<Restaurant>& RestaurantList);
    int  get_number_of_Resurants();
    /*PRINT*/
    void printFoods(std::list<FoodItem> FoodItemList);
    void printRestaurants(std::list<Restaurant> RestaurantList);
    /*DRIVER*/
    bool openDataBase();
    bool closeDataBase();
    /*RESTAURANT*/
    bool changeDistance(int ID,QString name,double distance); // will change the distance according to the selcted ID and name.
    bool addRestaurant(int ID, QString name, double distance);
    /*MENU*/
    bool changePrice(int ID,QString item,double price); // will change the price according to the selcted ID and item.
    bool addItem(int ID, QString item, double price);
    /*DELETE ITEM*/
    bool deleteItem(int ID);
    bool deleteItem(int ID,QString item);
    bool deleteItem(int ID,double price);
    bool deleteItem(double price);
    bool deleteItem(int ID,QString item,double price);
    bool deleteItem(QString item);
    /*DELETE Restaurant*/
    bool deleteRestaurant(int ID);
    bool deleteRestaurant(int ID,QString name);
    bool deleteRestaurant(int ID,double distance);
    bool deleteRestaurant(double distance);
    bool deleteRestaurant(int ID,QString name,double distance);
    bool deleteRestaurant(QString name);
private:
    QSqlDatabase _DB;
    QSqlQuery _qry;

};

#endif // SQL_H
