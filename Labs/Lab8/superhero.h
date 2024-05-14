#ifndef _SUPERHERO_H_
#define _SUPERHERO_H_
#include <iostream>

class Superhero
{
private:
    std::string name;
    std::string power;
    std::string realName;
    bool notCorrupt;
    std::string getTrueIdentity() const {return realName;}
public:
    friend class Team;
    Superhero(std::string aname, std::string arealName, std::string apower);
    const std::string getName() const{return name;}
    const std::string getPower() const{return power;}
    void print();
    bool isGood() const{return notCorrupt;}
    //Checks not equal
    bool operator!=(const std::string& check) const{return check != realName;}
    //Checks equal
    bool operator==(const std::string& check) const{return check == realName;}
    bool operator==(const Superhero& check) const;
    void operator-();
    bool operator>(const Superhero& b);
};
std::ostream& operator<< (std::ostream& a, const Superhero& b);
#endif