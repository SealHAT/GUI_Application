#include "maindialog.h"
#include "ui_maindialog.h"
#include "sql_account.h"
#include "shoppingcart.h"
#include <QDesktopWidget>
#include <QMessageBox>

#include <QDebug>

/**
 * Initial GUI setup.
 **/
maindialog::maindialog(QWidget *parent) : QDialog(parent), ui(new Ui::maindialog)
{
    ui->setupUi(this);

    // On the Login stack, set the welcome page.
    ui->loginStacked->setCurrentIndex(INITIAL_PAGE);

    // Set size for smaller welcome screen.
    this->setFixedSize(421, 421);
}

/**
 * Delete GUI on exit.
 **/
maindialog::~maindialog()
{
    delete ui;
}

/**
 * @brief maindialog::on_signOutButton_clicked
 */
void maindialog::on_signOutButton_clicked()
{
    // Sets the dialog back to a login screen
    this->setFixedSize(421, 421);

    ui->mainStacked->setCurrentIndex(0);
    ui->loginStacked->setCurrentIndex(INITIAL_PAGE);

    this->centerDialog();
}

/**
 * Center the contents of the page.
 **/
void maindialog::centerDialog() {
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}

/**
 *
 **/
void maindialog::on_restaurantsButton_clicked()
{
    ui->listOfRestaurants->clear();
    ui->listOfFoodItems->clear();

    for(list<Restaurant*>::const_iterator it = _restaurantList.restaurants.begin();
        it != _restaurantList.restaurants.end(); it++) {

        QTreeWidgetItem *type = new QTreeWidgetItem(ui->listOfRestaurants);
        ui->listOfRestaurants->addTopLevelItem(type);
        type->setText(0, ((*it)->getRestaurantName()));
        ui->listOfRestaurants->addTopLevelItem(type);

    }

    /** Automatically selects the first item on the list to view */
    ui->listOfRestaurants->setCurrentItem(ui->listOfRestaurants->topLevelItem(0));
    on_listOfRestaurants_itemSelectionChanged();

    ui->customerPages->setCurrentIndex(VIEW_RESTAURANTS);

}

/**
 *
 **/
void maindialog::on_customerHomeButton_clicked()
{
    ui->customerPages->setCurrentIndex(CONFIGURE_DEV_HOME_PAGE);
}

/**
 *
 **/
void maindialog::on_adminSignOutButton_clicked()
{
    on_signOutButton_clicked();
}

/**
 *
 **/
void maindialog::on_purchaseHistoryButton_clicked()
{
    QString foodName;
    QString price;
    QString qty;
    QString total;
    QString currentRestaurant;


    if(!(currentAccount->getPurchaseList().empty())) {

        list<FoodItem*> purchaseList = currentAccount->getPurchaseList();
        // Sets the iterator to begin at the start of the list
        list<FoodItem*>::iterator it = purchaseList.begin();
        QString previousRestaurant = (*it)->getFromWhere();

        while(it != purchaseList.end())
        {
            currentRestaurant = (*it)->getFromWhere();

            QTreeWidgetItem *parent = new QTreeWidgetItem(ui->purchaseHistoryList);
            ui->purchaseHistoryList->addTopLevelItem(parent);

            if(previousRestaurant == currentRestaurant ) {
                foodName = (*it)->getName();
                price = QString::number((*it)->getPrice());
                qty   = QString::number((*it)->getQuantity());
                total = QString::number((*it)->getPrice() * (*it)->getQuantity());

                QTreeWidgetItem *itm = new QTreeWidgetItem();

                itm->setText(0, foodName);
                itm->setText(1, "$" + price + ".00");
                itm->setTextAlignment(1, Qt::AlignCenter);
                itm->setText(2, qty);
                itm->setTextAlignment(2, Qt::AlignCenter);
                itm->setText(3, "$" + total + ".00");
                itm->setTextAlignment(3, Qt::AlignCenter);


                parent->addChild(itm);
            }
            else {
                parent->setText(0, (*it)->getFromWhere());
                ui->purchaseHistoryList->addTopLevelItem(parent);
                previousRestaurant = currentRestaurant;

            }
            // Iterator increments to the next node
            it++;
        }
    }
    else {
        ui->purchaseHistoryList->hide();
    }


    ui->customerPages->setCurrentIndex(PURCHASE_HISTORY);

}

