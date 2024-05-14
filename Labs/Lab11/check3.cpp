#include <iostream>
#include <string>
void reverse1(std::string& curr, int count, int lastcount){
    if(count>lastcount){
        return;
    }
    char temp = curr[count];
    curr[count] = curr[lastcount];
    curr[lastcount] = temp;
    reverse1(curr,count+1,lastcount-1);
}

void reverse(std::string& curr){
    if(curr.length()>1){
        reverse1(curr,0,curr.length()-1);
    }
}

int main() {
    std::string a = "ThisIsEven";
    std::string b = "ThisIsOdd";
    std::string c(a);
    std::string d(b);
    reverse(c);
    reverse(d);
    std::cout << a << " reversed is " << c << std::endl;
    std::cout << b << " reversed is " << d << std::endl;
}