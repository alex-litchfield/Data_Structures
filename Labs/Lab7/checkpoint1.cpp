#include <iostream>
#include <vector>
#include <ostream>

int countPaths(int x, int y) {
    if (x==0 || y==0) {
        return 1;
    }
    return (countPaths(x-1, y) + countPaths(x, y-1));
}

int main() {
    int x, y;
    std::cin >> x >> y;
    std::cout << "Number of Paths " << countPaths(x, y) << std::endl;
    return 0;
}