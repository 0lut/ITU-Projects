#ifndef Candy_h
#define Candy_h
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>


using namespace std;


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
    
    
    friend ostream& operator<<(ostream& out, const Candy& x){
        
        string errorMessage = "We don't have enough candies!";
        
        if(x.name == " "){
            
            throw errorMessage;
        }
        
        
        out << x.name << " " << "#" << x.weight << " Cost: "<< x.cost <<endl;
        
        return out;
        
    }
    
    float getAmount() const {return weight;}
    
    float getPricePerAmount() const {return priceperkg;}
    
    float getBaseCost() const {return cost;}
    
    string getTypeName() const {return typeName;}
    
    string getName() const {return name;}
    
};


#endif /* Candy_h */
