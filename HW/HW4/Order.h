// File:     Order.h
// Purpose:  Header file with declaration of the Order class, including member functions and private member variables.

#ifndef __Order_h_ //error guards
#define __Order_h_

#include <list>

class Order {
public:
    //Constructor
    Order(int _order_id, int _promised_time, std::list <std::string> _order_items);
    
    //Accessors
    std::list<std::string> getItems() const;
    int getPromisedTime() const;
    int getTimeToComplete() const;
    int getId() const;
    //Modifiers
    void setTimeToComplete(int new_time);

private: 
    //PRIVATE MEMBER FUNCTIONS

    // REPRESENTATION (member variables)
    int order_id, promised_time, time_to_complete;
    std::list <std::string> order_items;
};

//Returns true if order1 has a smaller remaining amount of time than item 2, or if both have equal remaining times and item1 has a smaller ID
bool sort_orders_by_time(const Order &order1, const Order &order2);
//Returns true if order1's id is less than order2's id
bool sort_orders_by_id(const Order &order1, const Order &order2);

#endif