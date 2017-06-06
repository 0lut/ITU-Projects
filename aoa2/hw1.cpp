#include <iostream>
#include <utility>
#include <set>
#include <cstdio>
#include <fstream>
#include <queue>          // std::queue
#include <deque>
#include <vector>
#include <string>
using namespace std;

class Block {
public:
	int xCor,yCor; 
	int length;
	char dir;
	
	Block(int x=0,char y='h',int k=0, int l=0):length(x),dir(y),xCor(k),yCor(l) {}
      
};

string convertStr(int [][6]);
void convertArr(string, int [][6]); 
bool canMove(Block &, string &, char);
void moveTarget(Block &, string &,char);
bool findInVec(vector < string > , string);

int main()
{

  //vector < vector <int > > puzzle(6, vector <int>(6,0));
	/*vector <int > puzzle[6];
	for(int i=0;i<6;i++)
		for(int j=0;j<6;j++)
			puzzle[i][j]=0;*/
  int puzzle[6][6]={0};
			
  vector <Block> blocks;
  //blocks
  ifstream file("blocks.txt");
  int i=0;
  while(!file.eof())
  {
	  i++;
	  Block temp;
      int x,y,len;
      char dir;
      file >> y>>x>>len>>dir;
      puzzle[y-1][x-1]=i;
      if(dir=='h')
          for(int k=0;k<len;k++)
              puzzle[y-1][x-1+k]=i;
      else
          for(int k=0;k<len;k++)
              puzzle[y-1-k][x-1]=i;

	  temp.xCor=x;
	  temp.yCor=y; //degisti
      temp.length=len;
      temp.dir=dir;
      blocks.push_back(temp);
      
      
 }

  for(i=0;i<6;i++){
      
      for(int j=0;j<6;j++)
          cout << puzzle[i][j]<<' '; 
              cout <<endl;
}
	
	
	
	queue < pair < vector < Block > , string > > state_que;
	vector < string > old_states;
	pair < vector < Block > , string  > init;
	init.first=blocks;
	init.second=convertStr(puzzle);
	state_que.push(init);
		while(!state_que.empty())
	
	{			
		for(int i=0;i < state_que.front().first.size();i++)
		{
			
			
			pair < vector < Block >, string > temp = state_que.front();
			pair < vector < Block >, string > temp2 = state_que.front();
			if(temp.first[i].dir=='h')
				{
					moveTarget(temp.first[i],temp.second,'l');
					if(!findInVec(old_states,temp.second))
						{
							old_states.push_back(temp.second);
							state_que.push(temp);
						}
						
				}		
			if(temp.first[i].dir=='h')
				{
					moveTarget(temp2.first[i],temp2.second,'r');
					if(!findInVec(old_states,temp.second))
						{
							old_states.push_back(temp2.second);
							state_que.push(temp2);
						}
				}
			if(temp.first[i].dir=='v')
				{
					moveTarget(temp.first[i],temp.second,'u');
					if(!findInVec(old_states,temp.second))
						{
							old_states.push_back(temp.second);
							state_que.push(temp);
						}
				}
			if(temp.first[i].dir=='v')
				{
					moveTarget(temp.first[i],temp2.second,'d');
					if(!findInVec(old_states,temp2.second))
						{
							old_states.push_back(temp2.second);
							state_que.push(temp2);
						}
				}
			
			
			int x[6][6];
		convertArr(temp.second,x);
		for(int z=0;z<6;z++)
		{
			for(int q=0;q<6;q++)
				cout<<x[z][q]<<"  ";
			cout<<endl;
		}
		cout<<endl;
		}
		
		state_que.pop();
	}



}
bool findInVec(vector <string> toSearch, string toFind)
{
		for(int i=0;i<toSearch.size();i++)
			if(toSearch[i]==toFind)
				return true;
				
		return false;
}

void moveTarget(Block & toMove, string &currMaze,char moveDir)
{
	
		int maze[6][6];
		convertArr(currMaze,maze);
		
		
		int blockNum=maze[toMove.yCor-1][toMove.xCor-1];
		
		if(moveDir=='l')
			if(canMove(toMove,currMaze,'l'))
				{
					maze[toMove.yCor-1][toMove.xCor-2]=blockNum;
					toMove.xCor--;
					maze[toMove.yCor-1][toMove.xCor-1+toMove.length]=0;
					
					
				}
		if(moveDir=='r')
			if(canMove(toMove,currMaze,'r'))
				{
				
					maze[toMove.yCor-1][toMove.xCor-1]=0;
					maze[toMove.yCor-1][toMove.xCor-1+toMove.length]=blockNum;
					toMove.xCor++;
					
					
				}
		
		if(moveDir=='u')
			if(canMove(toMove,currMaze,'u'))
				{	
					maze[toMove.yCor-1][toMove.xCor-1]=0;
					maze[toMove.yCor-1-toMove.length][toMove.xCor-1]=blockNum;
					toMove.yCor--;
				}
		if(moveDir=='d')
			if(canMove(toMove,currMaze,'d'))
				{
					
					maze[toMove.yCor][toMove.xCor-1]=blockNum;
					maze[toMove.yCor-toMove.length][toMove.xCor-1]=0;
					toMove.yCor++;
					
					
				}
				
		//currMaze=convertStr(maze);
		for(int i=0;i<6;i++)
		{
			for(int j=0;j<6;j++)
				cout <<maze[i][j]<<'\t';
			cout <<endl;
		}
		
		cout <<endl;
		
	
}
bool canMove(Block & toMove,string &currMaze, char moveDir)

{
	int maze[6][6];
	convertArr(currMaze,maze);
	int xCor=toMove.xCor;
	int yCor=toMove.yCor;
	int length=toMove.length;
	if(moveDir=='l' && (xCor-2 >= 0) && maze[(yCor - 1)][xCor-2] == 0 )
		return true;
	
	if(moveDir=='r' && (xCor+length-1<6) && maze[yCor-1][xCor-1+length] == 0)
		return true;
		
	if(moveDir=='u' && (yCor-1-length>=0) && maze[yCor-1-length][xCor - 1] == 0 )
		return true;
		
	if(moveDir=='d' && (yCor < 6) && maze[yCor][xCor-1] == 0 )
		return true;
		
	
			
	

	
		
	return false;
	
	
}

string convertStr(int maze[][6])
{
	string convertedStr;
	for(int i=0;i<6;i++)
		for(int j=0;j<6;j++)
			convertedStr.push_back(char(maze[i][j]+48));
			
	return convertedStr;
}

void convertArr(string toConv,int arr[][6])
{
	
		int count=0;
		for(int i=0;i<6;i++)
		{
		
				for(int j=0;j<6;j++)
				{
					arr[i][j]=int(toConv[count])-48;
					count++;
				}
		}
		
		
}
