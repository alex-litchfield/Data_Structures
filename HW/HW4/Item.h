// File:     Item.h
// Purpose:  Header file with declaration of the Item class, including member functions and private member variables.

#ifndef __Item_h_ //error guards
#define __Item_h_

#include <list>
#include <string>

class Item {
public:
    //Constructor
    Item(std::string _item_name);

    //Accessors
    int getCookTime() const;
    std::string getName() const;

    //Modifiers
    void setCookTime(int new_cook_time);


private: 
    // REPRESENTATION (member variables)
    std::string item_name;
    int cook_time;
};

//Returns true if item1 has a smaller cook time than item2 or item1 and item2 have the same cook time but item1's id is first in alphabetical order
bool sort_items_by_time(const Item &item1, const Item &item2);

#endif