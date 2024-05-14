#ifndef hash_table_h_
#define hash_table_h_
#include "movies.h"

class Hash_table {
public:
    Hash_table();
    Hash_table(unsigned int init_size);
    unsigned int size() const;
    void setOccupancy(double level);
    void resize(unsigned int newSize);
    //read line by line from file and hash that and then call this 
    bool insert(const Movies& value, const unsigned long& hashed_key);
    std::vector<std::list<std::string>> find(const std::vector<unsigned int>& keys);
private:
    // HASH SET REPRESENTATION
    std::string QUERY;
    std::vector<std::pair<std::string, std::list<std::string> > > m_table; //actual table
    unsigned int m_size; // number of keys
};
//hash function from djb2 by Dan Bernstein. https://www.programmingalgorithms.com/algorithm/djb-hash?lang=C%2B%2B
unsigned long hash(std::string key);
void printTable(const Hash_table& table,  std::vector<std::list<std::string>>& matches, std::vector<std::pair<std::string,std::string>>& actor_keys);
#endif