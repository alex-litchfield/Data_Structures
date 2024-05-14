#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "movies.h"
#include "hashtable.h"
using String = std::string;
/*loads the data from the files and stores them in the proper containers it loads the actors and numbers into a vector of pairs.
it loads all the data from the movie file into a movie object and hashes each part of the movie and uses that as a key for the hash table.
This returns a vector of movies to be used as a wild card input*/
std::vector<Movies> loadingTheData(const String& actor_file,const String& movie_file, Hashtable& mainTable, std::vector<std::pair<String,String> >& actor_num ){
    std::ifstream actors(actor_file);
    String line;
    std::vector<Movies> list_of_movies;
    while(std::getline(actors,line)){
        std::stringstream linestream(line);
        String actor, num;
        linestream>>num>>actor;
        actor_num.push_back(std::make_pair(num,actor) );
    }
    std::ifstream movies(movie_file);
    int counter=0;
    Movies movie;
    std::vector<String> entire_movie; 
    std::vector<String> actor_n;
    std::vector<String> role;
    std::vector<String> genre;
    String genre_S="";
    String role_s="";
    String actor_s="";
    String allParam="";
    while(std::getline(movies,line)){
        if(counter == 6){
            counter =0;
            movie.setTitle(entire_movie[0]);
            movie.setYear(entire_movie[1]);
            movie.setRuntime(entire_movie[2]);
            movie.setGenre(genre);
            movie.setActor_n(actor_n);
            movie.setRole(role);
            list_of_movies.push_back(movie);

            //insert by different values title year and runtime, genre,role, and actor respectivly
            // mainTable.insert(movie,hash(allParam));
            mainTable.insert(movie,hash(entire_movie[0]));
            mainTable.insert(movie,hash(entire_movie[1]));
            mainTable.insert(movie,hash(entire_movie[2]));
            mainTable.insert(movie,hash(genre_S));
            mainTable.insert(movie,hash(role_s));
            mainTable.insert(movie,hash(actor_s));

            //reset everything
            entire_movie.clear();
            actor_n.clear();
            role.clear();
            genre.clear();
            genre_S.clear();
            role_s.clear();
            actor_s.clear();
            allParam.clear();
        }
        allParam+=line;
        std::stringstream linestream(line);
        String s1;
        linestream>>s1;
        entire_movie.push_back(s1);
        if(counter ==3){
            int i= std::stoi(s1);
            for(int j=0; j<=i; j++){
                String s2;
                linestream>>s2;
                genre.push_back(s2);
                genre_S+=s2;
            }
        
        }
        if(counter == 4){
             int i= std::stoi(s1);
            for(int j=0; j<=i; j++){
                String s2;
                linestream>>s2;
                actor_n.push_back(s2);
                actor_s+=s2;
            }
        }
        if(counter==5){
            int i= std::stoi(s1);
            for(int j=0; j<=i; j++){
                String s2;
                linestream>>s2;
                role.push_back(s2);
                role_s+=s2;
            }
        }
        counter++;
    }
    movie.setTitle(entire_movie[0]);
    movie.setYear(entire_movie[1]);
    movie.setRuntime(entire_movie[2]);
    movie.setGenre(genre);
    movie.setActor_n(actor_n);
    movie.setRole(role);
    list_of_movies.push_back(movie);
    //insert by different values title year and runtime, genre,role, and actor respectivly
    mainTable.insert(movie,hash(entire_movie[0]));
    mainTable.insert(movie,hash(entire_movie[1]));
    mainTable.insert(movie,hash(entire_movie[2]));
    mainTable.insert(movie,hash(genre_S));
    mainTable.insert(movie,hash(role_s));
    mainTable.insert(movie,hash(actor_s));
    mainTable.insert(movie,hash(allParam));
    return list_of_movies;
}
int main(){
    String s1,actor_file, movie_file;
    Hashtable mainTable=Hashtable();
    std::vector<unsigned int> search_keys;
    std::vector<std::pair<String,String> > actor_keys;
    std::vector<Movies>results;
    std::vector<Movies>movie_objects;
    while(std::cin.good()){
        std::cin>>s1;
        if(s1=="table_size"){
            String s2;
            std::cin>>s2;
            int table_size=std::stoi(s2);
            mainTable= Hashtable(table_size);
        }
        if(s1=="occupancy"){
            String s2;
            std::cin>>s2;
            double occupancy= std::stod(s2);
            mainTable.setOccupancy(occupancy);
        }
        if(s1=="movies"){
            std::cin>>movie_file;

        }
        if(s1=="actors"){
            std::cin>>actor_file;
            movie_objects=loadingTheData(actor_file,movie_file,mainTable,actor_keys);
        }
        //read the search query
        if(s1=="query"){
            String s2;
            int counter=0;
            while(counter!=5){
                std::cin>>s2;
                if(s2!="0"||s2!="?"){
                    if(counter==3||counter ==4 || counter==5){
                        for(int i=0;i<std::stoi(s2); i++){
                            String s3;
                            std::cin>>s3;
                            search_keys.push_back(hash(s3));
                        }
                    }else{
                        search_keys.push_back(hash(s2));
                    }
                
                    
                 }else if(s2=="?"){
                    if(counter==0){
                         for(int i=0; i<movie_objects.size(); i++){
                             search_keys.push_back(hash(movie_objects[i].getTitle()));
                         }
                     }else if(counter==1){
                         for(int i=0; i<movie_objects.size(); i++){
                             search_keys.push_back(hash(movie_objects[i].getYear()));
                         }
                     }else if(counter==2){
                         for(int i=0; i<movie_objects.size(); i++){
                             search_keys.push_back(hash(movie_objects[i].getRuntime()));
                         }
                     }
                 }else if(s2=="0"){
                     if(counter==3){
                     for(int i=0;i<movie_objects.size(); i++){
                             for(int j=0; j<movie_objects[i].getGenre().size(); j++){
                                 search_keys.push_back(hash(movie_objects[i].getGenre()[j]));
                             }
                         }
                     }else if(counter==4){
                         for(int i=0;i<movie_objects.size(); i++){
                             for(int j=0; j<movie_objects[i].getActor().size(); j++){
                                 search_keys.push_back(hash(movie_objects[i].getActor()[j]));
                             }
                         }
                     }else if(counter ==5){
                         for(int i=0;i<movie_objects.size(); i++){
                             for(int j=0; j<movie_objects[i].getRole().size(); j++){
                                 search_keys.push_back(hash(movie_objects[i].getRole()[j]));
                             }
                         }
                     }
                }
                counter++;
            }
            
            results=mainTable.find(search_keys);
            //remvoes mataches 
            if(results.size()!=0)
                results.erase(std::unique(results.begin(),results.end()));
        }if(s1=="quit"){
            break;
        }
    }
    printTable(mainTable,results,actor_keys);

    
    
}