/**
 *
 **/
void maindialog::on_listOfRestaurants_itemSelectionChanged()
{
    Restaurant *currentRestaurant = NULL;
    QTreeWidgetItem* selectedRestaurant = ui->listOfRestaurants->currentItem();


    if(selectedRestaurant != NULL)
    {
        QString restaurantName = selectedRestaurant->data(0, 0).toString();

        currentRestaurant = _restaurantList.findRestaurantByName(restaurantName);
        ui->distanceFromSaddleback->setText(QString::number(currentRestaurant->getDistance()) + " miles");

        ui->listOfFoodItems->clear();

        list<FoodItem*> currentMenu = currentRestaurant->getMenu();
        for(list<FoodItem*>::const_iterator it = currentMenu.begin();
          it != currentMenu.end(); it++)
        {

          QTreeWidgetItem *type = new QTreeWidgetItem(ui->listOfFoodItems);
          ui->listOfFoodItems->addTopLevelItem(type);
          type->setText(0, ((*it)->getName()));
          type->setText(1, "$" + QString::number(((*it)->getPrice())));
          type->setTextAlignment(1, Qt::AlignCenter);
          ui->listOfFoodItems->addTopLevelItem(type);
        }
    }
    else {
        qDebug() << "Nothing was selected.\n";
    }
}

/**
 *
 **/
void maindialog::on_planATripButton_clicked()
{
    ui->customerPages->setCurrentIndex(PLAN_A_TRIP);
}

/**
 *
 **/
void maindialog::on_shortestTripButton_clicked()
{
    ui->customerPages->setCurrentIndex(SHORT_TRIP);
}

/**
 *
 **/
