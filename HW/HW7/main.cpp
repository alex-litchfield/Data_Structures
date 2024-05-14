// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>


// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef std::map<std::string, std::map<std::string, int> > MY_MAP2;
typedef std::map<std::string, std::map<std::string, std::map<std::string, int> > > MY_MAP3;



// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP3 &data3, MY_MAP2 &data2, const std::string &filename, int window, const std::string &parse_method, std::map<std::string, int> &word_count) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }
  
  bool first_word=true;
  bool second_word=true;
  std::string word;
  std::string prev_word;
  std::string prev_prev_word; //word before prev_word
  if (window==2) {
    while (ReadNextWord(istr,word)) {
      // skip the quotation marks (not used for this part)
      if (word == "\"") continue;
      if (first_word==true) {
        first_word=false;
        prev_word=word;
        ++word_count[word];  
      }
      else {
        ++data2[prev_word][word];
        ++word_count[word];
        prev_word=word;
      }
    }
  }
  else if (window==3) {
    while (ReadNextWord(istr,word)) {
      // skip the quotation marks (not used for this part)
      if (word == "\"") continue;
      if (first_word==true) {
        first_word=false;
        prev_word=word;
        ++word_count[word];  
      }
      else if (second_word==true) {
        second_word=false;
        prev_prev_word=prev_word;
        prev_word=word;
        ++word_count[word];  

      }
      else {
        ++data3[prev_prev_word][prev_word][word];
        ++word_count[word];
        prev_prev_word=prev_word;
        prev_word=word;
      }
    }
  }
}



