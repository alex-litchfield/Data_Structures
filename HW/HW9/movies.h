#ifndef movies_h_
#define movies_h_

class Movies {
public:
//list for a movie goes as follows: title, year, runtime, genre, actor_n, role
    Movies();
    void setTitle(std::string title);
    void setYear(std::string year);
    void setRuntime(std::string runtime);
    void setGenre(std::vector<std::string> genre);
    void setActors(std::vector<std::string> actors);
    void setRole(std::vector<std::string> role);
    std::string getTitle();
    std::string getYear();
    std::string getRuntime();
    std::vector<std::string> getGenre();
    std::vector<std::string> getActors();
    std::vector<std::string> getRole();
private:
    //REPRESENTATION
    std::string title_;
    std::string year_;
    std::string runtime_;
    std::vector<std::string> genre_;
    std::vector<std::string> actors_;
    std::vector<std::string> role_;
};
#endif