void maindialog::on_travelToAllButton_clicked()
{
    // Set the go back button the 'arrows.png'
    QPixmap pixmap(":/arrows.png");
    QIcon ButtonIcon(pixmap);
    ui->goBackFromTripToAllButton->setIcon(ButtonIcon);
    ui->goBackFromTripToAllButton->setIconSize(ui->goBackFromTripToAllButton->rect().size());

    float totalTraveled = 0.0;

    //Vertex<string> test;
    //test.createGraph(_restaurantList.restaurants, false);

    Vertex<string> vertexAr[11];

    float graph[11][11] = {{0.0,   8,    4.29, 12.41, 7.56, 2.67, 5.94, 8.44, 12.75, 9.19, 14.54, },
                           {8,     0.0,  13.2, 15.4,  11.5, 13.3, 15.2, 5.8,  6.9,   8.56, 3.5, },
                           {4.29,  13.2, 0.0,  15.1,  14.8, 0.1,  4.2,  10.3, 9.3,   5.2,  11.0,  },
                           {12.41, 15.4, 15.1, 0.0,   4.3,  16.1, 14.3, 18.4, 18.3,  17.2, 17.2,  },
                           {7.56,  11.5, 14.8, 4.3,   0.0,  8.1,  9.4,  14.4, 14.3,  13.2, 13.2, },
                           {2.67,  13.3, 0.1,  16.1,  8.1,  0.0,  4.5,  8.5,  8.4,   5.1,  12.1,   },
                           {5.94,  15.2, 4.2,  14.3,  9.4,  4.5,  0.0,  8.56, 11.1,  5.1,  14.2,   },
                           {8.44,  5.8,  10.3, 18.4,  14.4, 8.5,  8.56, 0.0,  0.7,   5.8,  4.0, },
                           {12.75, 6.9,  9.3,  18.7,  14.3, 8.4,  11.1, 0.7,  0.0,   5.7,  4.7,  },
                           {9.19,  8.56, 5.2,  17.2,  13.2, 5.1,  5.1,  5.8,  5.7,   0.0,  9.5, },
                           {14.54, 3.5,  11.0, 17.2,  13.2, 12.1, 14.2, 4.0,  4.7,   9.5,  0.0,},};
    QString nameAr[] = {"Saddleback",
                       "McDonalds", "Chipotle", "Dominos Pizza", "KFC", "Subway",
                       "In-N-Out", "Wendys", "Jack in the Box", "El Pollo Loco", "Papa Johns Pizza"};

    for(int k = 0; k < 11; k++)
    {
        vertexAr[k].setVertexValue(k);
        vertexAr[k].setData(nameAr[k].toStdString());
    }



    vertexAr[0].setVisited(true);

    int temp = 0;


    ui->shortestTripToAllList->clear();

    for(int i = 0; i < 10; i++)
    {
        int smallest = 1;

        for(int j = 0; j < 11; j++)
        {
            if(temp == smallest)
                smallest++;

            if(graph[temp][j] < graph[temp][smallest] && !vertexAr[j].getVisited())
            {
                smallest = j;
            }

        }


        QTreeWidgetItem *type = new QTreeWidgetItem(ui->shortestTripToAllList);
        ui->shortestTripToAllList->addTopLevelItem(type);
        type->setText(0, (nameAr[smallest]));
        type->setText(1, QString::number(graph[temp][smallest]) + " miles");
        type->setTextAlignment(1, Qt::AlignCenter);

        totalTraveled += graph[temp][smallest];
        qDebug() << "totalTraveled: " << totalTraveled;
        ui->shortestTripToAllList->addTopLevelItem(type);

        vertexAr[smallest].setVisited(true);
        temp = smallest;
    }

    ui->distanceToAllTotal->setText(QString::number(totalTraveled) + " miles");

    ui->customerPages->setCurrentIndex(TRIP_TO_ALL);
}

/**
 *
 **/
void maindialog::on_matienanceButton_clicked()
{
    ui->adminPages->setCurrentIndex(MATIENANCE);

    ui->listOfChangeRestaurants->clear();

    for(list<Restaurant*>::const_iterator it = _restaurantList.restaurants.begin();
        it != _restaurantList.restaurants.end(); it++) {

        QTreeWidgetItem *type = new QTreeWidgetItem(ui->listOfChangeRestaurants);
        ui->listOfChangeRestaurants->addTopLevelItem(type);
        type->setText(0, ((*it)->getRestaurantName()));
        type->setText(1, (QString::number((*it)->getDistance()) + " miles"));
        type->setTextAlignment(1, Qt::AlignCenter);

        ui->listOfChangeRestaurants->addTopLevelItem(type);

        }
}

/**
 *
 **/
void maindialog::on_editRestaurantButton_clicked()
{
    // Set the go back button the 'arrows.png'
    QPixmap pixmap(":/arrows.png");
    QIcon ButtonIcon(pixmap);
    ui->goBackFromEditRestaurant->setIcon(ButtonIcon);
    ui->goBackFromEditRestaurant->setIconSize(ui->goBackFromEditRestaurant->rect().size());

    ui->listOfSelectedRestaurantMenu->clear();


        QTreeWidgetItem *current = ui->listOfChangeRestaurants->currentItem();
        Restaurant *selectedRestaurant = NULL;

        if(current != NULL) {

           QString restaurantName = current->data(0, 0).toString();
           selectedRestaurant = _restaurantList.findRestaurantByName(restaurantName);

           ui->restaurantMenuHeading->setText(restaurantName + " Menu");

           list<FoodItem*> selectedMenu = selectedRestaurant->getMenu();

           for(list<FoodItem*>::const_iterator it = selectedMenu.begin();
               it != selectedMenu.end(); it++) {

               QTreeWidgetItem *type = new QTreeWidgetItem(ui->listOfSelectedRestaurantMenu);
               ui->listOfSelectedRestaurantMenu->addTopLevelItem(type);
               type->setText(0, ((*it)->getName()));
               type->setText(1, (QString::number((*it)->getPrice())));
               type->setTextAlignment(1, Qt::AlignCenter);
               ui->listOfSelectedRestaurantMenu->addTopLevelItem(type);
           }

           ui->adminPages->setCurrentIndex(2);

        }
        else {
            QMessageBox::warning(this, "Warning!", "Uh-oh, please select a restaurant to edit.");

        }
}