int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP2 data2;
  MY_MAP3 data3;

  // Parse each command
  int window;
  std::string command;
  std::map<std::string, int> word_count;   
  std::srand(std::time(0)); // use current time as seed for random generator
  while (std::cin >> command) {
    // load the sample text file
    if (command == "load") {
      std::string filename;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;
      LoadSampleText(data3, data2, filename, window, parse_method, word_count);
      std::cout << "Loaded " << filename << " with window = " << window << " and parse method = " << parse_method << std::endl << std::endl;
    } 
    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      if (sentence.size()==1 && window==2) {
        std::map<std::string, int>::const_iterator it;
        std::cout << sentence[0] << " (" << word_count[sentence[0]] << ")" << std::endl;
        for (it = data2[sentence[0]].begin(); it != data2[sentence[0]].end(); ++it) {
          std::cout << sentence[0] << " " << it->first << " (" << it->second << ")" << std::endl;
        }
        std::cout << std::endl;
      }
      else if (sentence.size()==1 && window==3) {
        std::map<std::string, std::map<std::string, int> >::const_iterator it;
        std::cout << sentence[0] << " (" << word_count[sentence[0]] << ")" << std::endl;
        for (it = data3[sentence[0]].begin(); it != data3[sentence[0]].end(); ++it) {
          std::map<std::string, int>::const_iterator it2;
          int counter=0;
          for (it2 = data3[sentence[0]][it->first].begin(); it2 != data3[sentence[0]][it->first].end(); ++it2) {
            counter=counter+it2->second;
          }
          std::cout << sentence[0] << " " << it->first << " (" << counter << ")" << std::endl;
        }
        std::cout << std::endl;
      }
      else if (sentence.size()>1 && window==3){
        for (int i=0; i<int(sentence.size()); i++) {
          std::cout << sentence[i] << " ";
        }
        int counter=0;
        std::map<std::string, int>::const_iterator it;
        for (it = data3[sentence[0]][sentence[1]].begin(); it != data3[sentence[0]][sentence[1]].end(); ++it) {
          counter=counter+it->second;
        }
        std::cout << "(" << counter << ")" << std::endl;
        for (it = data3[sentence[0]][sentence[1]].begin(); it != data3[sentence[0]][sentence[1]].end(); ++it) {
          std::cout << sentence[0] << " " << sentence[1] << " " << it->first;
          std::cout << " (" << it->second << ")" << std::endl; 
        }
        std::cout << std::endl;
      }
    }

    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
	      random_flag = true;
      } 
      else {
	      assert (selection_method == "most_common");
	      random_flag = false;
      }
      //random, one word, window 2
      if (random_flag==true && sentence.size()==1 && window==2) {
        std::cout << sentence[0];
        std::string new_word=sentence[0];
        for (int i=0; i<length; i++) {
          std::map<std::string, int>::const_iterator it = data2[new_word].begin();
          int random_variable = std::rand() % (data2.find(new_word))->second.size();
          for (int j=0; j<random_variable; j++) {
            ++it;
          }
          new_word = it->first;
          std::cout << " " << new_word;
        }
        std::cout << std::endl;
      }
      //most_common, one word, window 2
      else if (random_flag==false && sentence.size()==1 && window==2) {
        std::cout << sentence[0];
        std::string new_word=sentence[0];
        for (int i=0; i<length; i++) {
          std::map<std::string, int>::const_iterator it;
          std::vector<std::string> possible_words;
          int count=0;
          for (it = data2[new_word].begin(); it != data2[new_word].end(); ++it) {
            if (it->second>count) {
              count=it->second;
              possible_words.clear();
              possible_words.push_back(it->first);
            }
            else if (it->second==count) {
              possible_words.push_back(it->first);
            }
          }
          sort(possible_words.begin(), possible_words.end());
          new_word=possible_words[0];
          std::cout << " " << new_word;

        }
        std::cout << std::endl;
      }
      //random, window 3
      else if (random_flag==true && window==3) {
        std::cout << sentence[0];
        std::string new_word=sentence[0];
        std::string old_word;
        //when only one word is provided
        if (sentence.size()==1) {
          std::map<std::string, std::map<std::string, int>>::const_iterator it = data3[new_word].begin();
          int random_variable = std::rand() % (data3.find(new_word))->second.size();
          for (int j=0; j<random_variable; j++) {
            ++it;
          }
          old_word=new_word;
          new_word=it->first;
          std::cout << " " << new_word;
        }
        // when more than one word is provided
        else if (sentence.size()>1) {
          old_word=new_word;
          new_word=sentence[1];
          std::cout << " " << new_word;
          length++;
        }
        for (int i=0; i<(length-1); i++) {
          std::map<std::string, int>::const_iterator it = data3[old_word][new_word].begin();
          int random_variable = std::rand() % (data3[old_word].find(new_word))->second.size();
          for (int j=0; j<random_variable; j++) {
            ++it;
          }
          old_word=new_word;
          new_word=it->first;
          std::cout << " " << new_word;
        }
        std::cout << std::endl;
      }
      //most_common, window 3
      else if (random_flag==false && window==3) {
        std::cout << sentence[0];
        std::string new_word=sentence[0];
        std::string old_word;
        std::vector<std::string> possible_words1;
        if (sentence.size()==1) { // if one word is used
          std::map<std::string, std::map<std::string, int>>::const_iterator it;
          int total_count=0;
          for (it = data3[new_word].begin(); it != data3[new_word].end(); ++it) {
            std::map<std::string, int>::const_iterator it2;
            int count=0;
            for (it2 = data3[new_word][it->first].begin(); it2 != data3[new_word][it->first].end(); ++it2) {
              count=count+it2->second;
            }
            if (count>total_count) {
              total_count=count;
              possible_words1.clear();
              possible_words1.push_back(it->first);
            }
          }
          sort(possible_words1.begin(), possible_words1.end());
          old_word=new_word;
          new_word=possible_words1[0];
          std::cout << " " << new_word;
          possible_words1.clear();
        }
        //if more then one word given
        else if (sentence.size()>1){
          old_word=new_word;
          new_word=sentence[1];
          std::cout << " " << new_word;
          length++;
        }
        for (int i=0; i<(length-1); i++) {
          int count2=0;
          std::map<std::string, int>::const_iterator it3;
          for (it3 = data3[old_word][new_word].begin(); it3 != data3[old_word][new_word].end(); ++it3) {
            if (it3->second>count2) {
              count2=it3->second;
              possible_words1.clear();
              possible_words1.push_back(it3->first);
            }
          }
          sort(possible_words1.begin(), possible_words1.end());
          old_word=new_word;
          new_word=possible_words1[0];
          std::cout << " " << new_word;
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;

    } 
    else if (command == "quit") {
      break;
    } 
    else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
