// File:     board.h
// Purpose:  Header file with declaration of the Board class, including member functions and private member variables.

#ifndef __board_h_ //error guards
#define __board_h_

#include <vector> //library for vectors and their functions
#include <iostream> // library for reading & writing from the console/keyboard

class Board {
public:
    //Constructor
    Board();

    // ACCESSORS
    int get_height() const;
    int get_width() const;
    std::vector<std::vector<std::string>> get_zones() const;
    std::vector<std::vector<std::string>> get_board_vector() const;

    // MODIFIERS
    void set_height(int a_height);
    void set_width(int a_width);
    //gives board object the go-ahead to create its vector of parts
    void create_vector();
    //makes the board object add a new zone to its zone vector.
    void add_zone(std::string zone_name, std::string zone_size);
    //makes the board add a new point into the board vector and zone class
    void add_point(int height_pos, int width_pos, int zone_number);
    //changes a symbol within the board vector
    void edit_point(int height_pos, int width_pos, std::string new_char);
  
    //REPRESENTATION
    int height;
    int width;
    std::vector<std::vector<std::string>> board_vector;
    std::vector<std::vector<std::string>> zones;
};
// operator<< to allow output
std::ostream& operator<< (std::ostream& ostr, const Board& b);

#endif