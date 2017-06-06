#ifndef Shop_h
#define Shop_h
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>


using namespace std;

const int SIZE = 50;



template<class Dessert>
class Shop{
    
    Dessert* ptr = 0;
    Dessert* stockPtr = 0;
    string name = " ";
    string typeName = " ";
    float amount = 0;
    float pricePerAmount = 0;
    const float taxRate = 0.08;
    float discountRate = 0;
    int size = 0;
    int stockSize = 0;
    int sizeException = 0;
    float taxFreeCost = 0;
    float totalCost = 0;
    float discountedCost = 0;
    float discountAmount = 0;
    float stockCost = 0;
public:
    Shop(){
        
        ptr = new Dessert[SIZE];
        stockPtr = new Dessert[SIZE];
        
    }
    Shop(const Dessert& obj){
        
        if(ptr)
            delete[] ptr;
        
        ptr = new Dessert[SIZE];
        ptr[size] = obj;
        size++;
        
    }
    
    
    int getSize() const { return size; }
    
    int getStockSize() const { return stockSize; }
    
    float getDiscountAmount(){return discountAmount;}
    
    float getDiscountedCost(){return discountedCost;}
    
    float getTotalCost(){return totalCost;}
    
    void add(Dessert&);
    
    void addStock(Dessert&);
    
    void totalCostPrinter();
    
    void totalCostForOrders(ofstream&);
    
    void setDiscount(float);
    
    Dessert operator[](int);
    
    void stockChecker(ofstream&file);
    
    
    void txtReadWrite();
    
    ~Shop(){delete[] ptr;}
    
    
    friend ostream& operator<<(ostream& loadedOut, Shop& out){
        
        cout << "*****************" << endl;
        
        if(out.ptr == NULL)
            loadedOut << "No items to print!" <<endl;
        
        else{
            
            loadedOut << "Number of items: " << out.size << endl <<endl;
            
            for(int i = 0; i<out.size; i++)
                loadedOut << i+1 << ": " << out.ptr[i].getName() << " #" << out.ptr[i].getAmount() << " Cost: " << out.ptr[i].getBaseCost()<< endl<<endl;
        }
        
        loadedOut << "*****************" <<endl;
        
        out.totalCostPrinter();
        
        loadedOut << "*****************" <<endl;
        
        return loadedOut;
    }
    
    friend void operator<<(ofstream& file, Shop& out){
        
        
        
        out.stockChecker(file);
        
        file << "-------------------" << endl;
        
        
        
        if(out.getTotalCost() == 0)
            return;
        
        else{
            
            file << "Number of items: " << out.size << endl <<endl;
            
            for(int i = 0; i<out.size; i++)
                file << i+1 << ": " << out.ptr[i].getName() << " #" << out.ptr[i].getAmount() << " Cost: " << out.stockPtr[i].getBaseCost() * out.ptr[i].getAmount() / out.stockPtr[i].getAmount()<< endl<<endl;
        }
        
        file << "*****************" <<endl;
        
        out.totalCostForOrders(file);
        
        file << "*****************" <<endl;
        
        
    }
    
    
};


#endif /* Shop_h */
