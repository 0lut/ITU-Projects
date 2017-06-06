#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
typedef struct Passenger{
    int telephone;
    int passportNum; //assuming this is unique for each passenger.
    string nationality;
    string name;
    string address;
    Passenger * next=NULL;
    void printPassenger();
} Passenger;
void Passenger::printPassenger()
{
    cout <<"Credentials of passenger :"<<endl;
    cout <<"Name: "<<name<<endl;
    cout <<"Nationality: "<<nationality<<endl;
    cout << "Address: "<<address<<endl;
    cout <<"Passport number: "<<passportNum<<endl;
    cout <<"Telephone number: "<<telephone<<endl;
}

typedef struct Flight {
    int flightCode;
    int departure;
    int destination;
    string airPlaneType;
    string origin;
    string departureTime,landingTime;
    int totalSeats, reservedSeats;
    int ticketPrice;
    Passenger * head=NULL;
    Passenger * tail=NULL;
    Passenger * list=NULL;
    Passenger * taillist=NULL;
    bool registerPassenger(Passenger);
    void removePassenger(int);
    void removeAll();
    void printFlight();
} Flight;
typedef struct FlightList{
    int capacity;
    int totalFlights;
    Flight * ptr=NULL;
    void initialize();
    void addFlight();
    void extendList();
    void removeFlight();
    void removeAll();

} FlightList;
bool Flight::registerPassenger(Passenger toRegis)
{
    Passenger * registered = new Passenger;
    *registered=toRegis;
    if(totalSeats-reservedSeats<=0)
    {
        cout << "There are no avaible seats for flight #" << flightCode <<"passenger is taken to the queue"<<endl;


    if(head==NULL) // queue is empty
    {
        head=registered;
        head->next=NULL;
        tail=head;
    }
    else
    {
        tail->next=registered;
        tail=registered;
        tail->next=NULL;
    }
    }

    else
    {
        if(list==NULL) // list is empty
        {
            list=registered;
            list->next=NULL;
            taillist=list;
        }
        else
        {
            taillist->next=registered;
            taillist=registered;
            taillist->next=NULL;
        }
        reservedSeats++;
    }
    return true;
}
void Flight::removePassenger(int toRem)
{
    Passenger * trav=list;
    Passenger * prev=list;
    while(trav)
    {
        if(trav->passportNum==toRem)
        {
            cout << "Passanger to remove is found in registered passenger list"<<endl;

            if(trav==list) //if it is head of list
                list=trav->next;
           else if(trav==taillist) // if it is tail of list
                taillist=prev;
            else // if an intermediate element of list
            prev->next=trav->next;
            delete trav;
        }
        prev=trav;
        trav=trav->next;
    }
    trav=head;
    while(trav)
    {
        if(trav->passportNum==toRem)
        {
            cout << "Passanger to remove is found in waiting passenger queue"<<endl;

            if(trav==head) //if it is head of queue
                head=trav->next;
           else if(trav==tail) // if it is tail of queue
                tail=prev;
            else // if an intermediate element of queue
            prev->next=trav->next;
            delete trav;
        }
        prev=trav;
        trav=trav->next;
    }
}
void Flight::printFlight()
{
    cout << "Informations of flight: \n";
    cout << "Flight code: "<<flightCode<<endl;
    cout << "Departuring from: "<<departure<<endl;
    cout << "Destination of flight: "<<destination<<endl;
    cout << "Departure at "<< departureTime<<endl;
    cout << "Land at " << landingTime <<endl;
    cout << "Type of plane: " << airPlaneType<<endl;
    cout << "Avaible seats: "<<totalSeats-reservedSeats<<endl;
    cout << "Ticket price: "<<ticketPrice<<endl;
    cout << "Registered passenger list: "<<endl;
    Passenger *trav=list;
    while(trav)
    {
        trav->printPassenger();
        trav=trav->next;
    }
    cout << "Waiting passenger queue: "<<endl;
    trav=head;
    while(trav)
    {
        trav->printPassenger();
        trav=trav->next;
    }
}
void FlightList::initialize()
{
    capacity=20;
    totalFlights=0;
    ptr=new Flight[20];
}
void FlightList::addFlight()
{
    if(capacity==totalFlights)
        extendList();

    cout <<"Enter the informations of flight correspondingly."<<endl;
    Flight temp;
    totalFlights++;

}
void FlightList::extendList()
{
    capacity*=2;
    Flight *tmpptr=new Flight[capacity];
    for(int i=0;i<totalFlights;i++)
        tmpptr[i]=ptr[i];
    delete [] ptr;
    ptr=tmpptr;
}
void FlightList::removeFlight()
{
    cout << "Enter the flight code that you want to delete: "<<endl;
    int inp;
    bool flag=false;
    cin >> inp;
    int i=0;
    for(;i<totalFlights;i++)
        if(ptr[i].flightCode==inp)
        {
            flag=true;
            break;

        }
    if(flag)
    {
        cout<< "The flight is found, the followings are information of flight: "<<endl<<"Are you sure?(Y/N)";
        char decision;
        cin >>decision;
        if(decision=='Y')
        {
            //ptr[i].removeAll();
            ptr[i]=ptr[totalFlights--];
        }

        else if(decision=='N')
            cout << "The flight is not going to be deleted"<<endl;
        else
        {
            cout<< "Invalid decision is made, returning to main menu."<<endl;
        }
    }
    else
        cout <<"The flight could not be found"<<endl;

    return;
}
void FlightList::removeAll()
{
    for(int i=0;i<totalFlights;i++)
    {
        //ptr[i].removeAll();
    }
    delete [] ptr;
}
int main()
{
    Flight asd;
    asd.airPlaneType="aeroplane";
    asd.flightCode=123;
    asd.departure=333;
    asd.destination=444;
    asd.origin="Foshiq tece";
    asd.departureTime="12.34";
    asd.landingTime="13.31";
    asd.totalSeats=3;
    asd.reservedSeats=1;
    asd.ticketPrice=31;
    Passenger asd2;
    asd2.address="ataturk mah 164/4";
    asd2.name="kilimci";
    asd2.nationality="kurdish";
    asd2.passportNum=1133;
    asd2.telephone=331;

    asd.registerPassenger(asd2);
    asd2.nationality="ananza";
    asd2.passportNum=3131;
    asd.registerPassenger(asd2);
    asd.printFlight();
    asd.removePassenger(1133);
    asd.registerPassenger(asd2);
    asd.printFlight();
    return 0;
}
