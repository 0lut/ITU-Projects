#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "candy.h"

using namespace std;

const int SIZE = 50;



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
    
    friend ostream&  operator<<(ostream&, const Cookie&);
    
};

ostream& operator<<(ostream& out, const Cookie& x){

    string errorMessage = "We don't have enough cookies!";
    
    if(x.name == " "){
        
        throw errorMessage;
    }
    
    out << x.name << " " << "#" << x.number << " Cost: " << x.cost <<endl;

    return out;
}

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
    
    friend ostream&  operator<<(ostream&, const Icecream&);
    
};

ostream& operator<<(ostream& out, const Icecream& x){

    string errorMessage = "We don't have enough ice creams!";
    
    if(x.name == " "){
        
        throw errorMessage;
    }

    out << x.name << " " << "#" << x.litre << " Cost: " << x.cost <<endl;
   
    return out;

}

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
void txtReadWrite(){
    
    
    string line;
    string orderLine;
    string header;
    string addedName;
    string orderedName;
    string forNumbers;
    string forOrderNumbers;
    int addedTypeNumber = 0;
    float addedAmount = 0;
    float addedPrice = 0;
    int orderedTypeNumber;
    float orderedAmount;
    Shop<Cookie> cookieShop;
    Shop<Candy> candyShop;
    Shop<Icecream> iceCreamShop;
    
    ifstream instock;
    instock.open("stock.txt");

    
    if(instock.fail()){
        
        cout<<"Stock file cannot be opened!"<<endl;
    
        return;
        
    }
    
    else{
    getline(instock, header);
    
    while(getline(instock, line)){
        
        int j = 0;
        
        for(int i = 0; i<line.length(); i++){
        
            j++;
            
            if(iscntrl(line[i]))
            {
                
                break;
            }
        
            
        }
        
        
        addedName.assign(line,0,j);
        forNumbers.assign(line,j,line.length()-j);
        
        stringstream ss(forNumbers);
        
        ss >> addedTypeNumber >> addedAmount >> addedPrice;
        
        
        if(addedTypeNumber == 1){
            
            Cookie cookie1(addedName, addedAmount, addedPrice);
            cookieShop.addStock(cookie1);
            
        }
        
        if(addedTypeNumber == 2){
            
            Candy candy1(addedName, addedAmount, addedPrice);
            candyShop.addStock(candy1);
            
        }
        
        if(addedTypeNumber == 3){
            
            Icecream icecream1(addedName, addedAmount, addedPrice);
            iceCreamShop.addStock(icecream1);
            
        }

    }
}
    
    ifstream inorder;
    inorder.open("order.txt");
    
    if(inorder.fail()){
        
        cout<<"Order file cannot be opened!"<<endl;
        
        return;
        
    }
    
    
    while(getline(inorder, orderLine)){
        
        int j = 0;
        
        for(int i = 0; i<orderLine.length(); i++){
            
            j++;
            
            if(iscntrl(orderLine[i]))
            {
                
                break;
            }
            
            
        }
        
        
        orderedName.assign(orderLine,0,j);
        forOrderNumbers.assign(orderLine,j,orderLine.length()-j);
        
        stringstream ss(forOrderNumbers);
        
        ss >> orderedTypeNumber >> orderedAmount;
        
        
        if(orderedTypeNumber == 1){
            
            Cookie cookie1(orderedName, orderedAmount);
            cookieShop.add(cookie1);
            
            
        }
        
        if(orderedTypeNumber == 2){
            
            Candy candy1(orderedName, orderedAmount);
            candyShop.add(candy1);
            
        }
        
        if(orderedTypeNumber == 3){
            
            Icecream icecream1(orderedName, orderedAmount);
            iceCreamShop.add(icecream1);
            
        }
        
}

    
    ofstream checkout;
    checkout.open("checkout.txt");
    
    if(checkout.fail()){
        
        cout<<"Checkout file cannot be opened!"<<endl;
        
        return;
        
    }
    
    else{
        
        checkout << candyShop;
        checkout << iceCreamShop;
        checkout << cookieShop;
        
        
    }
    checkout.close();
    inorder.close();
    instock.close();
    
    
}

//////////////////////////////////end//////////////////////////////////////////////////////

int main() {
    Cookie cookie1("Chocolate Chip Cookies",10, 180); //(name, pieces, priceperdozen)
    Cookie cookie2("Cake Mix Cookies", 16, 210);
    
    //cout<<cookie1<<endl;

    Shop<Cookie> cookieShop(cookie1);
    cookieShop.add(cookie2);
    cout<<cookieShop<<endl;

    //Catch an exception here while trying to access the element at(2)
    
    try{
        cout << cookieShop[2] << endl;
    }
    
    catch (const string msg){
        cout<<msg<<endl;
    }
    Icecream icecream1("Chocolate ice cream",1.5, 170); //(name, litre, priceperlitre)
    Shop<Icecream> icecreamShop(icecream1);
    cout<<icecreamShop<<endl;

    //Catch an exception here while trying to set the discount to(50)
    try{
        
        icecreamShop.setDiscount(50);

        
    }
    
    catch(const string message){
        
        cout<<message<<endl;
    }
    
    Candy candy2("Gummi bears",12,89); //(name, weight, priceperkg)
    Candy candy3("Hanukkah gelt",8,110);

    Shop<Candy> candyShop(candy2);
    candyShop.add(candy3);

    candyShop.setDiscount(15);
    cout<<candyShop<<endl;
    
    txtReadWrite();
    

    /*You will also
     1) Read dessert stock and customer order from "stock.txt" and "order.txt", respectively.
     2) Write the total cost with 10% discount to8 "checkout.txt".
     Expected output for checkout:

     !!! We don't have 7 (Orange Jelly Candy)s.
     !!! We don't have 11 (Chocolate ice cream)s.
     -----------------------
     Number of items:2
     1: Chocolate Chip Cookies #2 Cost: 100

     2: Cake Mix Cookies #10 Cost: 150

     **********************
     Total cost: 270.0
     Discount: 10%
     Discount amount: -27.0
     Discounted cost: 243.0
     **********************

     */

    return 0;
}