/**
 *
 **/
void maindialog::on_goBackFromEditRestaurant_clicked()
{
    ui->adminPages->setCurrentIndex(MATIENANCE);
}

/**
 *
 **/
void maindialog::on_addRestaurantButton_clicked()
{
    // Set the go back button the 'arrows.png'
    QPixmap pixmap(":/arrows.png");
    QIcon ButtonIcon(pixmap);
    ui->goBackFromAddRestaurantButton->setIcon(ButtonIcon);
    ui->goBackFromAddRestaurantButton->setIconSize(ui->goBackFromAddRestaurantButton->rect().size());

    ui->listOfDistancesFromNewRestaurant->clear();

    for(list<Restaurant*>::const_iterator it = _restaurantList.restaurants.begin();
        it != _restaurantList.restaurants.end(); it++) {

        QTreeWidgetItem *type = new QTreeWidgetItem(ui->listOfDistancesFromNewRestaurant);
        ui->listOfDistancesFromNewRestaurant->addTopLevelItem(type);
        type->setText(0, ((*it)->getRestaurantName()));
        ui->listOfDistancesFromNewRestaurant->addTopLevelItem(type);

    }

    ui->newRestaurantErrorMessage->setVisible(false);
    ui->newDistanceErrorMessage->setVisible(false);
    ui->newAllDistanceErrorMessage->setVisible(false);
    
    ui->newRestaurantName->clear();
    ui->newRestaurantDistance->clear();

    ui->adminPages->setCurrentIndex(3);
}

/**
 *
 **/
void maindialog::on_goBackFromAddRestaurantButton_clicked()
{
    ui->adminPages->setCurrentIndex(MATIENANCE);
}

/**
 *
 **/
void maindialog::on_goBackFromAddNewMenuButton_clicked()
{
    ui->adminPages->setCurrentIndex(3);

}

/**
 *
 **/
