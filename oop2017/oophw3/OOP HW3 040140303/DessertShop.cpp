#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Shop.h"
#include "Shop.cpp"
#include "Cookie.h"
#include "Candy.h"
#include "Icecream.h"


using namespace std;

void txtReadWrite();

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
    
       
    return 0;
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


