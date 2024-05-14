#include <iostream>  //library for reading & writing from the console/keyboard
#include <fstream>   //library for reading and writing from other files
#include <vector>
#include <string>

//RULES:
    //start on smallest zone
    //stop if we end up in a state which the program has already seen
    //vector of things weve already seen before
    //Each row or column can have UP TO S stars in them
    //Each zone must have exactly S stars in them
    //Boards can be rectangles

    //g++ main.cpp board.cpp -o main.exe -Wall -Wextra
    //./a.out [input file] [output file] [stars per zone] [output mode] [solution mode]

bool is_number(const std::string& num_string){ //checks if a string is a number or an actual string
    std::string::const_iterator it = num_string.begin();
    while (it != num_string.end() && std::isdigit(*it)) {
        ++it;
    }
    return !num_string.empty() && it == num_string.end();
}

void solve(std::vector<std::vector<std::string>> &board, std::vector<std::vector<std::string>> &zones, int height, int width, int star_requirement) {
    bool solution=true;
    int star_counter=0;
    //are there exactly S stars in each zone
    for (int i=0; i<zones.size(); i++) {
        if (stoi(zones[i][2])!=star_requirement) {
            solution=false;
            break;
        }
    }
    if (solution==true) {
        //are there up to S stars in each row
        star_counter=0;
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                if (board[i][j]=="@") {
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
            if (board[i][0]=="@") {
                star_counter++;
            }
        }
        if (star_counter>star_requirement) {
            solution=false;
        }
    }
    if (solution==true) {
        //are any stars touching
        for (int i=0; i<height; i++) { //i=0 is left column, j=0 is top row
            for (int j=0; j<width; j++) {
                //TOP LEFT CASE
                if (i==0 && j==0 && board[i][j]=="@" && (board[i+1][j]=="@" || board[i][j+1]=="@" || board[i+1][j+1]=="@") ) {
                    solution=false;
                }
                //BOTTOM LEFT CASE
                else if (i==height-1 && j==0 && board[i][j]=="@" && (board[i-1][j]=="@" || board[i][j+1]=="@" || board[i-1][j+1]=="@") ) {
                    solution=false;
                }
                //BOTTOM RIGHT LEFT CASE
                else if (i==height-1 && j==width-1 && board[i][j]=="@" && (board[i-1][j]=="@" || board[i][j-1]=="@" || board[i-1][j-1]=="@") ) {
                    solution=false;
                }
                //TOP RIGHT LEFT CASE
                else if (i==0 && j==width-1 && board[i][j]=="@" && (board[i+1][j]=="@" || board[i][j-1]=="@" || board[i+1][j-1]=="@") ) {
                    solution=false;
                }
                //TOP ROW
                else if (i==0 && board[i][j]=="@" && (board[i][j-1]=="@" || board[i][j+1]=="@" || board[i+1][j+1]=="@" || board[i+1][j-1]=="@" || board[i+1][j]=="@") ) {
                    solution=false;
                }
                //BOTTOM ROW
                else if (i==height-1 && board[i][j]=="@" && (board[i][j-1]=="@" || board[i][j+1]=="@" || board[i-1][j+1]=="@" || board[i-1][j-1]=="@" || board[i-1][j]=="@") ) {
                    solution=false;
                }
                //LEFT COLUMN
                else if (j==0 && board[i][j]=="@" && (board[i+1][j]=="@" || board[i-1][j]=="@" || board[i+1][j+1]=="@" || board[i-1][j+1]=="@" || board[i][j+1]=="@") ) {
                    solution=false;
                }
                //RIGHT COLUMN
                else if (j==width-1 && board[i][j]=="@" && (board[i+1][j]=="@" || board[i-1][j]=="@" || board[i+1][j-1]=="@" || board[i-1][j-1]=="@" || board[i][j-1]=="@") ) {
                    solution=false;
                }
                //OTHER
                else if (board[i][j]=="@" && (board[i-1][j]=="@" || board[i-1][j-1]=="@" || board[i][j-1]=="@" || board[i+1][j-1]=="@" || board[i+1][j]=="@" || board[i+1][j+1]=="@" || board[i][j+1]=="@" || board[i-1][j+1]=="@") ) {
                    solution=false;
                }
            }
        }
    }
    if (solution==true) { 
        int x=0;
        //add to solution vector
    }
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            
            board[i][j]="@";
        }
    }
}

int main(int argc, char *argv[]) {
    int star_requirement;
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
    else {
        star_requirement=*argv[3];
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
    infile.open(argv[1]);

    std::string input1;
    std::string input2;
    std::vector<std::vector<std::string>> board;
    std::vector<std::vector<std::string>> zones;
    bool board_size=true;
    int height;
    int width;
    std::string current_zone_name;
    int number_of_zones=0;
    while (infile >> input1 >> input2) { 
        if (board_size==true) { //only occurs on first line in txt file
            height=stoi(input1);
            width=stoi(input2);
            board_size=false;
            for (int i=0; i<height; i++) {
                std::vector<std::string> new_row(width, "0");
                board.push_back(new_row);
            }
        }
        else if (is_number(input1)==false) { //input1 is a letter
            current_zone_name=input1;
            std::vector<std::string> new_zone{current_zone_name, input2, "0"}; //the 3rd element is how many stars are in it
            zones.push_back(new_zone);
            number_of_zones++;
        }
        else { //input 1 is a number
            board[stoi(input2)][stoi(input1)]=current_zone_name;
        }
    }
    std::vector<std::vector<std::vector<std::string>>> solutions;
    solve(board, zones, height, width, star_requirement);
    //Proves that the contents of the input file are correctly moved into the vector
    std::cout << "Number of solutions: " << solutions.size() << std::endl; 
    if (argv[5]!=std::string("one_solution") && argv[4]!=std::string("print") ) {
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                if (j==width-1) {
                    std::cout << board[i][j] << std::endl;
                }
                else {
                    std::cout << board[i][j];
                }
            }
        }
        std::cout<<std::endl;
    }
    else if (argv[5]!=std::string("all_solutions") && argv[4]!=std::string("print") ) {
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                if (j==width-1) {
                    std::cout << board[i][j] << std::endl;
                }
                else {
                    std::cout << board[i][j];
                }
            }
        }
        std::cout<<std::endl;
    }
    //Proves zone info vector works
    /*for (int i=0; i<number_of_zones; i++) {
        std::cout << zones[i][0]+zones[i][1] << std::endl;
    }*/
}
