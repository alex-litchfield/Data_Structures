// File:    Order.cpp
// Purpose: Implementation file for the Order class.

#include <string> //gives access to string functions
#include <list> //gives access to list functions
#include <algorithm> //gives access to sort function
#include "Order.h" // allows access to the header file

//Constructor
Order::Order(int _order_id, int _promised_time, std::list <std::string> _order_items) {
    order_id=_order_id;
    promised_time=_promised_time;
    time_to_complete=_promised_time;
    // Copying _order_items to order_items
    order_items.assign(_order_items.begin(), _order_items.end());
}

//Accessors
std::list<std::string> Order::getItems() const{
    return order_items;
}

int Order::getPromisedTime() const {
    return promised_time;
}

int Order::getTimeToComplete() const {
    return time_to_complete;
}

int Order::getId() const {
    return order_id;
}

//Modifiers
void Order::setTimeToComplete(int new_time) {
    time_to_complete=new_time;
}

//Returns true if order1 has a smaller remaining amount of time than item 2, or if both have equal remaining times and item1 has a smaller ID
bool sort_orders_by_time(const Order &order1, const Order &order2) {
    return (order1.getTimeToComplete()<order2.getTimeToComplete() || (order1.getTimeToComplete()==order2.getTimeToComplete() && order1.getId()<order2.getId()));
}

//Returns true if order1's id is less than order2's id
bool sort_orders_by_id(const Order &order1, const Order &order2)  {
    return order1.getId()<order2.getId();
}