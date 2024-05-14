#include <iostream> // library for reading & writing from the console/keyboard
#include <fstream> //library for reading and writing from other files
#include <vector> //library for vector functions

//replaces all the specified characters in the inputfile to the new characters 
std::vector<std::string> operation_replace(std::vector<std::string>infile_vector, std::string operation, std::string edited_char, std::string new_char) {
    int vector_size = infile_vector.size();
    int line_size = infile_vector[0].length();
    for (int i=0; i<vector_size; i++) {
        for (int j=0; j<line_size; j++) {
            if (infile_vector[i][j]==edited_char[0]) {
                infile_vector[i][j]=new_char[0];
            }
        }
    }
    return infile_vector;
}

//makes the clusters of "edited_char" characters expand
std::vector<std::string> operation_dilation(std::vector<std::string>infile_vector, std::string operation, std::string edited_char) {
    //edited_char is what the old characters become, so if it was a '-' and it became a 'X', the 'X' would be the edited_char
    std::vector<std::string>outfile_vector=infile_vector; //copies infile contents to outfile
    int vector_size = infile_vector.size();
    int line_size = infile_vector[0].length();
    //begins editing outfile to become dilated
    for (int i=0; i<vector_size; i++) {
        for (int j=0; j<line_size; j++) {
            if (i==0 && j==0 && infile_vector[i][j]==edited_char[0]) { //top left corner of grid
                //if this spot is the edited_char, it spreads to its right and down in the outfile
                outfile_vector[i][j+1]=edited_char[0]; //right
                outfile_vector[i+1][j]=edited_char[0]; //down
            }
            else if (i==0 && j==(line_size-1) && infile_vector[i][j]==edited_char[0]) { //top right corner of grid
                //if this spot is the edited_char, it spreads to its left and down in the outfile
                outfile_vector[i][j-1]=edited_char[0]; //left
                outfile_vector[i+1][j]=edited_char[0]; //down
            }
            else if (i==(vector_size-1) && j==0 && infile_vector[i][j]==edited_char[0]) { //bottom left corner of grid
                //if this spot is the edited_char, it spreads to its right and up in the outfile
                outfile_vector[i][j+1]=edited_char[0]; //right
                outfile_vector[i-1][j]=edited_char[0]; //up
            }
            else if (i==(vector_size-1) && j==(line_size-1) && infile_vector[i][j]==edited_char[0]) { //bottom right corner of grid
                //if this spot is the edited_char, it spreads to its left and up in the outfile
                outfile_vector[i][j-1]=edited_char[0]; //left
                outfile_vector[i-1][j]=edited_char[0]; //up
            }
            else if (i==0 && infile_vector[i][j]==edited_char[0]) { //rest of the top row of the grid
                //if this spot is the edited_char, it spreads to its left, right, and down in the outfile
                outfile_vector[i][j-1]=edited_char[0]; //left
                outfile_vector[i][j+1]=edited_char[0]; //right
                outfile_vector[i+1][j]=edited_char[0]; //down
            }
            else if (i==(vector_size-1) && infile_vector[i][j]==edited_char[0]) { //rest of the bottom row of the grid
                //if this spot is the edited_char, it spreads to its left, right, and up in the outfile
                outfile_vector[i][j-1]=edited_char[0]; //left
                outfile_vector[i][j+1]=edited_char[0]; //right
                outfile_vector[i-1][j]=edited_char[0]; //up
            }
            else if (j==0 && infile_vector[i][j]==edited_char[0]) { //rest of the left column of the grid
                //if this spot is the edited_char, it spreads to its right, up, and down in the outfile
                outfile_vector[i][j+1]=edited_char[0]; //right
                outfile_vector[i-1][j]=edited_char[0]; //up
                outfile_vector[i+1][j]=edited_char[0]; //down
            }
            else if (j==(line_size-1) && infile_vector[i][j]==edited_char[0]) { //rest of the right column of the grid
                //if this spot is the edited_char, it spreads to its left, up, and down in the outfile
                outfile_vector[i][j-1]=edited_char[0]; //left
                outfile_vector[i-1][j]=edited_char[0]; //up
                outfile_vector[i+1][j]=edited_char[0]; //down
            }
            else if (infile_vector[i][j]==edited_char[0]) { //every other spot in the grid
            //if this spot is the edited_char, it spreads to its left, right, up, and down in the outfile
                outfile_vector[i][j-1]=edited_char[0]; //left
                outfile_vector[i][j+1]=edited_char[0]; //right
                outfile_vector[i-1][j]=edited_char[0]; //up
                outfile_vector[i+1][j]=edited_char[0]; //down
            }
        }
    }
    return outfile_vector;
}

