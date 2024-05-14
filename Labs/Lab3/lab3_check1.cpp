#include <iostream> // library for reading & writing from the console/keyboard
#include <fstream> //library for reading and writing from other files
#include <cmath>

void compute_squares(unsigned int array_a[], unsigned int array_b[], unsigned int n) {
     unsigned int *ptr_a = &array_a[0];
     unsigned int *ptr_b = &array_b[0];
     for(int i = 0; i < 5; i++) {
        *ptr_b=pow(*ptr_a, 2);
        ptr_a++;
        ptr_b++;
     }
}

int main() {
    //unsigned int n=7;
    //unsigned int array_a[7]={1, 2, 3, 4, 5, 65535, 65536};
    unsigned int array_b[2];
    unsigned int array_a[2]={65535};
    compute_squares(array_a, array_b, 2);
    for (int i=0; i<2; i++) {
        std::cout<< array_b[i] <<" " <<std::endl;
    }
}