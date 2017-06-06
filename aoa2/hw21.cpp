#include <cstdio>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
using namespace std;
class Sentence {
public:
  vector <pair < string,string > > words;
  bool flag;
  string possible_transform(string, string);
  string extractParseTree(Sentence &,int length,string);
};
map <pair < string, string > , string > Grammar_Rules;
map <string,string> POS_Tags;
void initiliaze_rules();
int main(int argc, char *argv [])
{

  string inp;
  pair < string, string > inp2;
  initiliaze_rules();

  ifstream input(argv[1]);
  ofstream output("output.txt");

    int length=0;
    while(getline(input,inp))
    {

      Sentence asd;
      asd.flag=false;
      stringstream streamS(inp,ios_base::in);
      while(streamS>>inp2.second)
      {
        length++;
        if(inp2.second[0]<'[') //toLower
          inp2.second[0]=inp2.second[0]+32;

        asd.words.push_back(inp2);
        if(streamS.eof())
          break;
      }

      for(int i=0;i<length;i++)
        asd.words[i].first=POS_Tags[asd.words[i].second];
        length--;
        inp=asd.words[length].first+"("+asd.words[length].second+")";

      output<<asd.extractParseTree(asd,length,inp)<<endl;
      length=0;

      if(input.eof())
        break;




  }
  input.close();
  output.close();
  return 0;
}
string Sentence::possible_transform(string in1, string in2)
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
string Sentence::extractParseTree(Sentence &in, int length,string old)
{
    string replacement;
    if(length>0)
    {

      string trans1=in.words[length-1].first; //lastest word of sentence
      string trans2=in.words[length].first; // second lastest word of sentence
      string trans3="("+in.words[length-1].second+")"; // type of second lastest word
      replacement=in.possible_transform(trans1,trans2); // log(k)

      if(replacement!="")
      {
          if(replacement=="S" && length>1) // window is shifted
          {
            flag=true;
            replacement=in.extractParseTree(in,length-1,trans1+trans3); //additional n logn completixy
            for(int i=0;i<in.words.size();i++)
              if(in.words[i].first=="") //after swapping some words are deleted from current sentence, zipping them again
              {
                swap(in.words[i],in.words[length]);
                length=i+1; // 
                break;
              }
            old="["+replacement+" "+old+"]";

          }

          else
          {
            in.words[length].first="";
            in.words[length-1].first=replacement;

            if(flag && replacement=="S")
              old=replacement+old;
            else
              old=replacement+"["+trans1+trans3 +" "+old+"]";

          }
      }

      else
      return "SYNTAX ERROR";





          return in.extractParseTree(in,length-1,old); //iterates n-1 times


    }


    return old;
}
void initiliaze_rules()
{


  POS_Tags["that"]="DT";
  POS_Tags["this"]="DT";
  POS_Tags["a"]="DT";
  POS_Tags["the"]="DT";
  POS_Tags["book"]="NN";
  POS_Tags["flight"]="NN";
  POS_Tags["cat"]="NN";
  POS_Tags["mat"]="NN";
  POS_Tags["i"]="NN";
  POS_Tags["you"]="NN";
  POS_Tags["they"]="NN";
  POS_Tags["booked"]="VR";
  POS_Tags["included"]="VR";
  POS_Tags["preferred"]="VR";
  POS_Tags["sat"]="VR";
  POS_Tags["from"]="PR";
  POS_Tags["to"]="PR";
  POS_Tags["on"]="PR";
  POS_Tags["near"]="PR";
  POS_Tags["through"]="PR";
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


  string inp;
  pair < string, string > inp2;


  inp="NP";
  inp2.first="NN";
  inp2.second="NN";
  Grammar_Rules[inp2]=inp;

  inp2.first="AD";
  inp2.second="NN";
  Grammar_Rules[inp2]=inp;

  inp2.first="AD";
  inp2.second="NP";
  Grammar_Rules[inp2]=inp;

  inp2.first="DT";
  inp2.second="NP";
  Grammar_Rules[inp2]=inp;

  inp2.first="DT";
  inp2.second="NN";
  Grammar_Rules[inp2]=inp;

  inp="PP";

  inp2.first="PR";
  inp2.second="NN";
  Grammar_Rules[inp2]=inp;

  inp2.first="PR";
  inp2.second="NP";
  Grammar_Rules[inp2]=inp;

  inp="VP";
  inp2.first="VR";
  inp2.second="PP";
  Grammar_Rules[inp2]=inp;

  inp2.first="NN";
  inp2.second="VR";
  Grammar_Rules[inp2]=inp;

  inp2.first="NP";
  inp2.second="VR";
  Grammar_Rules[inp2]=inp;

  inp2.first="VR";
  inp2.second="NP";
  Grammar_Rules[inp2]=inp;

  inp="S";
  inp2.first="NP";
  inp2.second="VP";
  Grammar_Rules[inp2]=inp;

  inp2.first="NN";
  inp2.second="VP";
  Grammar_Rules[inp2]=inp;





}