//makes the "edited_char" clusters decrease in size
std::vector<std::string> operation_erosion(std::vector<std::string>infile_vector, std::string operation, std::string edited_char, std::string new_char) {
    //edited_char is what the old character which will be replace by new_char
    std::vector<std::string>outfile_vector=infile_vector; //copies infile contents to outfile
    int vector_size = infile_vector.size();
    int line_size = infile_vector[0].length();
    //begins editing outfile to become eroded
    for (int i=0; i<vector_size; i++) {
        for (int j=0; j<line_size; j++) {
            if (i==0 && j==0 && (infile_vector[i][j+1]!=edited_char[0] || infile_vector[i+1][j]!=edited_char[0])) { //top left corner of grid
                //if the spots to the right or under the corner are not the edited_char, it makes the corner become the new_char
                outfile_vector[i][j]=new_char[0];
            }
            else if (i==0 && j==(line_size-1) && (infile_vector[i][j-1]!=edited_char[0] || infile_vector[i+1][j]!=edited_char[0])) { //top right corner of grid
                //if the spots to the left or under the corner are not the edited_char, it makes the corner become the new_char
                outfile_vector[i][j]=new_char[0];
            }
            else if (i==(vector_size-1) && j==0 && (infile_vector[i][j+1]!=edited_char[0] || infile_vector[i-1][j]!=edited_char[0])) { //bottom left corner of grid
                //if the spots to the right or above the corner are not the edited_char, it makes the corner become the new_char
                outfile_vector[i][j]=new_char[0];
            }
            else if (i==(vector_size-1) && j==(line_size-1) && (infile_vector[i][j-1]!=edited_char[0] || infile_vector[i-1][j]!=edited_char[0])) { //bottom right corner of grid
                //if the spots to the left or above the corner are not the edited_char, it makes the corner become the new_char
                outfile_vector[i][j]=new_char[0];
            }
            else if (i==0 && (infile_vector[i][j-1]!=edited_char[0] || infile_vector[i][j+1]!=edited_char[0] || infile_vector[i+1][j]!=edited_char[0]) ) { //rest of the top row of the grid
                //if the spots to the left, right, or below the position are not the edited_char, it makes the position become the new_char
                outfile_vector[i][j]=new_char[0];
            }
            else if (i==(vector_size-1) && (infile_vector[i][j-1]!=edited_char[0] || infile_vector[i][j+1]!=edited_char[0] || infile_vector[i-1][j]!=edited_char[0])) { //rest of the bottom row of the grid
                //if the spots to the left, right, or above the position are not the edited_char, it makes the position become the new_char
                outfile_vector[i][j]=new_char[0];
            }
            else if (j==0 && (infile_vector[i][j+1]!=edited_char[0] || infile_vector[i-1][j]!=edited_char[0] || infile_vector[i+1][j]!=edited_char[0])) { //rest of the left column of the grid
                //if the spots to the right, below, or above the position are not the edited_char, it makes the position become the new_char
                outfile_vector[i][j]=new_char[0];
            }
            else if (j==(line_size-1) && (infile_vector[i][j-1]!=edited_char[0] || infile_vector[i-1][j]!=edited_char[0] || infile_vector[i+1][j]!=edited_char[0])) { //rest of the right column of the grid
                //if the spots to the left, below, or above the position are not the edited_char, it makes the position become the new_char
                outfile_vector[i][j]=new_char[0];
            }
            else if (infile_vector[i][j-1]!=edited_char[0] || infile_vector[i][j+1]!=edited_char[0] || infile_vector[i-1][j]!=edited_char[0] || infile_vector[i+1][j]!=edited_char[0]) { //every other spot in the grid
            //if the spots to the left, right, below, or above the position are not the edited_char, it makes the position become the new_char
                outfile_vector[i][j]=new_char[0];
            }
        }
    }
    return outfile_vector;
}