void maindialog::on_addNewRestaurantNextButton_clicked()
{
    ui->newRestaurantErrorMessage->setVisible(false);
    ui->newDistanceErrorMessage->setVisible(false);
    ui->newAllDistanceErrorMessage->setVisible(false);

    bool valid = true;

       //check to make sure all data fields are filled
       if(ui->newRestaurantName->text() == "")
       {
           //display error message for empty restaurant name
           valid = false;
           ui->newRestaurantErrorMessage->setText("Restaurant field was left blank.");
           ui->newRestaurantErrorMessage->setVisible(true);
       }
       else {
           //check to make sure restaurant is not already a part of the list
           for(list<Restaurant*>::const_iterator it = _restaurantList.restaurants.begin();
               it != _restaurantList.restaurants.end() && valid; it++)
           {
               if((*it)->getRestaurantName() == ui->newRestaurantName->text())
               {
                   valid = false;
                   ui->newRestaurantErrorMessage->setText("Restaurant name is taken.");
                   ui->newRestaurantErrorMessage->setVisible(true);
               }
           }
       }

       if(ui->newRestaurantDistance->text() == "")
       {
           valid = false;
           ui->newDistanceErrorMessage->setText("Distance to Saddleback field was left blank.");
           ui->newDistanceErrorMessage->setVisible(true);
       }
       //distances only accept positive values       
       else if(ui->newRestaurantDistance->text().toDouble() < 0) {
           valid = false;
           ui->newDistanceErrorMessage->setText("Distance needs to be positive.");
           ui->newDistanceErrorMessage->setVisible(true);
       }


       //loop to make sure all new distances are added into the table and are valid
       //QTreeWidgetItem *type = new QTreeWidgetItem(ui->distanceFromRestaurantsList);
       QTreeWidgetItemIterator it(ui->listOfDistancesFromNewRestaurant);

       while(*it)
       {
           if((*it)->text(1) == "" || (*it)->text(1).toDouble() < 0)
           {
               valid = false;
               (*it)->setBackgroundColor(1, *new QColor(Qt::GlobalColor(Qt::yellow)));

               //display error message - value greater than or equal to zero
               ui->newAllDistanceErrorMessage->setVisible(true);
               ui->newAllDistanceErrorMessage->setText("Highlighted rows' distances were left blank.");
           }

           it++;
       }

       //if all data is correctly added, go to menu page
       if(valid)
       {
           Restaurant *newRestaurant = new Restaurant;

           //set restaurant name
           //newRestaurant->setRestaurantName(ui->newRestaurantName->text());

           //set distance from saddleback
           newRestaurant->setDistance(ui->newRestaurantDistance->text().toDouble());

           //create and set a list of distances
           QTreeWidgetItemIterator it2(ui->listOfDistancesFromNewRestaurant);

           while(*it2)
           {
              newRestaurant->addDistanceToRestaurant(newRestaurant->getRestaurantName(),(*it2)->text(1).toDouble());
              it2++;
           }

           //switch to menu items page
           ui->adminPages->setCurrentIndex(4);
           ui->newRestaurantErrorMessage_2->hide();
           ui->newRestaurantErrorMessage_3->hide();

           // Add all data from this page to list if valid
           _restaurantList.pushBack(newRestaurant);

       }
}

/**
 *
 **/
void maindialog::on_continueToTakeATripButton_clicked()
{
    ui->customerPages->setCurrentIndex(TAKE_A_TRIP_INSTRUCTIONS);
}

/**
 *
 **/
void maindialog::on_takeATripButton_clicked()
{
    // Set the shopping cart the 'shop.png'
    QPixmap pixmap(":/shop.png");
    QIcon ButtonIcon(pixmap);
    ui->shoppingCartButton->setIcon(ButtonIcon);
    ui->shoppingCartButton->setIconSize(ui->shoppingCartButton->rect().size());
    ui->shoppingCartDummy->setIcon(ButtonIcon);
    ui->shoppingCartDummy->setIconSize(ui->shoppingCartDummy->rect().size());

    ui->customerPages->setCurrentIndex(TAKE_A_TRIP);
}

/**
 *
 **/
void maindialog::on_beginTripButton_clicked()
{

    ui->customerPages->setCurrentIndex(TAKE_A_TRIP_IN_PROCESS);

    QEventLoop pause;

    /** Iterates through each restaurant */ 
      // testing information at the momment
    for(int i = 1; i <= 5; i++) {

        if(i == 5) {
            ui->goToNextRestaurantButton->setText("FINISH");
        }
        
        ui->currentRestaurantNumber->setText("Restaurant #" + QString::number(i));

        /** Waits until user clicks 'next' button */
        QObject::connect(ui->goToNextRestaurantButton, SIGNAL(clicked()), &pause, SLOT(quit()));
        pause.exec();
        
    }

}

/**
 *
 **/
void maindialog::on_shoppingCartButton_clicked()
{
    ShoppingCart *currentShoppingCart = new ShoppingCart;
    
    list<FoodItem*> demo;

    currentShoppingCart->SetList(demo);
    currentShoppingCart->show();
    currentShoppingCart->setVisible(true);

}

/**
 *
 **/
void maindialog::on_goToNextRestaurantButton_clicked()
{
    if(ui->goToNextRestaurantButton->text() == "FINISH") {
        ui->customerPages->setCurrentIndex(TAKE_A_TRIP_END);
    }

}

