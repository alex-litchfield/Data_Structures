#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();


template <class T>
void bst_sort(std::map<T,int> &mp, std::ostream &ostr, int &output_count, std::istream &istr, int &input_count) {
  //input values
  input_count = 0;
  output_count = 0;
  T input;
  while (istr >> input) {
    mp[input]++;
    input_count++;
  }
  //printing
  typename std::map<T,int>::iterator it;
  for (it = mp.begin(); it != mp.end(); ++it) {
    for (int j = 0; j < (it->second); j++) {
      ostr << it->first << "\n";
      output_count++;
    }
  }
}

template <class T>
void bst_remove_duplicates(std::map<T,int> &mp, std::ostream &ostr, int &output_count, std::istream &istr, int &input_count) { 
  // don't reorder the elements, just do all pairwise comparisons
  input_count = 0;
  output_count = 0;
  T input;
  while (istr >> input) {
    if (mp.find(input) == mp.end()) {
      ostr << input << "\n";
      output_count++;
    }
    mp[input]++;
    input_count++;
  }
}


template <class T>
void bst_mode(std::map<T,int> &mp, std::ostream &ostr, int &output_count, std::istream &istr, int &input_count) {
  //input values
  input_count = 0;
  output_count = 0;
  T input;
  while (istr >> input) {
    mp[input]++;
    input_count++;
  }
  //finding the mode
  T mode;
  int mode_frequency = 0;
  typename std::map<T,int>::iterator it;
  output_count = 1;
  for (it = mp.begin(); it != mp.end(); ++it) {
    if (it->second > mode_frequency) {
      mode_frequency = it->second;
      mode = it->first;
    }
  }
  ostr << mode << "\n";
}


// note: closest_pair is only available for integer data (not string data)
void bst_closest_pair(std::set<int> &st, std::ostream &ostr, int &output_count, std::istream &istr, int &input_count) {
  //input values
  input_count = 0;
  int input;
  while (istr >> input) {
    st.insert(input);
    input_count++;
  }
  //finding closest pair
  typename std::set<int>::iterator it1;
  assert (st.size() >= 2);
  output_count = 2;
  int best;
  int best_index = -1;
  // the two elements with closest value must be next to each other in sorted order
  typename std::set<int>::iterator it2 = st.end();
  --it2;
  int counter=0;
  for (it1 = st.begin(); it1 != it2; ++it1) {
    counter++;
    int diff = *(++it1)-*(--it1);
    if (best_index == -1 || diff < best) {
      best = diff;
      best_index = counter;
    }
  }
  // print the two elements
  int best_index_counter=0;
  for (it1 = st.begin(); it1 != st.end(); ++it1) {
    best_index_counter++;
    if (best_index_counter==best_index || best_index_counter==best_index+1 ) {
      ostr << *it1 << "\n";
    }
  }
}


template <class T>
void bst_first_sorted(std::map<T,int> &mp, std::ostream &ostr, int &output_count, int optional_arg, std::istream &istr, int &input_count) {
  //input values
  assert (optional_arg >= 1);
  input_count = 0;
  output_count = optional_arg;
  T input;
  while (istr >> input) {
    mp[input]++;
    input_count++;
  }
  //finding the requested items
  assert (input_count >= optional_arg);
  int counter=0;
  typename std::map<T,int>::iterator it;
  for (it = mp.begin(); it != mp.end(); ++it) {
    for (int j = 0; j < (it->second); j++ ) {
      if (counter < optional_arg) {
        ostr << it->first << "\n";
        counter++;
      }
    }
  }
}

// note: longest_substring is only available for string data (not integer data)
void bst_longest_substring(std::map<std::string,int> &mp, std::ostream &ostr, int &output_count, std::istream &istr, int &input_count) {
  //For example, if the input contains the words ‘antelope’, ‘buffalo’ and ‘elephant’, the longest substring
  //match is ‘ant’ (found within both ‘antelope’ and ‘elephant’). If there is a tie, you may return any of
  //the longest matching substrings.
  //input values
  output_count=1;
  std::string longest_substring = "";
  input_count = 0;
  std::string input;
  while (istr >> input) {
    mp[input]++;
    input_count++;
  }
  //longest substring
  typename std::map<std::string,int>::iterator it1 = mp.begin();
  ++it1;
  for(; it1 != mp.end(); ++it1) {
    for(int j = 0; j< (it1->first).length(); j++) {
      for(int k = 0; k < (it1->first).length(); k++) {
        typename std::map<std::string,int>::iterator it2;
        for(it2 = mp.begin(); it2 != it1; ++it2) {
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


void bst_test(const std::string &operation, const std::string &type,
                std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    // create map (loading done in operations)
    std::map<std::string,int> mp;
    input_count = 0;
    if      (operation == "sort")              { bst_sort              (mp,ostr,output_count,istr,input_count); }
    else if (operation == "remove_duplicates") { bst_remove_duplicates (mp,ostr,output_count,istr,input_count); }
    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count,istr,input_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg,istr,input_count); }
    else if (operation == "longest_substring") { bst_longest_substring (mp,ostr,output_count,istr,input_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  } 
  else {
    assert (type == "integer");
    // create map and set(loading done in operations)
    std::map<int,int> mp;
    std::set<int> st;
    input_count=0;
    if      (operation == "sort")              { bst_sort              (mp,ostr,output_count,istr,input_count); }
    else if (operation == "remove_duplicates") { bst_remove_duplicates (mp,ostr,output_count,istr,input_count); }
    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count,istr,input_count); }
    else if (operation == "closest_pair")      { bst_closest_pair      (st,ostr,output_count,istr,input_count); }
    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg,istr,input_count); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
