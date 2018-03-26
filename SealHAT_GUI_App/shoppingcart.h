#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QWidget>
#include <list>
#include <iterator>
#include "fooditem.h"
namespace Ui {
class ShoppingCart;
}

class ShoppingCart : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingCart(QWidget *parent = 0);
    ~ShoppingCart();
    void SetList(list<FoodItem*> foodieList);


private:
    Ui::ShoppingCart *ui;
    list<FoodItem*> foodieItemsList;

};

#endif // SHOPPINGCART_H
