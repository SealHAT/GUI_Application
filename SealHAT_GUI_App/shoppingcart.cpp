#include "shoppingcart.h"
#include "ui_shoppingcart.h"

ShoppingCart::ShoppingCart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoppingCart)
{
    ui->setupUi(this);

    const float TAX = .075;

    double subTotal = 0.0;
    float  grandTotal = 0.0;
    int    totalQuantity = 0;
    float  taxedTotal = 0.0;
    for(list<FoodItem*>::iterator it = foodieItemsList.begin(); it != foodieItemsList.end(); it++)
    {
        QTreeWidgetItem *type = new QTreeWidgetItem(ui->ShoppingListTree);
        ui->ShoppingListTree->addTopLevelItem(type);
        type->setText(0,((*it)->getFromWhere()));
        type->setText(1,((*it)->getName()));
        type->setText(2,QString::number((*it)->getQuantity()));

        totalQuantity += (*it)->getQuantity();

        type->setText(3,"$" + QString::number((*it)->getPrice()));//price

        subTotal += ((*it)->getQuantity() *(*it)->getPrice());

        type->setText(4,"$" + QString::number(subTotal));//totl/price

        taxedTotal = (subTotal)*TAX;
        grandTotal = taxedTotal + subTotal;

    }

    ui->subTotalBox->setText("$" + QString::number(subTotal));
    ui->totalTaxBox->setText("$" + QString::number(taxedTotal));
    ui->grandTotalBox->setText("$" + QString::number(grandTotal));



}

ShoppingCart::~ShoppingCart()
{
    delete ui;
}
void ShoppingCart:: SetList(list<FoodItem*> foodieList)
{
    foodieItemsList = foodieList;
}
