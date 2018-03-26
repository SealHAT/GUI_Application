#include "sql.h"

SQL::SQL()
{
    _DB = QSqlDatabase::addDatabase("QSQLITE");

    /** REMEMBER EACH COMPUTER HAS A DIFFERENT PATH **/

    _DB.setDatabaseName("/Users/sarahsingletary/Documents/QT\ Workspace/quasar/fastfoodfantasy/sqlite/fast_food_fantasy.db");
    openDataBase();
    _qry = QSqlQuery(_DB);

      if(_DB.isOpen())
      {
          qDebug()<<"Data Base account is open";
          _DB.exec("PRAGMA foreign_keys=ON;");
      }
      else
          qDebug()<<"data base not open";
}

/**
 * @brief SQL_Account::~SQL_Account
 */
SQL::~SQL() {closeDataBase();qDebug()<<"data base closing";}


/**
 * @brief SQL_Account::addAccount
 * @param tableName
 * @param a
 * @return T/F if successfully added
 */
bool SQL::addAccount(Account *a)
{
    QSqlQuery query;
    query.prepare("INSERT into account(ID,username,password)"
                  "values(NULL,:username,:password);");
    query.bindValue(":username",a->getUsername());
    query.bindValue(":password",a->getPassword());
    return query.exec();
}
/*!
 * \brief SQL_Account::addAccount
 * \param username
 * \param password
 * \return
 */
bool SQL::addAccount(QString username,QString password)
{
    QSqlQuery query;
    query.prepare("INSERT into account(ID,username,password)"
                  "values(NULL,:username,:password);");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    return query.exec();
}


/**
 * @brief SQL_Account::deleteAccount
 * @param tableName
 * @param arg1
 * @return T/F if deleted successfully
 */
bool SQL::deleteAccount(const QString &username)
{
    QSqlQuery query;
    query.prepare("DELETE FROM account WHERE username=:username;");
    query.bindValue(":username",username);
    return query.exec();
}

/**
 * @brief SQL_Account::deleteAccount
 * @param tableName
 * @param arg1
 * @return T/F if deleted successfully
 */
bool SQL::deleteAccount(unsigned short ID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM account WHERE ID=:ID;");
    query.bindValue(":ID",ID);
    return query.exec();
}
/**
 * @brief SQL::receiveAccount
 * @param tableName
 * @param arg1
 * @return T/F if recieved successfully
 */
bool SQL::receiveAccount(unsigned short ID,std::list<Customer>& customerList)
{
    bool valid;
     QString query = "SELECT * FROM account WHERE ID =\"" + QString::number(ID) + "\";";

      if(_qry.exec(query))
      {
          valid = true;
          qDebug()<<"(receive account )is select" << _qry.isSelect();
          while(_qry.next())
          {
            customerList.push_back(*(new Customer(_qry.value(0).toInt(),_qry.value(1).toString(),_qry.value(2).toString())));
          }
       }
      else
      {
          valid = false;
          qDebug() << "recieve query not valid";
      }
      return valid;
}
bool SQL::receiveAccount(CustomerList& customerList)
{
    bool valid;
     QString query = "SELECT * FROM account;";

      if(_qry.exec(query))
      {
          valid = true;
          qDebug()<<"(receive account )is select" << _qry.isSelect();
          while(_qry.next())
          {
              Customer *c = new Customer(_qry.value(0).toInt(),_qry.value(1).toString(),_qry.value(2).toString());
            customerList.addCustomer(c);
          }
       }
      else
      {
          valid = false;
          qDebug() << "recieve query not valid";
      }
      return valid;
}
bool SQL::receiveAccount(std::list<Customer>& customerList)
{
    bool valid=false;
    QString query ="SELECT * FROM account;";
    if(_qry.exec(query))
    {
        valid = true;
        while(_qry.next())
        {
            customerList.push_back(*(new Customer(_qry.value(0).toInt(),_qry.value(1).toString(),_qry.value(2).toString())));
        }
    }
    return valid;
}

/**
 * @brief SQL::displayAccount
 */
void SQL::displayAccount()
{

     QString query = "SELECT * FROM account;";

      if(_qry.exec(query))
      {
          qDebug()<<"ID | username | password |";
          qDebug()<<"--------------------------";
          while(_qry.next())
          {
               qDebug()<<"| "<<_qry.value(0).toString()<<" | "<<_qry.value(1).toString()<<" | "<<_qry.value(2).toString()<<" | ";
          }
          qDebug()<<"--------------------------";
       }
      else
      {
          qDebug() << "recieve query not valid";
      }
//    qDebug() << get_recievedUsername();
//    qDebug() << get_recievedPassword();

}



