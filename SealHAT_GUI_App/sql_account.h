#ifndef SQL_ACCOUNT
#define SQL_ACCOUNT

#include "customerlist.h"
#include "restaurant.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class SQL_Account
{
public:
    SQL_Account();
    ~SQL_Account();

     /***ADD***/
    bool addAccount(Account *a);

     /***DELETE***/
    bool deleteAccount(QString tableName,const QString &arg1);

     /***RECIEVE***/
    bool receiveAccount(QString tableName,const QString &arg1);

     /***DISPLAY***/
    void displayAccount();
    void displayAll(QString tablename);
    bool isEmpty(QString tableName);

     /***UPDATE***/
    int vector_to_SQL(CustomerList& customerList);
    int SQL_to_Vector(CustomerList& customerList);
    void closeDatabase();



    /*ACCESSORS*/
    QString get_recievedUsername()const;
    QString get_recievedPassword()const;

private:
    QSqlDatabase _DB;
    QSqlQuery _qry;
    QString _recievedUsername;
    QString _recievedPassword;

};

#endif // SQL_ACCOUNT

