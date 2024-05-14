#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();


template <class T>
void list_sort(std::list<T> &lst, std::ostream &ostr, int &output_count) {
  // use the list sort algorithm
  lst.sort();
  typename std::list<T>::iterator it;
  output_count=0;
  for (it = lst.begin(); it != lst.end(); ++it) {
    output_count++;
    ostr << *it << "\n";
  }
}


template <class T>
void list_remove_duplicates(const std::list<T> &lst, std::ostream &ostr, int &output_count) {
  // don't reorder the elements, just do all pairwise comparisons
  output_count = 0;
  typename std::list<T>::const_iterator it1 = lst.begin();
  for (; it1 != lst.end(); ++it1) {
    bool dup = false;
    typename std::list<T>::const_iterator it2;
    for (it2 = lst.begin(); it2 != it1; ++it2) {
      if (*it1 == *it2) {
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << *it1 << "\n";
      output_count++;
    }
  }
}


template <class T>
void list_mode(std::list<T> &lst, std::ostream &ostr, int &output_count) {
  // use the list sort algorithm
  lst.sort();
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two iterators into the structure
  typename std::list<T>::iterator current = lst.begin();
  ++current;
  typename std::list<T>::iterator previous = lst.begin();
  for (; current != lst.end(); ++current, ++previous) {
    if (*current == *previous) {
      // if they are the same element increment the count
      current_count++;
    } else if (current_count >= mode_count) {
      // found a new mode!
      mode = *previous;
      mode_count = current_count;
      current_count = 1;
    } else {
      current_count = 1;
    }
  }
  if (current_count >= mode_count) {
    // last entry is a new mode!
    mode = *previous;
    mode_count = current_count;
  }
  // save the mode to the output vector
  output_count = 1;
  ostr << mode << "\n";
}


// note: closest_pair is only available for integer data (not string data)
void list_closest_pair(std::list<int> &lst, std::ostream &ostr, int &output_count) {
  assert (lst.size() >= 2);
  // use the list sort algorithm
  lst.sort();
  typename std::list<int>::iterator it1;
  output_count = 2;
  int best;
  int best_index = -1;
  // the two elements with closest value must be next to each other in sorted order
  typename std::list<int>::iterator it2 = lst.end();
  --it2;
  int counter=0;
  for (it1 = lst.begin(); it1 != it2; ++it1) {
    counter++;
    int diff = *(++it1)-*(--it1);
    if (best_index == -1 || diff < best) {
      best = diff;
      best_index = counter;
    }
  }
  // print the two elements
  int best_index_counter=0;
  for (it1 = lst.begin(); it1 != lst.end(); ++it1) {
    best_index_counter++;
    if (best_index_counter==best_index || best_index_counter==best_index+1 ) {
      ostr << *it1 << "\n";
    }
  }
}


template <class T>
void list_first_sorted(std::list<T> &lst, std::ostream &ostr, int &output_count, 
                       int optional_arg) {
  typename std::list<T>::iterator it;
  assert (optional_arg >= 1);
  assert (lst.size() >= optional_arg);
  // use the list sort algorithm
  lst.sort();
  output_count = optional_arg;
  int counter=0;
  for (it = lst.begin(); it != lst.end(); ++it) {
    counter++;
    ostr << *it << "\n";
    if (counter==optional_arg) {
      break;
    }
  }
}


// note: longest_substring is only available for string data (not integer data)
void list_longest_substring(std::list<std::string> &lst, std::ostream &ostr,
                            int &output_count) {
  output_count=1;
  std::string longest_substring = "";
  typename std::list<std::string>::iterator it1 = lst.begin();
  ++it1;
  for(; it1 != lst.end(); ++it1) {
    for(int j = 0; j< (*it1).length(); j++) {
      for(int k = 0; k < (*it1).length(); k++) {
        typename std::list<std::string>::iterator it2;
        for(it2 = lst.begin(); it2 != it1; ++it2) {
          if( (*it2).find((*it1).substr(k, j+1)) != -1) {
            if( (*it1).substr(k, j+1).length() > longest_substring.length()) {
              longest_substring = (*it1).substr(k, j+1);
            }
          }
        }
      }
    }
  }
  ostr << longest_substring << "\n";
}


void list_test(const std::string &operation, const std::string &type,
                std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    // load the data into a list of strings
    std::list<std::string> lst;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      lst.push_back(s);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  else {
    assert (type == "integer");
    // load the data into a list of integers
    std::list<int> lst;
    int v;
    input_count = 0;
    while (istr >> v) {
      lst.push_back(v);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
