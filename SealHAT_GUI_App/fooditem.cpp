#include "fooditem.h"

/**
 * @brief FoodItem::FoodItem
 */
FoodItem :: FoodItem()
{
    _name = "";
    _price = 0.0;
    _quantity = 0;
}

/**
 * @brief FoodItem::FoodItem
 * @param newName
 * @param newPrice
 * @param newQuantity
 */
FoodItem::FoodItem(QString newName, double newPrice, unsigned short newQuantity) {
    _name = newName;
    _price = newPrice;
    _quantity = newQuantity;
}

FoodItem::FoodItem(QString newFromWhere, QString newName, float newPrice, unsigned short newQuantity) {
    _fromWhere = newFromWhere;
    _name = newName;
    _price = newPrice;
    _quantity = newQuantity;
}
FoodItem::FoodItem(int id, QString newName, double newPrice, unsigned short newQuantity)
{
    _account_ID =id;
    _name=newName;
    _price=newPrice;
    _quantity=newQuantity;
}
/**
 * @brief FoodItem::~FoodItem
 */
FoodItem :: ~FoodItem()
{

}

/**
 * @brief FoodItem::getName
 * @return
 */
QString FoodItem :: getName() const
{
    return _name;
}

/**
 * @brief FoodItem::getQuantity
 * @return
 */
unsigned short FoodItem :: getQuantity() const
{
    return _quantity;
}

/**
 * @brief FoodItem::getPrice
 * @return
 */
double FoodItem :: getPrice() const
{
    return _price;
}

/**
 * @brief FoodItem::getRestaurantID
 * @return
 */
QString FoodItem :: getFromWhere() const
{
    return _fromWhere;
}

int FoodItem::getAccountID() const {
    return _account_ID;
}

/**
 * @brief FoodItem::setName
 * @param newName
 */
void FoodItem :: setName(QString newName)
{
    _name = newName;
}

/**
 * @brief FoodItem::setPrice
 * @param newPrice
 */
void FoodItem :: setPrice(double newPrice)
{
    _price = newPrice;
}

/**
 * @brief FoodItem::setQuantity
 * @param newQuantity
 */
void FoodItem :: setQuantity(unsigned short newQuantity)
{
    _quantity = newQuantity;
}




