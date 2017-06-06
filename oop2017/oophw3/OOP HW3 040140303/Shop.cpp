#include "Shop.h"
#include <iostream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

template<class Dessert>
void Shop<Dessert>::setDiscount(float tryToSet){
    
    string errorMessage = "Discount rate is out of range!";
    
    if(tryToSet<0 || tryToSet>30){
        throw errorMessage;
    }
    
    discountRate = tryToSet;
    
}

template<class Dessert>
void Shop<Dessert>::add(Dessert& added){
    
    if(ptr==0)
        ptr = new Dessert[SIZE];
    
    ptr[size] = added;
    
    size++;
    
    typeName = added.getTypeName();
    
}

template<class Dessert>
void Shop<Dessert>::addStock(Dessert& added){
    
    if(stockPtr==0)
        stockPtr = new Dessert[SIZE];
    
    stockPtr[stockSize] = added;
    
    stockSize++;
    
    typeName = added.getTypeName();
    
}


template<class Dessert>
Dessert Shop<Dessert>::operator[](int x){
    
    
    return ptr[x];
    
}

template<class Dessert>
void Shop<Dessert>::totalCostPrinter(){
    
    float taxFreeTotalCost=0;
    
    for(int i = 0; i<size; i++)
        taxFreeTotalCost += ptr[i].getBaseCost();
    
    totalCost = taxFreeTotalCost + (taxRate*taxFreeTotalCost);
    
    if(discountRate==0)
        cout<<"Total cost: "<<totalCost<<endl;
    
    else{
        
        discountAmount = (discountRate*totalCost/100);
        discountedCost = (totalCost - discountAmount);
        
        cout<<"Total cost: " << totalCost << endl << "Discount: %" << discountRate << endl << "Discount amount: -" << discountAmount << endl << "Discounted cost: " << discountedCost<<endl;
        
    }
    
}
template <class Dessert>
void Shop<Dessert>::totalCostForOrders(ofstream& output){
    
    
    if(totalCost!=0){
        
        setDiscount(10);
        
        totalCost += totalCost*taxRate;
        
        discountAmount = (discountRate*totalCost/100);
        
        discountedCost = (totalCost - discountAmount);
        
        
        output<< "*****************" << endl;
        
        output<<"Total cost: " << totalCost << endl << "Discount: %10"  << endl << "Discount amount: -" << discountAmount << endl << "Discounted cost: " << discountedCost <<endl;
        
        output<< "*****************" << endl;
        
    }
}

template <class Dessert>
void Shop<Dessert>::stockChecker(ofstream&file){
    
    bool flag;;
    
    for(int i = 0; i<stockSize; i++){
        for(int j = 0; j<size; j++){
            
            flag = false;
            
            if(stockPtr[i].getName() == ptr[j].getName()){
                
                flag = true;
                
            }
            
            if(flag && (stockPtr[i].getAmount() < ptr[j].getAmount())){
                
                file << "!!! We don't have " << ptr[j].getAmount() << "(" << ptr[j].getName() << ")s!" << endl;
                
            }
            
            if(flag && (stockPtr[i].getAmount() >= ptr[j].getAmount())){
                
                totalCost += stockPtr[i].getBaseCost() * ptr[j].getAmount() / stockPtr[i].getAmount();
            }
            
            
            
        }
    }
    
}