/**
 * @brief SQL::isEmpty
 * @param tableName
 * @return
 */
bool SQL::isEmpty()
{

    bool valid = false;
    QString query = "SELECT count(*) FROM account;";
    if(_qry.exec(query))
    {
        qDebug()<<"is empty next : "<<_qry.next();
        int count = _qry.value(0).toInt();
        valid = (count==0);
        qDebug()<<QString("is Database empty? %1" ).arg(count == 0);

    }
    else
    {
        qDebug()<<"query for is " << query << " empty didn't execute: " <<        _qry.lastError().text();
    }

    return valid ;
}
int  SQL::get_number_of_Resurants()
{
    QString query = "SELECT count(*) FROM Restaurant;";
    if(_qry.exec(query))
    {
        return _qry.value(0).toInt();
    }
}

int SQL::CustomerList_to_SQL(CustomerList &customerList) {
    int count = 0;
    Account* a;

    while(!customerList.isEmpty())
    {
        a = customerList.front();
        addAccount(a);
        customerList.pop_front();
        ++count;
    }

    return count;
}
void SQL::RestaurantList_to_SQL(RestaurantList& restaurantList)
{
    Restaurant* r;

    while(!restaurantList.isEmpty())
    {
        r = restaurantList.front();
        addRestaurant(r->getRestaurantID(),r->getRestaurantName(),r->getDistance());
        restaurantList.popFront();
    }

}

void SQL::FoodItem_to_SQL(FoodItem& foodItem)
{

        addItem(foodItem.getAccountID(),foodItem.getName(),foodItem.getPrice());

}

void SQL::Travel_to_SQL(Travel& travel)
{

    addTravel(travel);

}

int SQL::SQL_to_RestaurantList(RestaurantList& restaurantList) {

    /** Adds restaurants to the list */
    if(!isEmpty()) {
        QString query = "SELECT * FROM \"Restaurant\";";

        if(_qry.exec(query)) {
            while(_qry.next()) {
                restaurantList.addRestaurant(_qry.value(0).toInt(), _qry.value(1).toString(), _qry.value(2).toDouble());
            }
        }
    }
    else {
        qDebug() << "Restaurant table is empty!";
    }

    /** Adds menu items corresponding to each newly added restaurants */
    if(!isEmpty()) {
        QString query = "SELECT * FROM \"Menu\";";

        if(_qry.exec((query))) {
            while(_qry.next()) {
                // Finds what restaurant the food item is from
                Restaurant *currentRestaurant = restaurantList.findRestaurantByID(_qry.value(0).toInt());

                if(currentRestaurant != NULL) {
                    currentRestaurant->addMenuItem(currentRestaurant->getRestaurantName(), _qry.value(1).toString(), _qry.value(2).toDouble());
                }
                else {
                    qDebug() << "Error! " << _qry.value(1).toString() << " does not exists.";
                }

            }
        }
    }
}

int SQL::SQL_to_CustomerList(CustomerList &customer_list) {
    int index = 0;

    if(!isEmpty())
    {
        QString query = "SELECT * FROM account;";
        if(_qry.exec(query))
        {
            // receives info from SQL adds to vector
            while(_qry.next())
          {
                index++;
                customer_list.addCustomer(_qry.value(1).toString(),_qry.value(2).toString());
            }
        }//second if
    }//first if
    else
    {
        qDebug() << "Customer data base is empty";
    }

    // Returns the number of customer accounts.
    return index;
}

bool SQL::openDataBase()
{
    _DB.open();
    _qry = QSqlQuery(_DB);

      if(_DB.isOpen())
      {
          return true;
      }
      return false;
}
bool SQL::closeDataBase()
{
    _DB.close();
    if(!(_DB.isOpen()))
    {
        return true;
    }
    return false;

}

/*!
 * \brief SQL_Account::addPurchase
 * \param ID
 * \param restaurant_ID
 * \param item
 * \param quantity
 * \return
 */
bool SQL::addPurchase(unsigned short ID, QString restaurant_ID, QString item, unsigned short quantity)
{
    QString query = "insert into purchase values(\""+QString::number(ID)+"\",\""+restaurant_ID+"\",\""+item+"\",\""+QString::number(quantity)+"\");";
    return _qry.exec(query);
}

