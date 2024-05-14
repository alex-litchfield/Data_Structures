#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();


template <class T>
void hash_table_remove_duplicates(std::unordered_map<T,int> &ht, 
                                  std::ostream &ostr, int &output_count,
                                  std::istream &istr, int &input_count) { 
  // don't reorder the elements, just do all pairwise comparisons
  input_count = 0;
  output_count = 0;
  T input;
  while (istr >> input) {
    if (ht.find(input) == ht.end()) {
      ostr << input << "\n";
      output_count++;
    }
    ht[input]++;
    input_count++;
  }
}


template <class T>
void hash_table_mode(std::unordered_map<T,int> &ht, std::ostream &ostr,
                     int &output_count, std::istream &istr, int &input_count) {
  //input values
  input_count = 0;
  output_count = 0;
  T input;
  while (istr >> input) {
    ht[input]++;
    input_count++;
  }
  //finding the mode
  T mode;
  int mode_frequency = 0;
  typename std::unordered_map<T,int>::iterator it;
  output_count = 1;
  for (it = ht.begin(); it != ht.end(); ++it) {
    if (it->second > mode_frequency) {
      mode_frequency = it->second;
      mode = it->first;
    }
  }
  ostr << mode << "\n";
}


// note: longest_substring is only available for string data (not integer data)
void hash_table_longest_substring(std::unordered_map<std::string,int> &ht,
                                  std::ostream &ostr, int &output_count, 
                                  std::istream &istr, int &input_count) {
  //For example, if the input contains the words ‘antelope’, ‘buffalo’ and ‘elephant’, the longest substring
  //match is ‘ant’ (found within both ‘antelope’ and ‘elephant’). If there is a tie, you may return any of
  //the longest matching substrings.
  //input values
  output_count=1;
  std::string longest_substring = "";
  input_count = 0;
  std::string input;
  while (istr >> input) {
    ht[input]++;
    input_count++;
  }
  //longest substring
  typename std::unordered_map<std::string,int>::iterator it1 = ht.begin();
  ++it1;
  for(; it1 != ht.end(); ++it1) {
    for(int j = 0; j< (it1->first).length(); j++) {
      for(int k = 0; k < (it1->first).length(); k++) {
        typename std::unordered_map<std::string,int>::iterator it2;
        for(it2 = ht.begin(); it2 != it1; ++it2) {
          if( (it2->first).find((it1->first).substr(k, j+1)) != -1) {
            if( (it1->first).substr(k, j+1).length() > longest_substring.length()) {
              longest_substring = (it1->first).substr(k, j+1);
            }
          }
        }
      }
    }
  }
  ostr << longest_substring << "\n";
}


void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    std::unordered_map<std::string,int> ht;
    input_count = 0;
    // "sort" not available for hash table
    if (operation == "remove_duplicates")      { hash_table_remove_duplicates (ht,ostr,output_count,istr, input_count); }
    else if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count,istr, input_count); }
    // "closest_pair" not available for hash table
    // "first_sorted" not available for hash table
    else if (operation == "longest_substring") { hash_table_longest_substring (ht,ostr,output_count,istr, input_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  else {
    assert (type == "integer");
    std::unordered_map<int,int> ht;
    input_count = 0;
    // "sort" not available for hash table
    if (operation == "remove_duplicates")      { hash_table_remove_duplicates (ht,ostr,output_count,istr, input_count); }
    else if (operation == "mode")              { hash_table_mode              (ht,ostr,output_count,istr, input_count); }
    // "closest_pair" not available for hash table
    // "first_sorted" not available for hash table
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
