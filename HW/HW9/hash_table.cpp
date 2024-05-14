#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "hash_table.h"
#include "movies.h"

Hash_table::Hash_table() {
    m_table=100; //set to 100 when blank
    m_size=0; 
}
Hash_table::Hash_table(unsigned int init_size){
    m_table=init_size;
    m_size=0; 
}
unsigned int Hash_table::size() const {
    return m_size;
}
void Hash_table::setOccupancy(double level) {
    maxLevel=level;
}
void Hash_table::resize(unsigned int newSize){
    std::vector<std::pair<unsigned long, Movies> > newTable(newSize);
    int size=0;
    for(unsigned int i=0; i<m_table.size(); i++){
        int index= (m_table[i].first)%newTable.size();
        if(newTable[index].second==Movies()){
            newTable[index]= m_table[i];
            size++;
        }else{
            while(newTable[index].second!=Movies()){
                index++;
            }
            newTable[index]=m_table[i];
            size++;
        }
    }
    m_table=newTable;
    m_size=size;
}
//read line by line from file and hash that and then call this 
bool Hash_table::insert(const Movies& value, const unsigned long& hashed_key) {
    bool did_insert=false;
    float occupancy=number_of_entries/m_table.size();
    if(occupancy>= maxLevel){
        this->resize(2*m_table.size()+1);
    }
    unsigned int index = hashed_key%m_table.size();
    std::list<std::string> movies;
    if(m_table[index].second==movies) {
        m_table[index]= std::make_pair(hashed_key,value);
        m_size++;
    }
    else{
        while(m_table[index].second!=movies){
            index++;
        }
        m_table[index]=std::make_pair(hashed_key,value);
        m_size++;
    }
    did_insert=true;
    return did_insert;
}
std::vector<std::list<std::string>> Hash_table::find(const std::vector<unsigned int>& keys) {
    std::vector<std::list<std::string>> found;
    for(int i=0; i<keys.size(); i++){
        int index= keys[i]%m_table.size()+2;
        if(m_table[index].first==keys[i]) {
            std::list<std::string> found_movie = m_table[index].second;
            Movies found_movie= m_table[index].second;
            found.push_back(found_movie);
        }
    }
    return found;
}
//hash function from djb2 by Dan Bernstein. https://www.programmingalgorithms.com/algorithm/djb-hash?lang=C%2B%2B
unsigned long hash(std::string key) {
    unsigned int len = key.length();
    unsigned long hash = 5381;
    unsigned int i = 0;
    for (i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + (key[i]);
    }
    return hash;
}
}
//Prints the table
void printTable(const Hash_table& table,  std::vector<Movies>& matches, std::vector<std::pair<std::string,std::string>>& actor_keys) {
    std::cout<<"Printing "<<matches.size()<<" result(s):"<<std::endl;
    for(int i=0; i<matches.size();i++){
        Movies temp=matches[i];
        std::cout<<temp.getTitle()<<std::endl;
        std::cout<<temp.getYear()<<std::endl;
        std::cout<<temp.getRuntime()<<std::endl;
        std::cout<<temp.getGenre().size()<<" ";
        for(int j=0; j<temp.getGenre().size(); j++){
            std::cout<<temp.getGenre()[j]<<"";
        }
        std::cout<<std::endl;
        std::cout<<temp.getActor().size()<<" ";
        for(int j=0; j<temp.getActor().size(); j++){
            for(int k=0; k<actor_keys.size(); k++){
                if(temp.getActor()[j]==actor_keys[k].first){
                    std::cout<<actor_keys[k].second<<" ("<<temp.getRole()[j]<<") ";
                }
                /*else{
                    continue;
                }*/
            }
        }
        std::cout<<std::endl;
    }
}