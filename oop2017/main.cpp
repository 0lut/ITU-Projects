
#include <iostream>
#include <string>

using namespace std;

class Node{

public:
    Node *next;
    Node *previous;
    int data;
    Node(){


        data = 0;
    }
    Node(int i){
        next = NULL;
        previous = NULL;
        data = i;
    }
};


class ARTraverser{

    friend class AdderRemover;
    friend class FAFR;
    friend class FALR;
    friend class LAFR;
    friend class LALR;


protected:
    Node *current;

public:
    virtual bool hasNode() const = 0;
    virtual int next() = 0;


};

class ARTF:public ARTraverser{

public:

    int element;

    bool hasNode() const{

        if(current) {return true;}
        else {return false;}

    }

    int next(){

        if(hasNode())

        {

            element = current->data;
            current = current->next;

            return element;

        }

        else return -1;

    }
};

class ARTL:public ARTraverser{

public:

    int element;

    bool hasNode() const{

        if(current!=NULL)
        {


            return true;

        }

        return false;
    }

    int next(){

        if(hasNode()==true)

        {

            element = current->data;
            current = current->previous;
            cout <<"Next";
            return element;

        }

        else return -1;


    }
};


class AdderRemover{

protected:
    Node *head;
    Node *tail;
    string name;
    ARTraverser *traverser;
    int nodeCount;
public:
    virtual void add(int i) = 0;
    virtual void remove() = 0;
    virtual void setTraverser() = 0;
    virtual void removeAll() =0;

    void display(){



        if(head==NULL){
            cout<<endl;
            cout<<name<<" | NodeCount: 0"<<endl;
            cout<<"-----"<<endl;
            cout<<"There's no element to print."<<endl<<endl;
        }


        else{

            cout<<endl;
            cout<<name<<" | NodeCount: "<<nodeCount<<endl;
            cout<<"-----"<<endl;

            while(head)
            {
                cout<<head->data<<endl;
                head=head->next;
            }

        }
    }


    void traverse(){


        cout<<"abi cidden mi   "<<name;

        if(name=="FAFR"||name=="FALR"){

            traverser = new ARTF();
            traverser->current = head;

            if(traverser->hasNode()==false){
                cout<<endl;
                cout<<name<<" | NodeCount: 0"<<endl;
                cout<<"-----"<<endl;
                cout<<"There's no element to print."<<endl<<endl;

            }

            else{
                cout<<endl;
                cout<<name<<" | NodeCount: "<<nodeCount<<endl;
                cout<<"-----"<<endl;

                while(traverser->current !=NULL){
                    cout<<traverser->next()<<endl;
                }

            }

        }

        if(name=="LAFR"||name=="LALR"){

            traverser = new ARTL();
            traverser->current = tail;

            if(traverser->hasNode()==false){
                cout<<endl;
                cout<<name<<" | NodeCount: 0"<<endl;
                cout<<"-----xd"<<endl;
                cout<<"There's no element to print."<<endl<<endl;

            }

            else{
                cout<<endl;
                cout<<name<<" | NodeCount: "<<nodeCount<<endl;
                cout<<"-----xd"<<endl;
                int i=0;
                while(traverser->hasNode())
                    cout<<traverser->next()<<" " << i++ <<endl;


            }

        }



    }

};

class LALR:public AdderRemover{

    Node *temp;

public:


    void add(int i){

        temp = new Node(i);

        if(tail){

            temp->previous=tail;
            tail->next=temp;
            tail=temp;
            tail->next=NULL;
            nodeCount++;
        }

        else{

            head=NULL;
            tail=temp;
            tail->next=NULL;
            tail->previous=NULL;
            nodeCount++;
        }

    }

    void remove(){

        if(tail->previous!=NULL){

            temp = tail;
            tail = tail->previous;
            temp->previous->next = NULL;
            temp->previous = NULL;
            delete temp;
            nodeCount--;
            name = "LALR";
        }



          else  if(tail==NULL) //check
                cout<<"There's nothing to remove"<<endl;

            else
            {

                temp = head;
                head = NULL;
                tail = NULL;
                delete temp;
                nodeCount = 0;

            }
      void removeAll()
      {
        while(nodeCount)
          remove();
      }    


    }

