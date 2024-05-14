#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "hash_table.h"
#include "movies.h"

std::vector<Movies> loadingTheData(const std::string& actor_file,const std::string& movie_file, Hash_table& mainTable, std::vector<std::pair<std::string,std::string> >& actor_num ){
    std::ifstream actors(actor_file);
    std::string line;
    std::vector<Movies> list_of_movies;
    while(std::getline(actors,line)){
        std::stringstream linestream(line);
        std::string actor, num;
        linestream>>num>>actor;
        actor_num.push_back(std::make_pair(num,actor) );
    }
    std::ifstream movies(movie_file);
    int counter=0;
    Movies movie;
    std::vector<std::string> entire_movie; 
    std::vector<std::string> actor_n;
    std::vector<std::string> role;
    std::vector<std::string> genre;
    std::string genre_S="";
    std::string role_s="";
    std::string actor_s="";
    std::string allParam="";
    while(std::getline(movies,line)){
        if(counter == 6){
            counter =0;
			//list for a movie goes as follows: title, year, runtime, genre, actor_n, role
			movie.setTitle(entire_movie[0]);
            movie.setYear(entire_movie[1]);
            movie.setRuntime(entire_movie[2]);
            movie.setGenre(genre);
            movie.setActors(actor_n);
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
        std::string s1;
        linestream>>s1;
        entire_movie.push_back(s1);
        if(counter ==3){
            int i= std::stoi(s1);
            for(int j=0; j<=i; j++){
                std::string s2;
                linestream>>s2;
                genre.push_back(s2);
                genre_S+=s2;
            }
        
        }
        if(counter == 4){
             int i= std::stoi(s1);
            for(int j=0; j<=i; j++){
                std::string s2;
                linestream>>s2;
                actor_n.push_back(s2);
                actor_s+=s2;
            }
        }
        if(counter==5){
            int i= std::stoi(s1);
            for(int j=0; j<=i; j++){
                std::string s2;
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
    movie.setActors(actor_n);
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

int main() {
	std::string operation;
	std::string actors_file;
	std::string movies_file;
	Hash_table table=Hash_table();
	std::vector<unsigned int> search_keys;
    std::vector<std::pair<std::string,std::string> > actor_keys;
    std::vector<std::list<std::string>> results;
    std::vector<std::list<std::string>> movie_objects;
	while(std::cin.good()) {
		std::cin >> operation;
		if (operation == "movies") {
			std::cin >> movies_file;
			movie_objects=loadingTheData(actors_file,movies_file, table ,actor_keys);
		}
		else if (operation == "actors") {
			std::cin >> actors_file;
		}
		else if (operation == "table_size") {
			std::string size_string;
			std::cin >> size_string;
			int size_int = std::stoi(size);
			table= Hash_table(size_int);
		}
		else if (operation == "occupancy") {
			std::string occupancy_level;
			std::cin >> occupancy_level;
		}
		else if (operation == "query") {
			std::list<std::string> MOVIE_DATA;
			std::string s2;
			for (int i=0; i<5; i++) {
				std::cin >> s2;
				if(s2=="?" && i==0) {
					for(int j=0; j<movie_objects.size(); j++){
						search_keys.push_back(hash(movie_objects[i][0]));
					}
				}
                else if (s2=="?" && i==1) {
					for(int j=0; j<movie_objects.size(); j++){
						search_keys.push_back(hash(movie_objects[i][1]));
					}
                }
				else if(s2=="?" && counter==2) {
					for(int j=0; j<movie_objects.size(); j++){
						search_keys.push_back(hash(movie_objects[i][2]));
					}
				}
				else if(s2=="0" && i==3) {
                    for(int i=0;i<movie_objects.size(); i++){
                        for(int j=0; j<movie_objects[i].getGenre().size(); j++){
                            search_keys.push_back(hash(movie_objects[i].getGenre()[j]));
                        }
                    }
                }
				else if(s2=="0" && i==4) {
                    for(int i=0;i<movie_objects.size(); i++){
                        for(int j=0; j<movie_objects[i].getActor().size(); j++){
                            search_keys.push_back(hash(movie_objects[i].getActor()[j]));
                        }
                    }
                }
				else if(s2=="0" && i==5) {
                    for(int i=0;i<movie_objects.size(); i++){
                        for(int j=0; j<movie_objects[i].getRole().size(); j++){
                            search_keys.push_back(hash(movie_objects[i].getRole()[j]));
                        }
                    }
                }
				else if (i==3 || i==4 || i==5) {
					for(int i=0;i<std::stoi(s2); i++){
						std::string s3;
						std::cin >> s3;
						search_keys.push_back(hash(s3));
                    }
				}
				else {
                    search_keys.push_back(hash(s2));
                }
			}
		}
		else if (operation == "quit") {
			break;
		}
	}
	printTable(mainTable,results,actor_keys);
}