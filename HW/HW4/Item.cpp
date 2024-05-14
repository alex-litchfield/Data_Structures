// File:    item.cpp
// Purpose: Implementation file for the Item class.

#include "Item.h" // allows access to the header file
#include <algorithm> //gives access to sort function

//Constructor
Item::Item(std::string _item_name) {
    item_name=_item_name;
    cook_time=-1;
}
//Accessors
int Item::getCookTime() const{
    return cook_time;
}

std::string Item::getName() const{
    return item_name;
}
//Modifiers
void Item::setCookTime(int new_cook_time) {
    cook_time=new_cook_time;
}

//Returns true if item1 has a smaller cook time than item2 or item1 and item2 have the same cook time but item1's id is first in alphabetical order
bool sort_items_by_time(const Item &item1, const Item &item2) {
    int name_order=item1.getName().compare(item2.getName()); //0 when equal, neg when order1 is less, and pos when order2 is greater
    if (item1.getCookTime()<item2.getCookTime()) {
        return true;
    }
    else if (item1.getCookTime()>item2.getCookTime()) {
        return false;
    }
    else if (item1.getCookTime()==item2.getCookTime() && name_order<0) {
        return true;
    }
    else {
        return false;
    }
}