/**
 *
 **/
void maindialog::on_listOfDistancesFromNewRestaurant_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    bool VALID_COL = 1;
    if(column == VALID_COL) {
        item->setFlags (item->flags () | Qt::ItemIsEditable);
    }
}

/**
 *
 **/
void maindialog::on_confirmTripToAllButton_clicked()
{
    Travel newTrip;
}

/**
 *
 **/
void maindialog::on_goBackFromCustomTripButton_clicked()
{
    ui->customerPages->setCurrentIndex(PLAN_A_TRIP);
}

/**
 *
 **/
void maindialog::on_customTripButton_clicked()
{
    // Set the go back button the 'arrows.png'
    QPixmap pixmap(":/arrows.png");
    QIcon ButtonIcon(pixmap);
    ui->goBackFromCustomTripButton->setIcon(ButtonIcon);
    ui->goBackFromCustomTripButton->setIconSize(ui->goBackFromCustomTripButton->rect().size());

    ui->customerPages->setCurrentIndex(CUSTOM_TRIP);
}

/**
 *
 **/
void maindialog::on_goBackFromTripToAllButton_clicked()
{
    ui->customerPages->setCurrentIndex(TAKE_A_TRIP);
}

/**
 *
 **/
void maindialog::on_addNewMenuItemButton_2_clicked()
{
    //displays current menu items and prices
    list<Restaurant*>::const_iterator restaurantIt = _restaurantList.restaurants.end();
    list<FoodItem*>::const_iterator foodIt = (*restaurantIt)->getMenu().begin();

    --restaurantIt;

    for(list<FoodItem*>::const_iterator it = (*restaurantIt)->getMenu().begin();
        it != (*restaurantIt)->getMenu().end(); it++) {

        QTreeWidgetItem *type = new QTreeWidgetItem(ui->listOfNewRestaurantMenuItems);
        ui->listOfNewRestaurantMenuItems->addTopLevelItem(type);
        type->setText(0, ((*it)->getName()));
        type->setText(1, (QString::number((*it)->getPrice())));
        type->setTextAlignment(1, Qt::AlignCenter);
        ui->listOfNewRestaurantMenuItems->addTopLevelItem(type);
    }

    //hide error messages
    ui->newRestaurantErrorMessage_2->hide();
    ui->newRestaurantErrorMessage_3->hide();

    bool valid = true;

   //check to make sure all data fields are filled
   if(ui->newMenuItemName->text() == "")
   {
       //display error message for empty menu item name
       valid = false;
       ui->newRestaurantErrorMessage_2->setText("Item Name field was left blank.");
       ui->newRestaurantErrorMessage_2->setVisible(true);
   }
   else
   {
       //checks to make sure menu item is not duplicated
       while(foodIt != (*restaurantIt)->getMenu().end())
       {
           if((*foodIt)->getName() == ui->newMenuItemName->text())
           {
               valid = false;
           }

           foodIt++;
       }
   }

   //checks to make sure field is not empty
   if(ui->newMenuItemPrice->text() == "")
   {
       valid = false;
       ui->newRestaurantErrorMessage_3->setText("Menu Price field was left blank.");
       ui->newRestaurantErrorMessage_3->setVisible(true);
   }
   //prices only accept positive values
   else if(ui->newMenuItemPrice->text().toDouble() < 0) {
       valid = false;
       ui->newRestaurantErrorMessage_3->setText("Price needs to be positive.");
       ui->newRestaurantErrorMessage_3->setVisible(true);
   }

   if(valid)
   {
       (*restaurantIt)->addMenuItem((*restaurantIt)->getRestaurantName(), ui->newMenuItemName->text(),
                                    ui->newMenuItemPrice->text().toDouble());
   }
}

/**
 *
 **/
void maindialog::on_doneButtonOnAddMenuItem_clicked()
{
    //switch to admin home page
    ui->adminPages->setCurrentIndex(0);
}