bool SQL::receivePurchases(std::list<FoodItem> purchaseList)
{
    QString query = "SELECT * FROM purchase;";
    if(_qry.exec(query))
    {
        while(_qry.next())
        {
            purchaseList.push_back(*(new FoodItem
                                        (_qry.value(0).toInt(),
                                         _qry.value(1).toString(),
                                         _qry.value(2).toDouble(),
                                         _qry.value(3).toInt())));
        }
        return true;
    }
    return false;
}
void SQL::get_FoodItemsWhereID(const int food_ID, std::list<FoodItem>& FoodItemList)
 {
 QSqlQuery query;
 query.prepare("SELECT * from Restaurant,Menu where Restaurant.ID=:ID and Menu.ID=:ID;");
 query.bindValue(":ID",food_ID);
 if(query.exec())
 {
     while(query.next())
     {
    FoodItemList.push_back(*(new FoodItem(query.value(0).toInt(),query.value(4).toString(),query.value(5).toDouble(),0)));
     }
 }

 }
 void SQL::get_ResurantsWhereID(const int res_ID,std::list<Restaurant>& RestaurantList)
 {
     QSqlQuery query;
     query.prepare("SELECT * from Restaurant where Restaurant.ID=:ID;");
     query.bindValue(":ID",res_ID);
     if(query.exec())
     {
         while(query.next())
         {
//                     qDebug()<<query.value(0).toInt();
//                     qDebug()<<query.value(1).toString();
//                     qDebug()<<query.value(2).toDouble();
//                     qDebug()<<"----------------------";
        RestaurantList.push_back(*(new Restaurant(query.value(0).toInt(),query.value(1).toString(),query.value(2).toDouble())));
         }
     }
 }

 void SQL::get_FoodItems(std::list<FoodItem>& FoodItemList)
 {
     QString query = "SELECT * from Menu";
     if(_qry.exec(query))
     {
         while(_qry.next())
         {

         FoodItemList.push_back(*(new FoodItem(_qry.value(0).toInt(),_qry.value(1).toString(),_qry.value(2).toDouble(),0)));
         }
     }
 }
void SQL::get_Resurants(std::vector<QString>& RestaurantList)
{
    QString query = "SELECT * FROM Restaurant;";
    if(_qry.exec(query))
    {
        while(_qry.next())
        {
            RestaurantList.push_back(_qry.value(1).toString());
        }
    }
}

void SQL::get_Resurants(std::list<Restaurant>& RestaurantList)
{
    QString query = "SELECT * FROM Restaurant;";
    if(_qry.exec(query))
    {
        while(_qry.next())
        {
            RestaurantList.push_back(*(new Restaurant
                                        (_qry.value(0).toInt(),
                                         _qry.value(1).toString(),
                                         _qry.value(2).toDouble())));
        }
    }
}

void SQL::get_Resurants(RestaurantList& restaurantList)
{
    QString query = "SELECT * FROM Restaurant;";
    if(_qry.exec(query))
    {
        while(_qry.next())
        {
            restaurantList.pushBack(new Restaurant(_qry.value(0).toInt(),_qry.value(1).toString(),_qry.value(2).toDouble()));
        }
    }
}

void SQL::printFoods(std::list<FoodItem> FoodItemList)
{
    for(std::list<FoodItem>::iterator it = FoodItemList.begin();it != FoodItemList.end();it++)
    {
        qDebug()<<"--------";
        qDebug()<<"name: "<<it->getName();
        qDebug()<<"price: "<<it->getPrice();
    }
}
void SQL::printRestaurants(std::list<Restaurant> RestaurantList)
{
    for(std::list<Restaurant>::iterator it = RestaurantList.begin();it != RestaurantList.end();it++)
    {
        qDebug()<<"--------";
        qDebug()<<"ID: " << (it)->getRestaurantID();
        qDebug()<<"name: " << (it)->getRestaurantName();
        qDebug() <<"distance: " << (it)->getDistance();
    }
}

bool SQL::changePrice(int ID,QString item,double price)
{
    QSqlQuery query;
    query.prepare("UPDATE Menu set price = :price where ID = :ID and item = :item;");
    query.bindValue(":ID",ID);
    query.bindValue(":item",item);
    query.bindValue(":price",price);
    return query.exec();
}
bool SQL::addItem(int ID,QString item,double price)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Menu (ID, item, price) "
                  "VALUES (:ID, :item, :price)");
    query.bindValue(":ID", ID);
    query.bindValue(":item", item);
    query.bindValue(":price", price);
    return query.exec();
}
bool SQL::deleteItem(int ID)
{
    QSqlQuery query;
    query.prepare("DELETE from Menu where ID=:ID;");
    query.bindValue(":ID",ID);
    return query.exec();
}

