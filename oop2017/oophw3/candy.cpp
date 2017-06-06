#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "candy.h"


ostream& Candy::operator<<(ostream& out, const Candy& x){
    
    string errorMessage = "We don't have enough candies!";
    
    if(x.name == " "){
        
        throw errorMessage;
    }

  
    out << x.name << " " << "#" << x.weight << " Cost: "<< x.cost <<endl;

    return out;

}
