// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>

// add a number, name pair to the phonebook O(number)
void add(std::map<int, std::string> &phonebook, int number, std::string name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling O(number)
void identify(std::map<int, std::string> &phonebook, int number) {
  std::map<int, std::string>::iterator it = phonebook.find(number);
  if (it == phonebook.end()) {
    std::cout << "unknown caller!" << std::endl;;
  }
  else {
    std::cout << phonebook[number] << " is calling!" << std::endl;
  }
}


int main() { // -better because it allows us to use numbers larger than the size of the phonebook
  std::map<int, std::string> phonebook;

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");
  add(phonebook, 7777777, "alex");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
  identify(phonebook, 7777777);
}
