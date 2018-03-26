//#include "sql_account.h"

///**
// * @brief SQL::SQL
// */
//SQL_Account::SQL_Account()
//{
//    _DB = QSqlDatabase::addDatabase("QSQLITE", "first");

//    /** REMEMBER EACH COMPUTER HAS A DIFFERENT PATH **/

//    _DB.setDatabaseName("/Users/sarahsingletary/Documents/QT\ Workspace/quasar/fastfoodfantasy/sqlite/account.db");
//    _DB.open();
//    _qry = QSqlQuery(_DB);

//      if(_DB.isOpen())
//      {
//          qDebug()<<"Data Base is open";
//          _DB.exec("PRAGMA foreign_keys=ON;");
//      }
//}

///**
// * @brief SQL_Account::~SQL_Account
// */
//SQL_Account::~SQL_Account() {
//    _DB.close();

//    qDebug()<<"Account Database is closing";
//}

///**
// * @brief SQL_Account::get_recievedUsername
// * @return attribute: _recievedUsername
// */
//QString SQL_Account::get_recievedUsername()const
//{
//    return _recievedUsername;
//}

///**
// * @brief SQL_Account::get_recievedPassword
// * @return attribute: _recievedPassword
// */
//QString SQL_Account::get_recievedPassword()const
//{
//    return _recievedPassword;
//}

///**
// * @brief SQL_Account::addAccount
// * @param tableName
// * @param a
// * @return T/F if successfully added
// */
//bool SQL_Account::addAccount(Account *a)
//{

//    QString query = "insert into \"account\" values(null,\""
//            +a->getUsername()
//            +"\",\""
//            +a->getPassword()
//            +"\");";
//    bool valid = _qry.exec(query);


//    qDebug() << query;
//    qDebug() << "SQL class  adding query -> valid : " << valid;

//return valid;

//}

///**
// * @brief SQL_Account::deleteAccount
// * @param tableName
// * @param arg1
// * @return T/F if deleted successfully
// */
//bool SQL_Account::deleteAccount(QString tableName,const QString &arg1)
//{
//      QString query = "DELETE FROM \""+tableName+"\" WHERE Username = \""+arg1+"\";";
//    bool valid = _qry.exec(query);
//    qDebug() << "delete query valid : " << valid;
//    return valid;

//}

///**
// * @brief SQL::receiveAccount
// * @param tableName
// * @param arg1
// * @return T/F if recieved successfully
// */
//bool SQL_Account::receiveAccount(QString tableName,const QString &arg1)
//{
//    bool valid;
//     QString query = "SELECT * FROM \""+tableName+"\" WHERE Username =\"" + arg1 + "\";";

//      if(_qry.exec(query))
//      {
//          valid = true;
//          qDebug()<<"(receive account )is select" << _qry.isSelect();
//          while(_qry.next())
//          {
//               _recievedUsername = _qry.value(1).toString();
//               _recievedPassword = _qry.value(2).toString();
//          }
//       }
//      else
//      {
//          valid = false;
//          qDebug() << "recieve query not valid";
//      }
//      return valid;
//}

///**
// * @brief SQL::displayAccount
// */
//void SQL_Account::displayAccount()
//{

//    qDebug() << get_recievedUsername();
//    qDebug() << get_recievedPassword();

//}

//void SQL_Account::closeDatabase() {
//    _DB.close();
//    qDebug() << "Account database is closing!" << endl;
//}

///**
// * @brief SQL::isEmpty
// * @param tableName
// * @return
// */
//bool SQL_Account::isEmpty(QString tableName)
//{

//    bool valid = false;
//    QString query = "SELECT count(*) FROM account;";
//    if(_qry.exec(query))
//    {
//        qDebug()<<"is empty next : "<<_qry.next();
//        int count = _qry.value(0).toInt();
//        valid = (count==0);
//        qDebug()<<QString("is Database empty? %1" ).arg(count == 0);

//    }
//    else
//    {
//        qDebug()<<"query for is " << query << " empty didn't execute: " <<        _qry.lastError().text();
//    }

//    return valid ;
//}


//int SQL_Account::vector_to_SQL(CustomerList &customerList) {
//    int count = 0;
//    Account* a;

//    while(!customerList.isEmpty())
//    {
//        a = customerList.front();
//        addAccount(a);
////        update("account",a);
//        customerList.pop_front();
//        ++count;
//    }

//    return count;
//}


//int SQL_Account::SQL_to_Vector(CustomerList &customer_list) {
//    int index = 0;

//    if(!isEmpty("account"))
//    {
//        QString query = "SELECT * FROM \"account\";";
//        if(_qry.exec(query))
//        {
//            // receives info from SQL adds to vector
//            while(_qry.next())
//          {
//                index++;
//                customer_list.addCustomer(_qry.value(1).toString(),_qry.value(2).toString());
//            }
//        }//second if
//    }//first if
//    else
//    {
//        qDebug() << "Customer data base is empty";
//    }

//    // Returns the number of customer accounts.
//    return index;
//}


