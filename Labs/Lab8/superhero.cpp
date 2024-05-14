#include "superhero.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

Superhero::Superhero(std::string aname, std::string arealName, std::string apower){
    name = aname;
    realName = arealName;
    power = apower;
    notCorrupt = true;
}
std::ostream& operator<< (std::ostream& a, const Superhero& b){ 
    if(b.isGood() == false){
        return a << "Supervillan" << " " << b.getName() << " " << "has power" << " " << b.getPower() << std::endl;
    }else{
        return a << "Superhero" << " " << b.getName() << " " << "has power" << " " << b.getPower() << std::endl;
    } 
}
void Superhero::operator-(){
    if(notCorrupt){
        notCorrupt = false;
    }else{
        notCorrupt = true;
    }
}
bool Superhero::operator>(const Superhero& b){
    if(getPower() == "Wood" && b.getPower() == "Fire"){
        return false;
    }
    if(getPower() == "Wood" && b.getPower() == "Wood"){
        return true;
    }
    if(getPower() == "Wood" && b.getPower() == "Water"){
        return true;
    }
    if(getPower() == "Fire" && b.getPower() == "Fire"){
        return true;
    }
    if(getPower() == "Fire" && b.getPower() == "Wood"){
        return true;
    }
    if(getPower() == "Fire" && b.getPower() == "Water"){
        return false;
    }
    if(getPower() == "Water" && b.getPower() == "Water"){
        return true;
    }
    if(getPower() == "Water" && b.getPower() == "Fire"){
        return true;
    }
    if(getPower() == "Water" && b.getPower() == "Wood"){
        return false;
    }
    if(getPower() == "Invisible" && b.getPower() == "Wood"){
        return true;
    }
    if(getPower() == "Invisible" && b.getPower() == "Fire"){
        return false;
    }
    if(getPower() == "Invisible" && b.getPower() == "Water"){
        return true;
    }
    if(getPower() == "Invisible" && b.getPower() == "Flying"){
        return true;
    }
    return false;
}

bool Superhero::operator==(const Superhero& check) const{
    if(name != check.getName())  return false;
    if(power != check.getPower()) return false;
    if(realName != check.realName)  return false;
    if(notCorrupt != check.notCorrupt)  return false;
    return true;
}
