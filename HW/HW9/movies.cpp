#include <vector>
#include <string>
#include "movies.h"

Movies::Movies() {
    title_="";
    year_="";
    runtime_="";
}
Movies::setTitle(std::string title) {
    title_=title;
}
Movies::setYear(std::string year) {
    year_=year;
}
Movies::setRuntime(std::string runtime) {
    runtime_=runtime;
}
Movies::setGenre(std::vector<std::string> genre) {
    for (int i=0; i<genre.size(); i++) {
        genre_.push_back(genre[i]);
    }
}
Movies::setActors(std::vector<std::string> actors) {
    for (int i=0; i<actors.size(); i++) {
        actors_.push_back(actors[i]);
    }
}
Movies::setRole(std::vector<std::string> role) {
    for (int i=0; i<role.size(); i++) {
        role_.push_back(role[i]);
    }
}
std::string Movies::getTitle() {
    return title_;
}
std::string Movies::getYear() {
    return year_;
}
std::string Movies::getRuntime() {
    return runtime_;
}
std::vector<std::string> Movies::getGenre() {
    return genre_;
}
std::vector<std::string> Movies::getActors() {
    return actors_;
}
std::vector<std::string> Movies::getRole() {
    return role_;
}