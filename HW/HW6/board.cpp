// File:    board.cpp
// Purpose: Implementation file for the Board class.

#include <iostream> // library for reading & writing from the console/keyboard
#include <vector> //library for vectors and their functions
#include <string> //library for strings and their commands
#include "board.h" //allows this file to have access to the header file

//Constructor
Board::Board() {
    height=0;
    width=0;
}

//Accessors
int Board::get_height() const{
    return height;
}
int Board::get_width() const{
    return width;
}
std::vector<std::vector<std::string>> Board::get_zones() const{
    return zones;
}

std::vector<std::vector<std::string>> Board::get_board_vector() const{
    return board_vector;
}

//Modifiers
void Board::set_height(int a_height) {
    height=a_height;
}
void Board::set_width(int a_width) {
    width=a_width;
}
//gives board object the go-ahead to create its vector of parts
void Board::create_vector() {
    for (int i=0; i<height; i++) {
        std::vector<std::string> new_row(width, "0");
        board_vector.push_back(new_row);
    }
}
//makes the board object add a new zone to its zone vector.
void Board::add_zone(std::string zone_name, std::string zone_size) {
    std::vector<std::string> new_zone{zone_name, zone_size, "0"}; //the 3rd element is how many stars are in it
    zones.push_back(new_zone);
}
//makes the board add a new point into the board vector and zone class
void Board::add_point(int height_pos, int width_pos, int zone_number) {
    board_vector[height_pos][width_pos]=zones[zone_number][0];
    int new_zone_size=stoi(zones[zone_number][1])+1;
    zones[zone_number][1]=std::to_string(new_zone_size);
}
//changes a symbol within the board vector
void Board::edit_point(int height_pos, int width_pos, std::string new_char) {
    board_vector[height_pos][width_pos]=new_char;
}
//Prints the board through the ostream when called
std::ostream& operator<< (std::ostream& ostr, const Board& b) {
    for (int i=0; i<b.get_height(); i++) {
        for (int j=0; j<b.get_width(); j++) {
            if (j==b.get_width()-1) {
                ostr << b.get_board_vector()[i][j] << "\n";
            }
            else { 
                ostr << b.get_board_vector()[i][j];
            }
        }
    }
    return ostr;
}
