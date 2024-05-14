// File:    Board.cpp
// Purpose: Implementation file for the Board class.

#include "Board.h" // allows access to the header file

//Constructed from
Board::Board(std::string a_p1_token, std::string a_p2_token, std::string a_blank_token) {
    p1_token=a_p1_token;
    p2_token=a_p2_token;
    blank_token=a_blank_token;
    total_rows=5;
    total_cols=4;
    m_data=new std::string* [total_cols]; 
    col_data=new int [total_cols];
    for (int i = 0; i < total_cols; i++) {
        m_data[i] = NULL;
        col_data[i]=0;
    }
}

//Destructor
Board::~Board() {
    for (int i=0; i<total_cols; i++) {
        delete [] m_data[i];
    }
    delete [] m_data;
    delete [] col_data;
}

//Copy Constructor
Board::Board(const Board &old_obj) {
    copy(old_obj);
}

// Copies the board into another board
void Board::copy(const Board& b) {
    this->row = b.row;
    this->col = b.col;
    this->total_rows = b.total_rows;
    this->total_cols = b.total_cols;
    this->p1_token = b.p1_token;
    this->p2_token = b.p2_token;
    this->blank_token = b.blank_token;
    this->player = b.player;
    //copying m_data and col data
    this->col_data = new int [this->total_cols];
    for(int i=0; i < this->total_cols;i++) {
        this -> col_data[i] = b.col_data[i];
    }
    this->m_data = new std::string* [this->total_cols];
    for(int i=0; i < this->total_cols; i++) {
        this->m_data[i] = new std::string [this->col_data[i]];
        for(int j=0; j < this->col_data[i]; j++) {
            this->m_data[i][j] = b.m_data[i][j];
        }
    }
}
//Asignment Operator
Board& Board::operator= (const Board& b) {
    if (this != &b) {
        for (int i=0; i<total_cols; i++) {
            delete [] m_data[i];
        }
        delete [] m_data;
        delete [] col_data;
        this -> copy(b);
    }
    return *this;
}
// ACCESSORS
int Board::numRows() const {
    return total_rows; 
}

int Board::numColumns() const {
    return total_cols;
}

std::string Board::getBlankToken() const {
    return blank_token;
}

std::string Board::getP1Token() const {
    return p1_token;
}

std::string Board::getP2Token() const {
    return p2_token;
}

int Board::numTokensInRow(int row) const {
    if (0<=row && row<total_rows) {
        int tokens_in_row=0;
        for (int i=0; i<total_cols; i++) {
            if ((*this).numTokensInColumn(i)>0 && (*this).numTokensInColumn(i)>=row-1) {
                tokens_in_row=tokens_in_row+1;
            }
        }
        return tokens_in_row;
    }
    else {
        return -1;
    }
}

int Board::numTokensInColumn(int col) const {
    if (0<=col && col<total_cols) {
        return col_data[col];
    }
    else {
        return -1;
    }
}

std::string** Board::getBoard() const{
    return m_data;
}

//MODIFIERS
std::string Board::insert(int col, bool player) { //inserts a players token into the board
    //determining player
    std::string token;
    if (player==true) {//player 1
        token=p1_token;
    }
    else if (player==false) { //player 2
        token=p2_token;
    }
    //adding tokens
    int current_row=0;
    if (col<total_cols) { //adds token to a currently existing column
        if (m_data[col]==NULL) {
            m_data[col] = new std::string[1]; //creates an array for the col
            m_data[col][0]=token;
            current_row=0;
            col_data[col]=1;
        }
        else { //if total rows increases by 1 OR board does not increase
            if ( ((*this).numTokensInColumn(col)+1)>total_rows) {
                total_rows=total_rows+1;
            }
            std::string *temp;
            temp = new std::string[(*this).numTokensInColumn(col)+1];
            for (int i=0; i<(*this).numTokensInColumn(col); i++) { //copies contents to temp
                temp[i]=m_data[col][i];
            }
            temp[(*this).numTokensInColumn(col)]=token;
            current_row=(*this).numTokensInColumn(col);
            delete [] m_data[col]; 
            m_data[col] = temp;
            col_data[col]=col_data[col]+1;
        }
    }
    else { //adds a column to the right
        std::string** temp = new std::string* [col+1];
        int* temp_col_data=new int [col+1];
        for (int i=0; i<(col+1); i++) { //copies contents to temp
            if (i<total_cols) {
                temp[i]=m_data[i];
                temp_col_data[i]=col_data[i];
            }
            else if (i==col) {
                temp[i] = new std::string[1]; //creates an array for the col
                temp[i][0]=token; //adds new token
                current_row=0;
                temp_col_data[i]=1;
            }
            else if (i<col) {
                temp[i]=NULL;
                temp_col_data[i]=0;
            }
        }
        delete [] m_data;
        m_data=temp;
        delete [] col_data;
        col_data=temp_col_data;
        total_cols=col+1;
    }
    //if no one wins return the blank token, and if someone does win return their token
    //win conditions
    std::string winner = blank_token;
    //check for vertical wins
    if (current_row>=3 && m_data[col][current_row]==m_data[col][current_row-1]) {
        if (m_data[col][current_row]==m_data[col][current_row-2] && m_data[col][current_row]==m_data[col][current_row-3]) {
            winner=m_data[col][current_row];
            return token;
        }
    }
    //check for horizontal wins
    int vertical_tokens = 1;
    bool consecutive_token_right = true;
    bool consecutive_token_left = true;
    int horizontal_tokens = 1;
    int i = col;
    int j = col_data[col]-1;
    //for win to right of token just place
    while(consecutive_token_right) {
        i++;
        if(i<total_cols && j<col_data[i] && m_data[i][j]==token) {
            vertical_tokens++;
        } 
        else {
            consecutive_token_right = false;
        }
    }
    //check for win to left of token just placed
    i = col;
    j = col_data[col]-1;
    while(consecutive_token_left) {
        i--;
        if(i>=0 && j<col_data[i] && m_data[i][j]==token) {
            horizontal_tokens++;
        } else {
            consecutive_token_left = false;
        }
    }
    //return the winner of the game
    if(vertical_tokens >= 4 || horizontal_tokens >= 4) {
        return token;
    }
    return blank_token;
}

void Board::clear() {//clears the board of all previous tokens/size increases
    for (int i=0; i<total_cols; i++ ) {
        delete [] m_data[i];
    }
    delete [] m_data;
    delete [] col_data;
    total_rows=5;
    total_cols=4;

    m_data=new std::string* [total_cols]; 
    col_data=new int [total_cols];
    for (int i = 0; i < total_cols; i++) {
        m_data[i] = NULL;
        col_data[i]=0;
    }
}

//Prints the board through the ostream when called
std::ostream& operator<< (std::ostream& ostr, const Board& b) {
    std::string board_string;
    for (int i=b.numRows()-1; i>=0; i--) { //rows
        for (int j = 0; j < b.numColumns(); j++) { //cols
            if (b.getBoard()[j]==NULL ) {
                board_string=board_string+b.getBlankToken();
            }
            else {
                if (i<b.numTokensInColumn(j) && (b.getBoard()[j][i]==b.getP1Token() || b.getBoard()[j][i]==b.getP2Token()) ) {
                    board_string=board_string+b.getBoard()[j][i];
                }
                else  {
                    board_string=board_string+b.getBlankToken();
                }
                
            }
            if (j<(b.numColumns()-1) ) { //not yet end of row
                board_string=board_string+" ";
            }
            else {//end of row
                board_string=board_string+"\n";
            }
        }
    }
    ostr << board_string;
    return ostr;
}