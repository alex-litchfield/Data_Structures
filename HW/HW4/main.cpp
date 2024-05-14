// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <cassert> //gives access to assert function
#include <iostream> // gives access to input/output terminal functions (cin/cout)
#include <string> //gives access to string functions (to_string)
#include <list> //gives access to list functions
#include <algorithm> //gives access to sort function
#include "Order.h" //gives access to header file of the Order Class
#include "Item.h"//gives access to header file of the Item Class

typedef std::list <Order> OrderList; //holds orders
typedef std::list <Item> KitchenList; //holds items 

//Needed for CanFillOrder()
typedef std::list <KitchenList::const_iterator> OrderFillList;

//Helper function
//Returns true if order can be fulfilled, and false otherwise. If true, then
//items_to_remove has iterators to kitchen_completed for all items that are used 
//in the order.
bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove);

int main() {
  //lists of different types
  OrderList orders;
  KitchenList food_cooking;
  KitchenList food_completed;

  std::string token;
  while (std::cin >> token) {
    if (token == "add_order") { //adds an order to the list of nonfilled/nonexpired orders
      int id, promised_time, n_items = 0;
      std::string next_item;
      std::list <std::string> order_items;

      std::cin >> id >> promised_time >> n_items;
      assert(n_items > 0);

      std::cout << "Received new order #"+std::to_string(id)+" due in "+std::to_string(promised_time)+" minute(s):" << std::endl; //my line
      for (int i = 0; i < n_items; i++) {
        std::cin >> next_item;
        order_items.push_back(next_item);
        std::cout << "  "+next_item <<std::endl;
      }
      //added by me
      Order o(id, promised_time, order_items);
      orders.push_back(o);
      orders.sort(sort_orders_by_time);
    }
    /* YOU MUST FINISH THIS IMPLEMENTATION */
    else if (token == "add_item") { //adds an item to the list of items cooking in the kitchen
      int cook_time = -1; //this is bc time actually CAN be zero in the list
      std::string name;
      std::cin >> cook_time >> name;
      assert(cook_time >= 0);
      //added by me
      Item t(name);
      t.setCookTime(cook_time);
      food_cooking.push_back(t);
      food_cooking.sort(sort_items_by_time);
      std::cout << "Cooking new " << name << " with " << cook_time << " minute(s) left." << std::endl;
    }
    /* YOU MUST FINISH THIS IMPLEMENTATION */
    else if (token == "print_orders_by_time") { //prints out all the orders (and their contents) by time first then ID.
      std::list<Order>::iterator order_it;
      std::cout << "Printing " << orders.size() << " order(s) by promised time remaining:" << std::endl;
      //iterates through list based on number of orders
      for (order_it = orders.begin(); order_it != orders.end(); order_it++) {
        std::list<std::string>::iterator order_items_it;
        std::cout << "  #" << (*order_it).getId() << " (" << (*order_it).getTimeToComplete() << " minute(s) left):" << std::endl;
        std::list<std::string> item_names;
    		item_names = (*order_it).getItems();
        //iterates through the number of items within an order
    		for(order_items_it = item_names.begin(); order_items_it != item_names.end(); ++order_items_it) {
	    		std::cout << "    " << *order_items_it << std::endl;
	    	}
      }
    }
    /* YOU MUST FINISH THIS IMPLEMENTATION */
    else if (token == "print_orders_by_id") { //prints out all the orders (and their contents) by ID first
      orders.sort(sort_orders_by_id);
      std::cout << "Printing "+std::to_string(orders.size())+" order(s) by ID:" <<std::endl;
      std::list<Order>::iterator order_it2;
      //iterates through number of orders
      for (order_it2 = orders.begin(); order_it2 != orders.end(); order_it2++) {
        std::list<std::string>::iterator order_items_it;
        std::cout << "  #"+std::to_string((*order_it2).getId())+" ("+std::to_string((*order_it2).getTimeToComplete())+" minute(s) left):" << std::endl;
        std::list<std::string> item_names;
    		item_names = (*order_it2).getItems();
        //iterates through number of items in an order
    		for(order_items_it = item_names.begin(); order_items_it != item_names.end(); ++order_items_it) {
	    		std::cout << "    " << *order_items_it << std::endl;
	    	}
      }
      //sorts back to by time after
      orders.sort(sort_orders_by_time);
    }
    
    /* YOU MUST FINISH THIS IMPLEMENTATION */
    else if (token == "print_kitchen_is_cooking") { //prints out all the items still cooking in the kicthen
      std::list<Item>::iterator cooking_it;
      std::cout << "Printing "+std::to_string(food_cooking.size())+" items being cooked:" << std::endl;
      //Iterates through list of food still cooking
      for (cooking_it = food_cooking.begin(); cooking_it != food_cooking.end(); cooking_it++) {
          int time = cooking_it->getCookTime();
          std::string food_name = cooking_it->getName();
          std::cout << "  "+food_name+" ("+std::to_string(time)+" minute(s) left)" << std::endl;;
      }
    }
    /* YOU MUST FINISH THIS IMPLEMENTATION */
    else if (token == "print_kitchen_has_completed") { //prints out food the kitchen has finished cooking
      std::list<Item>::iterator complete_it;
      std::cout << "Printing "+std::to_string(food_completed.size())+" completely cooked items:" << std::endl;
      //Iterates through list of food done cooking
      for (complete_it = food_completed.begin(); complete_it != food_completed.end(); complete_it++) {
          std::string food_name = complete_it->getName();
          std::cout <<"  "+food_name << std::endl;
      }
    }
    /* YOU MUST FINISH THIS IMPLEMENTATION */
    else if (token == "run_for_time") { //runs events until the given time has come to pass
      int run_time = 0;
      std::cin >> run_time;
      assert(run_time >= 0);
      //added by me
      std::list<Item>::iterator kitchen_it1;
      std::list<Order>::iterator order_it1;
      std::list<Order>::iterator order_it3;
      std::list<KitchenList::const_iterator>::iterator CFO_it;
      OrderFillList list_of_its;
      std::cout << "===Starting run of " << std::to_string(run_time) << " minute(s)===" << std::endl;
      for (int i=0; i< run_time; i++) {
        //if food items have a time of zero, they are removed from the food_cooking list to the food_completed list.
        for (kitchen_it1 = food_cooking.begin(); kitchen_it1!=food_cooking.end(); ) {
          int new_cook_time = kitchen_it1->getCookTime();
          if (new_cook_time==0) {
            std::cout << "Finished cooking " << (*kitchen_it1).getName() << std::endl;
            food_completed.push_back(*kitchen_it1);
            food_cooking.erase(kitchen_it1);
            kitchen_it1=food_cooking.begin();
          }
          else {
            ++kitchen_it1;
          }
        }
        //if an rder can be filled
        for (order_it3 = orders.begin(); order_it3!=orders.end()&& orders.size()>0; ) {
          if (food_completed.size()>0 && CanFillOrder(*order_it3, food_completed, list_of_its)==true) {
            std::cout << "Filled order #" << order_it3->getId() << std::endl;
            for (CFO_it = list_of_its.begin(); CFO_it != list_of_its.end(); ++CFO_it) {
              std::cout << "Removed a " << (*CFO_it)->getName() << " from completed items." << std::endl;
              food_completed.erase(*CFO_it);
            }
            orders.erase(order_it3);
            order_it3=orders.begin();
          }
          else {
            ++order_it3;
          }
        }
        //if an order expired
        for (order_it3 = orders.begin(); order_it3 != orders.end(); ) {
          if ((*order_it3).getTimeToComplete()<=0) {
            std::cout << "Order # " << (*order_it3).getId() << " expired." << std::endl;
            orders.erase(order_it3);
            order_it3=orders.begin();
          }
          else {
            order_it3++;
          }
        }
        //time goes down by 1 for orders and food cooking
        for(order_it3 = orders.begin(); order_it3 != orders.end(); ++order_it3) {
  			  order_it3->setTimeToComplete(order_it3->getTimeToComplete()-1);
        }
        for(kitchen_it1 = food_cooking.begin(); kitchen_it1 != food_cooking.end(); ++kitchen_it1) {
          kitchen_it1->setCookTime(kitchen_it1->getCookTime()-1);
        }
      }
      //CHECK EVERYTHING AGAIN AT THE END
      //if food items have a time of zero, they are removed from the food_cooking list to the food_completed list.
      for (kitchen_it1 = food_cooking.begin(); kitchen_it1!=food_cooking.end(); ) {
        int new_cook_time = kitchen_it1->getCookTime();
        if (new_cook_time==0) {
          std::cout << "Finished cooking " << (*kitchen_it1).getName() << std::endl;
          food_completed.push_back(*kitchen_it1);
          food_cooking.erase(kitchen_it1);
          kitchen_it1=food_cooking.begin();
        }
        else {
          ++kitchen_it1;
        }
      }
      //if an order can be filled
      for (order_it3 = orders.begin(); order_it3!=orders.end()&& orders.size()>0; ) {
        if (food_completed.size()>0 && CanFillOrder(*order_it3, food_completed, list_of_its)==true) {
          std::cout << "Filled order #" << order_it3->getId() << std::endl;
          for (CFO_it = list_of_its.begin(); CFO_it != list_of_its.end(); ++CFO_it) {
            std::cout << "Removed a " << (*CFO_it)->getName() << " from completed items." << std::endl;
            food_completed.erase(*CFO_it);
          }
          orders.erase(order_it3);
          order_it3=orders.begin();
        }
        else {
          ++order_it3;
        }
      }
      //if an order expired
      for (order_it3 = orders.begin(); order_it3 != orders.end(); ) {
        if ((*order_it3).getTimeToComplete()<=0) {
          std::cout << "Order # " << (*order_it3).getId() << " expired." << std::endl;
          orders.erase(order_it3);
          order_it3=orders.begin();
        }
        else {
          order_it3++;
        }
      }
      std::cout << "===Run for specified time is complete===" <<std::endl;
    }
    /* YOU MUST FINISH THIS IMPLEMENTATION */
    else if (token == "run_until_next") { //runs until the next event occurs
      std::cout << "Running until next event." << std::endl;
      /* YOU MUST FINISH THIS IMPLEMENTATION */
	    //check for anything in orders or food_cooking
	    if(orders.size() == 0 && food_cooking.size() == 0) {
	  	  std::cout << "No events waiting to process." << std::endl;
	    } 
      else {
        int mins_passed = 0;
        //will break when this bool end becomes true
        while(true) {
          bool end = false;
          //if cooking for an item can be completed, it is removed from food_cooking and put into food_completed
          std::list<Item>::iterator item_it;
          std::list<Order>::iterator order_it;
          for(item_it = food_cooking.begin(); item_it != food_cooking.end(); ++item_it) {
            if(item_it->getCookTime() < 1) {
              std::cout << "Finished cooking " << item_it->getName() << std::endl;
              food_completed.push_back(*item_it);
              food_cooking.erase(item_it);
              end=true;
              break;
            }
          }
          if(end==true) { //Are we done yet?
            break;
          }
          //order can be filled
          OrderFillList list_of_its;
          std::list<KitchenList::const_iterator>::iterator CFO_it;
          for(order_it = orders.begin(); order_it!= orders.end(); ++order_it) {
            if(CanFillOrder(*order_it, food_completed, list_of_its)) {
              for(CFO_it = list_of_its.begin(); CFO_it != list_of_its.end(); ++CFO_it) {
                food_completed.erase(*CFO_it);
              }
              std::cout << "Filled order #" << order_it->getId() << std::endl;
              orders.erase(order_it);
              end=true;
              break;
            }
          }
          if(end==true) { //Are we done yet?
            break;
          }
          //If an order expiration
          for(order_it = orders.begin(); order_it != orders.end(); ++order_it) {
            if(order_it->getTimeToComplete() <= 0) {
              std::cout << "Order # " << order_it->getId() << " expired." << std::endl;
              orders.erase(order_it);
              end=true;
              break;
            }
          }
          if(end==true) { //Are we done yet?
            break;
          }
          //time goes down by 1 for orders and food cooking
          for(order_it = orders.begin(); order_it != orders.end(); ++order_it) {
            order_it->setTimeToComplete(order_it->getTimeToComplete()-1);
          }
          for(item_it = food_cooking.begin(); item_it != food_cooking.end(); ++item_it) {
            item_it->setCookTime(item_it->getCookTime()-1);
          }
          mins_passed++;
        }
        std::cout << mins_passed << " minute(s) have passed." << std::endl;
      }
    }
  }
  return 0;
}


bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove) {
  items_to_remove.clear(); //We will use this to return iterators in kitchen_completed

  //Simple solution is nested for loop, but I can do better with sorting...

  std::list <std::string> order_items = order.getItems();
  order_items.sort();

  std::list<std::string>::const_iterator item_it;
  std::string prev_item = "";
  KitchenList::const_iterator kitchen_it;

  for (item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
    bool found = false;

    /*Start back at beginnging of list if we're looking for something else
     *Thanks to sorting the order_items list copy, we know we're done with
       whatever kind of item prev_item was!*/
    if (prev_item != *item_it) {
      kitchen_it = kitchen_completed.begin();
      prev_item = *item_it;
    }

    /*Resume search wherever we left off last time (or beginning if it's a
    new kind of item*/
    for (; !found && kitchen_it != kitchen_completed.end(); kitchen_it++) {
      if (kitchen_it->getName() == *item_it) {
        items_to_remove.push_back(kitchen_it);
        found = true;
      }
    }

    //If we failed to satisfy an element of the order, no point continuing the search
    if (!found) {
      break;
    }
  }

  //If we couldn't fulfill the order, return an empty list
  if (items_to_remove.size() != order_items.size()) {
    items_to_remove.clear();
    return false;
  }

  return true;
}

