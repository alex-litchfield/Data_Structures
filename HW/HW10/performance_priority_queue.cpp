#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();


template <class T>
void priority_queue_sort(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq,
                         std::ostream &ostr, int &output_count) {
  //just prints the queue
  output_count = pq.size();
  while (!pq.empty()) {
    ostr << pq.top() << "\n";
    pq.pop();
  }
}


template <class T>
void priority_queue_mode(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq,
                         std::ostream &ostr, int &output_count) {
  //finds mode by going through list
  output_count = 1;
  T previous;
  T top;
  int top_count = 0;
  T mode;
  int mode_count = 0;;
  while (!pq.empty()) {
    top = pq.top();
    if (top == previous) {
      top_count++;
    }
    else {
      top_count=1;
    }
    if (top_count >= mode_count) {
      mode = top;
      mode_count = top_count;
    }
    previous = top;
    pq.pop();
  }
  ostr << mode << "\n";
}


// note: closest_pair is only available for integer data (not string data)
void priority_queue_closest_pair(std::priority_queue<int,std::vector<int>, std::greater<int> > &pq,
                                 std::ostream &ostr, int &output_count) {
  assert (pq.size() >= 2);
  output_count = 2;
  int bigger_num, smaller_num, previous, top, best;
  int diff = 0;
  int counter = 0;
  //goes through queue and compares difference with previous values.
  while (!pq.empty()) {
    top = pq.top();
    if (counter>0) {
      diff = top-previous;
      if (counter == 1 || diff <= best) {
        best = diff;
        smaller_num = previous;
        bigger_num = top;
      }
    }
    previous = top;
    counter++;
    pq.pop();
  }
  ostr << smaller_num << "\n";
  ostr << bigger_num << "\n";
}


template <class T>
void priority_queue_first_sorted(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq,
                                 std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)pq.size() >= optional_arg);
  //only prints the first (optional argument) number of items
  output_count = optional_arg;
  for (int i = 0; i < output_count; i++) {
    ostr << pq.top() << "\n";
    pq.pop();
  }
}


void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {
  if (type == "string") {
    // load the data into into a priority queue
    std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      pq.push(s);
      input_count++;
    }

    if      (operation == "sort")              { priority_queue_sort         (pq,ostr,output_count); }
    // "remove duplicates" not available for priority queue
    else if (operation == "mode")              { priority_queue_mode         (pq,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { priority_queue_first_sorted (pq,ostr,output_count,optional_arg); }
    // "longest_substring" not available for priority queue
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers and put that into a priority queue
    std::priority_queue<int,std::vector<int>, std::greater<int> > pq;
    int v;
    input_count = 0;
    while (istr >> v) {
      pq.push(v);
      input_count++;
    }

    if      (operation == "sort")              { priority_queue_sort          (pq,ostr,output_count); }
    // "remove duplicates" not available for priority queue
    else if (operation == "mode")              { priority_queue_mode          (pq,ostr,output_count); }
    else if (operation == "closest_pair")      { priority_queue_closest_pair  (pq,ostr,output_count); }
    else if (operation == "first_sorted")      { priority_queue_first_sorted  (pq,ostr,output_count,optional_arg); }
    // "longest_substring" not available for priority queue
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
