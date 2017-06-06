#include <stdio.h>
#include <string.h>
void stage_one(char * );
void stage_two();
int compare_for_stage_one(char, char);
int main()
{
  char inputString[51];
  printf("Enter a string up to 50 characters to process\n");
  scanf("%s",inputString);
  stage_one(inputString);
  printf("\nResult of stage 1:\t%s\n",inputString);
  stage_two(inputString);
  printf("\nResult of stage 2:\t%s\n",inputString);


}

void stage_one(char *toCluster)
{
  
  int length_of_string=strlen(toCluster);
  for(int i=0;i<length_of_string-1;i++)
  {
    int flag=0;
    for(int j=0;j<length_of_string-1-i;j++)
    {
      if(compare_for_stage_one(toCluster[j], toCluster[j+1]))
        {
          char temp=toCluster[j+1];
          toCluster[j+1]=toCluster[j];
          toCluster[j]=temp;
          flag=1;
        }
    }
    if(!flag)
      break;
  }

}
void stage_two(char *toSort)
{

  int length_of_string=strlen(toSort);
  for(int i=0;i<length_of_string-1;i++)
  {
    int flag=0;
    for(int j=0;j<length_of_string-i-1;j++)
    {
      if(toSort[j] > toSort[j+1])
        {
          char temp=toSort[j+1];
          toSort[j+1]=toSort[j];
          toSort[j]=temp;
          flag=1;
        }
    }
    if(!flag)
      break;
  }
}

int compare_for_stage_one(char x,char y)
{
  if('0' <= x  && x <='9'   &&  '0' <= y  && y <='9')
    return 0;

  if('A' <= x  && x <='Z'   &&  'A' <= y  && y <='Z')
    return 0;

  if('0' <= x  && x <='9'   &&  'A' <= y  && y <='Z')
    return 0;

  return 1;

}