int main(int argc, char *argv[]) {
    //open a text file and read from it
    std::ifstream infile(argv[1]);
    //this forces the program to print an error and stop if the reading file does not work.
    if (!infile.good()) {
        std::cerr << "Can't open " << argv[1] << " to read" << std::endl;
        exit(1);
    }
    //creates string values for the operations to remove warnings
    std::string dilation_variable="dilation";
    std::string erosion_variable="erosion";
    std::string replace_variable="replace";
    //this forces the program to print an error and stop if the operation is not 'replace', 'dilation', or 'erosion'
    if (argv[3]!=replace_variable && argv[3]!=dilation_variable && argv[3]!=erosion_variable) {
        std::cerr << "The operation " << argv[2] << " does not match 'replace', 'dilation', or 'erosion'" << std::endl;
        exit(1);
    }
    //this forces the program to print an error and stop if the operation is 'replace' or 'erosion'
    if ( (argv[3]==replace_variable || argv[3]==erosion_variable) && argc!=6) {
        std::cerr << "The operation " << argv[3] << " requires 5 input arguments" << std::endl;
        exit(1);
    }
    //this forces the program to print an error and stop if the operation is 'dilation'
    if (argv[3]==dilation_variable && argc!=5) {
        std::cerr << "The operation " << argv[3] << " requires 4 input arguments" << std::endl;
        exit(1);
    }
    // Create a text string, which is used to output the text file
    std::string outText;
    //creates an vector of strings- these strings are each line of the input file
    std::vector<std::string>infile_vector;
    //creates an vector of strings- these strings are each line of the output file
    std::vector<std::string>outfile_vector;
    while (getline (infile, outText)) {
        // adds 'outText' string to the end of the vector
        infile_vector.push_back(outText);
    }
    // Close the the reading file
    infile.close();
    //creates and opens a file to write in
    std::ofstream outfile(argv[2]);
    //this forces the program to print an error and stop if the writing file does not work.
    if (!outfile.good()) {
        std::cerr << "Can't open " << argv[2] << " to write" << std::endl;
        exit(1);
    }
    // If operation is replace, it conducts the "replace" operation in the writing file
        if (argv[3]==replace_variable) {
            outfile_vector=operation_replace(infile_vector, argv[3], argv[4], argv[5]);
            int outfile_vector_size=outfile_vector.size();
            for (int i=0; i < outfile_vector_size; i++) {
                outfile << outfile_vector[i] << std::endl;
            }
        }
    // If operation is dilation, it conducts the "dilation" operation in the writing file
    if (argv[3]==dilation_variable) {
        //makes the 'outfile_vector' variable now hold the dilated vector
        outfile_vector=operation_dilation(infile_vector, argv[3], argv[4]);
        int outfile_vector_size=outfile_vector.size();
        for(int i=0; i < outfile_vector_size; i++) {
             outfile << outfile_vector[i] <<std::endl;
        }
    }
    // If operation is erosion, it conducts the "erosion" operation in the writing file
    else if(argv[3]==erosion_variable) {
        //makes the 'outfile_vector' variable now hold the dilated vector
        outfile_vector=operation_erosion(infile_vector, argv[3], argv[4], argv[5]);
        int outfile_vector_size=outfile_vector.size();
        for(int i=0; i < outfile_vector_size; i++) {
             outfile << outfile_vector[i] <<std::endl;
        }
    }
    // Close the the writing file
    outfile.close();
}