#include <iostream>
#include <map>
#include <string>

int main() {
  int s;
  std::map<int, int> counters; // store each word and an associated counter

  // read the input, keeping track of each word and how often we see it
  while (std::cin >> s) {
    ++counters[s];
  }

  // write the words and associated counts
  std::map<int, int>::const_iterator it;
  int max=0;
  for (it = counters.begin(); it != counters.end(); ++it) {
    if (it->second>max) {
      max=it->second;
    }
  }

  for (it = counters.begin(); it != counters.end(); ++it) {
    if (it->second==max) {
      std::cout << it->first << "\t" << it->second << std::endl;
    }
  }
  return 0;
}