bool SQL::deleteItem(int ID,QString item)
{
    QSqlQuery query;
    query.prepare("DELETE from Menu where ID=:ID and item=:item;");
    query.bindValue(":ID",ID);
    query.bindValue(":item",item);
    return query.exec();
}

bool SQL::deleteItem(int ID,double price)
{
    QSqlQuery query;
    query.prepare("DELETE from Menu where ID=:ID and price=:price;");
    query.bindValue(":ID",ID);
    query.bindValue(":price",price);
    return query.exec();
}
bool SQL::deleteItem(double price)
{
    QSqlQuery query;
    query.prepare("DELETE from Menu where price=:price;");
    query.bindValue(":price",price);
    return query.exec();
}
bool SQL::deleteItem(int ID,QString item,double price)
{
    QSqlQuery query;
    query.prepare("DELETE from Menu where ID=:ID and item=:item and price=:price;");
    query.bindValue(":ID",ID);
    query.bindValue(":item",item);
    query.bindValue(":price",price);
    return query.exec();
}
bool SQL::deleteItem(QString item)
{
    QSqlQuery query;
    query.prepare("DELETE from Menu where item=:item;");
    query.bindValue(":item",item);
    return query.exec();
}

bool SQL::deleteRestaurant(int ID)
{
    QSqlQuery query;
    query.prepare("DELETE from Restaurant where ID=:ID;");
    query.bindValue(":ID",ID);
    return query.exec();
}

bool SQL::deleteRestaurant(int ID,QString name)
{
    QSqlQuery query;
    query.prepare("DELETE from Restaurant where ID=:ID and name=:name;");
    query.bindValue(":ID",ID);
    query.bindValue(":name",name);
    return query.exec();
}

bool SQL::deleteRestaurant(int ID,double distance)
{
    QSqlQuery query;
    query.prepare("DELETE from Restaurant where ID=:ID and distance=:distance;");
    query.bindValue(":ID",ID);
    query.bindValue(":distance",distance);
    return query.exec();
}
bool SQL::deleteRestaurant(double distance)
{
    QSqlQuery query;
    query.prepare("DELETE from Restaurant where distance=:distance;");
    query.bindValue(":distance",distance);
    return query.exec();
}
bool SQL::deleteRestaurant(QString name)
{
    QSqlQuery query;
    query.prepare("DELETE from Restaurant where name=:name;");
    query.bindValue(":name",name);
    return query.exec();
}
bool SQL::deleteRestaurant(int ID,QString name,double distance)
{
    QSqlQuery query;
    query.prepare("DELETE from Restaurant where ID=:ID and name=:name and distance=:distance;");
    query.bindValue(":ID",ID);
    query.bindValue(":name",name);
    query.bindValue(":distance",distance);
    return query.exec();
}
/*RESTAURANT*/
bool SQL::changeDistance(int ID,QString name,double distance)
{
    QSqlQuery query;
    query.prepare("UPDATE Restaurant set distance = :distance where ID = :ID and name = :name;");
    query.bindValue(":ID",ID);
    query.bindValue(":distance",distance);
    query.bindValue(":name",name);
    return query.exec();
}

bool SQL::addRestaurant(int ID, QString name, double distance)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Restaurant (iD, name, distance) "
                  "VALUES (:ID, :name, :distance)");
    query.bindValue(":ID", ID);
    query.bindValue(":name", name);
    query.bindValue(":distance", distance);
    return query.exec();
}

bool SQL::addTravel(Travel& travel)
{
//    QSqlQuery query;
//    query.prepare("INSERT INTO travel (ID, username, destination,taken) "
//                  "VALUES (:ID, :username, :destination,:taken)");
//    query.bindValue(":ID", travel.getId());
//    query.bindValue(":username", travel.getUsername());
//    query.bindValue(":destination", travel.getdestination());
//    query.bindValue(":taken",travel.getTaken() );
//    return query.exec();
    return false;
}

QString SQL::get_distances()
{
    QString query = "SELECT * FROM vertex;";
    if(_qry.exec(query))
    {
        _qry.next();
            return _qry.value(0).toString();
    }
}

void SQL::setDistances(const QString& d)
{
    QSqlQuery query;
    query.prepare("UPDATE vertex set distances =:d;");
    query.bindValue(":d",d);
    query.exec();
}
