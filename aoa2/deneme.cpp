#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
void arrTr(int x[][6])
{
for(int i=0;i<6;i++)
for(int j=0;j<6;j++)
	x[i][j]=i;
}

int ** convertArr(string toConv)
{
		int **arr;
		arr=new int*[6];
		int count=0;
		for(int i=0;i<6;i++)
		{
			arr[i]=new int[6];
				for(int j=0;j<6;j++)
				{
					arr[i][j]=int(toConv[count])-48;
					count++;
				}
		}
		
		return arr;
}

string convertStr(int maze[][6])
{
	string convertedStr;
	for(int i=0;i<6;i++)
		for(int j=0;j<6;j++)
			convertedStr.push_back(char(maze[i][j]+49));
			
	return convertedStr;
}
int main()

{

int arr[6][6];
arrTr(arr);
string asd=convertStr(arr);
int **newarr=convertArr(asd);
for(int i=0;i<6;i++)
for(int j=0;j<6;j++)
	cout<<newarr[i][j]<<'\t';


 
}
