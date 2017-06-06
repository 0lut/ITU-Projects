#ifndef Icecream_h
#define Icecream_h
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>


using namespace std;


class Icecream{
    
    string name;
    string typeName;
    float litre;
    float priceperlitre;
    float cost;
    
public:
    Icecream() : name(" "), litre(0), priceperlitre(0), cost(0), typeName("ice cream"){}
    
    Icecream(const string itsName, float itsLitre, float itsppl) : name(itsName), litre(itsLitre), priceperlitre(itsppl), cost(litre*priceperlitre), typeName("ice cream") {}
    
    Icecream(const string itsName, float itsLitre) : name(itsName), litre(itsLitre), typeName("ice cream"){}
    
    float getAmount() const {return litre;}
    
    float getPricePerAmount() const {return priceperlitre;}
    
    float getBaseCost() const {return cost;}
    
    string getTypeName() const {return typeName;}
    
    string getName() const {return name;}
    
    friend ostream& operator<<(ostream& out, const Icecream& x){
        
        string errorMessage = "We don't have enough ice creams!";
        
        if(x.name == " "){
            
            throw errorMessage;
        }
        
        out << x.name << " " << "#" << x.litre << " Cost: " << x.cost <<endl;
        
        return out;
        
    }
    
};


#endif /* Icecream_h */
