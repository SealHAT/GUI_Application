#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "account.h"
#include "restaurant.h"
#include "customerlist.h"
#include "sql.h"
#include "restaurantlist.h"
#include "vertex.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <list>


namespace Ui {
class maindialog;
}

class maindialog : public QDialog
{
    Q_OBJECT
    CustomerList _customerList;
    RestaurantList _restaurantList;
    SQL _sql;

    enum CUSTOMER_PAGES {
        CONFIGURE_DEV_HOME_PAGE = 0,
        VIEW_RESTAURANTS,
        TRAVEL_LOG,
        PLAN_A_TRIP,
        CUSTOM_TRIP,
        CUSTOM_TRIP_CONFIRM,
        SHORT_TRIP,
        SHORT_TRIP_CONFRIM,
        TRIP_TO_ALL,
        TAKE_A_TRIP,
        TAKE_A_TRIP_INSTRUCTIONS,
        TAKE_A_TRIP_IN_PROCESS,
        TAKE_A_TRIP_END,
        PURCHASE_HISTORY,
    };

    enum ADMIN_PAGES {
        RETRIEVE_DATA_HOME_PAGE,
        MATIENANCE,
        CUSTOMER_HISTORY,
    };

    enum LOGIN_PAGES {
        INITIAL_PAGE = 0,
        SIGN_UP_PAGE,
    };

public:
    explicit maindialog(QWidget *parent = 0);
    bool isBlank(QString text);
    void centerDialog();

    ~maindialog();

private slots:
    void on_signOutButton_clicked();

    void on_restaurantsButton_clicked();

    void on_customerHomeButton_clicked();

    void on_adminSignOutButton_clicked();

    void on_purchaseHistoryButton_clicked();

    void on_configureDevOptionButton_clicked();

    void on_retrieveDataButton_clicked();

    void on_goBackButton_clicked();

    void on_createAccountButton_clicked();

    void on_listOfRestaurants_itemSelectionChanged();

    void on_planATripButton_clicked();

    void on_shortestTripButton_clicked();

    void on_matienanceButton_clicked();

    void on_editRestaurantButton_clicked();

    void on_goBackFromEditRestaurant_clicked();

    void on_addRestaurantButton_clicked();

    void on_goBackFromAddRestaurantButton_clicked();

    void on_goBackFromAddNewMenuButton_clicked();

    void on_addNewRestaurantNextButton_clicked();

    void on_travelToAllButton_clicked();

    void on_continueToTakeATripButton_clicked();

    void on_takeATripButton_clicked();

    void on_beginTripButton_clicked();

    void on_shoppingCartButton_clicked();
    
    void on_goToNextRestaurantButton_clicked();

    void on_listOfDistancesFromNewRestaurant_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_confirmTripToAllButton_clicked();
    
    void on_goBackFromCustomTripButton_clicked();
    
    void on_customTripButton_clicked();
    
    void on_goBackFromTripToAllButton_clicked();

    void on_addNewMenuItemButton_2_clicked();

    void on_doneButtonOnAddMenuItem_clicked();

private:
    Ui::maindialog *ui;
    Account* currentAccount;
};

#endif // MAINDIALOG_H
