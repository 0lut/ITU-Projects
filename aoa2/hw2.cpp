#include <cstdio>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;
class Sentence {
public:
  vector <string> words;
  string ans="";

};
string divide_string(Sentence &,int length,string);
string possible_transform(string , string );
map <pair < string, string > , string > Grammar_Rules;
int main()
{

  map <string,string> POS_Tags;
  string inp;
  pair < string, string > inp2;
  POS_Tags["that"]="DT";
  POS_Tags["this"]="DT";
  POS_Tags["a"]="DT";
  POS_Tags["the"]="DT";
  POS_Tags["book"]="NN";
  POS_Tags["flight"]="NN";
  POS_Tags["cat"]="NN";
  POS_Tags["mat"]="NN";
  POS_Tags["I"]="NN";
  POS_Tags["you"]="NN";
  POS_Tags["they"]="NN";
  POS_Tags["booked"]="VR";
  POS_Tags["included"]="VR";
  POS_Tags["preffered"]="VR";
  POS_Tags["sat"]="VR";
  POS_Tags["from"]="PR";
  POS_Tags["to"]="PR";
  POS_Tags["on"]="PR";
  POS_Tags["near"]="PR";
  POS_Tags["though"]="PR";
  POS_Tags["big"]="AD";
  POS_Tags["heavy"]="AD";
  POS_Tags["beautiful"]="AD";
  POS_Tags["cheap"]="AD";
  POS_Tags["DT"]="DT";
  POS_Tags["NN"]="NN";
  POS_Tags["S"]="S";
  POS_Tags["NP"]="NP";
  POS_Tags["VP"]="VP";
  POS_Tags["PP"]="PP";
  POS_Tags["VR"]="VR";
  POS_Tags["PR"]="PR";

  ifstream input("rules.txt");

  while(!input.eof())
  {
    input >> inp >>inp2.first>>inp2.second;
    Grammar_Rules[inp2]=inp;
  }
    Sentence asd;
    asd.words.push_back("the");
    asd.words.push_back("cat");
    asd.words.push_back("sat");
    asd.words.push_back("on");
    asd.words.push_back("the");
    asd.words.push_back("mat");
    for(int i=0;i<6;i++)
      asd.words[i]=POS_Tags[asd.words[i]];
    cout<<divide_string(asd,5,"NN(mat)")<<endl;
      //cout<< possible_transform("NP","VP");

}
string possible_transform(string in1, string in2)
{
    pair <string,string> temp;
    temp.first=in1;
    temp.second=in2;
    if(Grammar_Rules.find(temp)!=Grammar_Rules.end())
    {
      return Grammar_Rules[temp];
    }



    return "";
}
string divide_string(Sentence &in, int length,string old)
{
    string replacement;
    bool flag=false;
    if(length>0)
    {
      string trans2=in.words[length];
      string trans1=in.words[length-1];
      replacement=possible_transform(trans1,trans2);

      if(replacement!="")
      {
          if(replacement=="S" && length>1)
          {
            flag=true;
            replacement=divide_string(in,length-1,in.words[length-1]+"(e)");

            for(int i=0;i<in.words.size();i++)
              if(in.words[i]=="")
              {
                swap(in.words[i],in.words[length]);
                break;
              }
            old="["+replacement+" "+old+"]";
          }

          else
          {
            in.words[length]="";
            in.words[length-1]=replacement;
            if(replacement=="S")
              trans1="";
          }
      }
          //cout<<endl<<replacement<<length<<endl<<old<<endl;
          if(!flag)
            old=replacement+"["+trans1+"(e) "+old+"]";
          return divide_string(in,length-1,old);


    }


    return old;
}
