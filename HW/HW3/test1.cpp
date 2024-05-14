#include <iostream>
int main() {
    std::string** temp = new std::string* [total_cols+1];
        int* temp_col_data=new int [total_cols+1];
        for (int i; i<total_cols; i++) { //copies contents to temp //CHECK THE I
            temp[i]=m_data[i];
            temp_col_data[i]=col_data[i];
        }
        temp[total_cols] = new std::string[1]; //creates an array for the col
        temp[total_cols][0]=token; //adds new token
        delete [] m_data; //removes old board
        m_data=temp;
        temp_col_data[total_cols]=1;
        delete [] col_data;
        col_data=temp_col_data;
        
        total_cols=total_cols+1;
}
