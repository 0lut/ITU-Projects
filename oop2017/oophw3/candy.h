#ifndef CANDY_H
#define CANDY_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>

class Candy{

    string name;
    string typeName;
    float weight;
    float priceperkg;
    float cost;


public:
    Candy() : name(" "), weight(0), priceperkg(0), cost(0), typeName("candy"){}
    
    Candy(const string itsName, float itsWeight, float itsppk) : name(itsName), weight(itsWeight), priceperkg(itsppk), cost(weight*priceperkg), typeName("candy"){}
    
    Candy(const string itsName, float itsWeight) : name(itsName), weight(itsWeight), typeName("candy"){}

    
    friend ostream& operator<<(ostream&, const Candy&);
    
    float getAmount() const {return weight;}
    
    float getPricePerAmount() const {return priceperkg;}
    
    float getBaseCost() const {return cost;}
    
    string getTypeName() const {return typeName;}
    
    string getName() const {return name;}
    
};
#endif
