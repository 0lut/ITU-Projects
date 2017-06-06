#ifndef Cookie_h
#define Cookie_h
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>



using namespace std;



class Cookie{
    
    string name;
    string typeName;
    float number;
    float priceperdozen;
    float cost;
    
    
public:
    Cookie() : name(" "), number(0), priceperdozen(0), cost(0), typeName("cookie"){}
    
    Cookie(const string itsName, float itsNumber, float itsppd) : name(itsName), number(itsNumber), priceperdozen(itsppd), cost(number*priceperdozen/12), typeName("cookie"){}
    
    Cookie(const string itsName, float itsNumber) : name(itsName), number(itsNumber), typeName("cookie"){}
    
    
    float getAmount() const {return number;}
    
    float getPricePerAmount() const {return priceperdozen;}
    
    float getBaseCost() const {return cost;}
    
    string getTypeName() const {return typeName;}
    
    string getName() const {return name;}
    
    friend ostream& operator<<(ostream& out, const Cookie& x){
        
        string errorMessage = "We don't have enough cookies!";
        
        if(x.name == " "){
            
            throw errorMessage;
        }
        
        out << x.name << " " << "#" << x.number << " Cost: " << x.cost <<endl;
        
        return out;
    }
    
    
};

#endif /* Cookie_h */