    void setTraverser(){

        name = "LALR";

    }
    LALR(){
        cout<<"olusturduk abi";
    }
};
class FAFR:public AdderRemover{

    Node *temp;
public:

    void add(int i){

        temp = new Node(i);

        if(head){

            temp->next = head;
            head->previous = temp;
            head = temp;
            nodeCount++;
            name = "FAFR";

        }

        else{

            head = temp;
            tail = temp;
            nodeCount++;
            name = "FAFR";


        }

    }

    void remove(){

        if(head->next!=NULL){


            temp = head;
            head = head->next;
            temp->next = NULL;
            head->previous = NULL;
            delete temp;
            --nodeCount;
            name = "FAFR";
        }

        else{

            if(head==NULL)
                cout<<"There's nothing to remove"<<endl;

            else{

                temp = head;
                head = NULL;
                tail = NULL;
                delete temp;
                nodeCount = 0;
                name = "FAFR";
            }


        }


    }

    void setTraverser(){

        name = "FAFR";


    }
};

class FALR:public AdderRemover{

    Node *temp;

public:

    void add(int i){

        temp = new Node(i);

        if(head){

            temp->next = head;
            head->previous = temp;
            head = temp;
            nodeCount++;
            name = "FALR";

        }

        else{


            temp->data = i;
            head = temp;
            tail = temp;
            nodeCount++;
            name = "FALR";



        }

    }

    void remove(){

        if(head->next!=NULL){

            temp = tail;
            tail = tail->previous;
            temp->previous->next = NULL;
            temp->previous = NULL;
            delete temp;
            --nodeCount;
            name = "FALR";
        }

        else{

            if(tail==NULL)
                cout<<"There's nothing to remove"<<endl;

            else{

                temp = head;
                head = NULL;
                tail = NULL;
                delete temp;
                nodeCount = 0;
                name = "FALR";
            }
        }

    }

    void setTraverser(){

        name = "FALR";

    }
};

class LAFR:public AdderRemover{

    Node *temp;

public:


    void add(int i){

        temp = new Node(i);

        if(head){

            temp->previous = tail;
            tail->next = temp;
            temp->next = NULL;
            tail = temp;
            nodeCount++;
            name = "LAFR";
        }

        else{

            head = temp;
            tail = temp;
            nodeCount++;
            name = "LAFR";
        }

    }



    void remove(){

        if(head->next!=NULL){


            temp = head;
            head = head->next;
            temp->next = NULL;
            head->previous = NULL;
            delete temp;
            --nodeCount;
            name = "LAFR";
        }

        else{

            if(head==NULL)
                cout<<"There's nothing to remove"<<endl;

            else{

                temp = head;
                head = NULL;
                tail = NULL;
                delete temp;
                nodeCount = 0;
                name = "LAFR";
            }


        }


    }

    void setTraverser(){

        name = "LAFR";


    }

};





int main(int argc, char **argv) {

    AdderRemover *myList[4];

    myList[0] = new FAFR();
    myList[1] = new LALR();
    myList[2] = new FALR();
    myList[3] = new LAFR();

    for(int j=0; j<4; j++) {
        for(int i=0; i<5; i++)
            myList[j]->add(i);
    }



    for(int j=0; j<4; j++){
        myList[j]->remove();
        myList[j]->display();
        myList[j]->removeAll();
        myList[j]->display();
    }

    cout << endl << "Test case for ARTraverser"<< endl;
    for(int j=0; j<4; j++) {
        for(int i=0; i<5; i++)
            myList[j]->add(i);
        myList[j]->remove();
    }
    cout <<"x";
    for(int j=0; j<4; j++){

        myList[j]->setTraverser();
        myList[j]->traverse();
    }

    return 0;
}
