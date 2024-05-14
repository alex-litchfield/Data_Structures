// File:     Board.h
// Purpose:  Header file with declaration of the Board class, including member functions and private member variables.

#ifndef __Board_h_ //error guards
#define __Board_h_

#include <iostream>

class Board {
public:
    //Constructor
    Board(std::string a_p1_token, std::string a_p2_token, std::string a_blank_token);
    //Destructor
    ~Board();
    //Copy Constructor
    Board(const Board &old_obj);
    //Assignment Operator
    Board& operator=(const Board& b);

    // ACCESSORS
    int numRows() const;
    int numColumns() const;
    std::string getBlankToken() const;
    std::string getP1Token() const;
    std::string getP2Token() const;
    int numTokensInRow(int row) const;
    int numTokensInColumn(int col) const;
    std::string ** getBoard() const;

    // MODIFIERS
    std::string insert(int col, bool player);
    void clear();
private: 
    //PRIVATE MEMBER FUNCTIONS
    void copy(const Board& b); 

    // REPRESENTATION (member variables)
    int row, col, total_rows, total_cols;
    std::string p1_token, p2_token, blank_token;
    bool player; //true for player 1 and false for plyer 2
    std::string** m_data;
    int* col_data;

};

// operator<< to allow output
std::ostream& operator<< (std::ostream& ostr, const Board& n);

#endif