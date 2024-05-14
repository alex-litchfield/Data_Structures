#include <iostream>
#include <list>

int main()
{
    std::list<std::string> list = { "blue", "red", "green" };
    for (auto it = list.begin(); it != list.end(); it++) {
        std::cout << *it << std::endl;
    }
 
    return 0;
}
