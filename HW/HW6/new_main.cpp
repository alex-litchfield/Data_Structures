#include <iostream> //library for reading & writing from the console/keyboard
#include <fstream>  //library for reading and writing from other files
#include <vector>   //library for vectors and their functions
#include <string>   //library for strings and their commands
#include "board.h"  //gives this file access to the Board class

//RULES:
//start on smallest zone
//stop if we end up in a state which the program has already seen
//vector of things weve already seen before
//Each row or column can have UP TO S stars in them
//Each zone must have exactly S stars in them
//Boards can be rectangles

//checks if a string is a number or an actual string
bool is_number(std::string &num_string){
    std::string::const_iterator it = num_string.begin();
    while (it != num_string.end() && std::isdigit(*it)) {
        ++it;
    }
    return !num_string.empty() && it == num_string.end();
}

//the recursive function to solve boards, recreate them and put them in the solutions vector.
void solve(Board &editing_board, std::vector<Board> &solutions, int star_requirement, int height, int width) {
    bool solution=true;
    int star_counter=0;
    //are there exactly S stars in each zone
    for (int i=0; i<editing_board.get_zones().size(); i++) {
        if (stoi(editing_board.get_zones()[i][2])!=star_requirement) {
            solution=false;
            break;
        }
    }
    if (solution==true) {
        //are there up to S stars in each row
        star_counter=0;
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                if (editing_board.get_board_vector()[i][j]=="@") {
                    star_counter++;
                }
            }
            if (star_counter>star_requirement) {
                solution=false;
                break;
            }
        }
    }
    if (solution==true) {
        //are there up to S stars in each column
        star_counter=0;
        for (int i=0; i<height; i++) {
            if (editing_board.get_board_vector()[i][0]=="@") {
                star_counter++;
            }
        }
        if (star_counter>star_requirement) {
            solution=false;
        }
    }
    if (solution==true) { 
        solutions.push_back(editing_board);
    }
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            //validity
            editing_board.edit_point(i,0,"@");
        }
    }
}

int main(int argc, char *argv[]) {
    //Error Checks are done first

    //Error check for if there are the correct amount of arguments present.
    if (argc!=6) {
        std::cerr << "Requires 5 total arguments." <<std::endl;
        exit(1);
    }
    //Error check for if input file is valid.
    std::ifstream infile(argv[1]);
    if (!infile.good()) {
        std::cerr << "Can't open " << argv[1] << " to read" << std::endl;
        exit(1);
    }
    infile.close();
    //Error check for if output file is valid.
    std::ofstream outfile(argv[2]);
    if (!outfile.good()) {
        std::cerr << "Can't open " << argv[2] << " to write" << std::endl;
        exit(1);
    }
    outfile.close();
    //Error check for if there is a valid number of stars (one or more).
    if (*argv[3]<1) {
        std::cerr << "Requires a number of stars greater than 0." << std::endl;
        exit(1);
    }
    //Error check for if output mode is valid ("count" or "print")
    if (argv[4]!=std::string("count") && argv[4]!=std::string("print")) {
        std::cerr << "Ouput mode must be 'count' or 'print'." << std::endl;
        exit(1);
    }
    //Error check for if solution mode is valid ("one_solution" or "all_solutions")
    if (argv[5]!=std::string("one_solution") && argv[5]!=std::string("all_solutions")) {
        std::cerr << "Solution mode must be 'one_solution' or 'all_solutions'." << std::endl;
        exit(1);
    }

    //Grabs all the information from the input file and incorporates it into a board object

    infile.open(argv[1]);
    std::string input1;
    std::string input2;
    bool board_size=true;
    int height;
    int width;
    std::string current_zone_name;
    int current_zone=-1;
    Board original_board;
    while (infile >> input1 >> input2) { 
        if (board_size==true) { //only occurs on first line in txt file
            height=stoi(input1);
            width=stoi(input2);
            board_size=false;
            original_board.set_height(height);
            original_board.set_width(width);
            original_board.create_vector();
        }
        else if (is_number(input1)==false) { //input1 is a letter
            current_zone_name=input1;
            original_board.add_zone(current_zone_name, input2);
            current_zone++;
        }
        else { //input 1 is a number
            original_board.add_point(stoi(input2), stoi(input1), current_zone);
        }
    }
    infile.close();
    outfile.open(argv[2]);

    //creates a board to edit on and a vector of possible solutions, as well as 
    //calling the recursive function

    std::vector<Board> solutions;
    Board editing_board;
    editing_board.set_height(height);
    editing_board.set_width(width);
    editing_board.create_vector();
    solve(editing_board, solutions, *argv[3], height, width);

    //Sends everything to the output file
    //based on conditions given in the arguments
    outfile << "Number of solutions: " << solutions.size() << "\n" << "\n";
    if (argv[5]!=std::string("one_solution") && argv[4]!=std::string("print") ) {
        outfile << "Solution 1\n" << solutions[0];
    }
    else if (argv[5]!=std::string("all_solutions") && argv[4]!=std::string("print") ) {
        for (int i=0; i<solutions.size(); i++) {
            outfile << "Solution " << i+1 << "\n";
            outfile << solutions[0];
        }
    }
}