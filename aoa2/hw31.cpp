#include <bits/stdc++.h>
using namespace std;
vector <int> profs,astprofs,asts;
int journals=0,confs=0,works=0;
void init_graph(vector < vector < pair < int,int > > > &);
void print_graph(vector < vector < pair < int,int > > > &);
bool bfs(vector < vector < pair < int,int > > > &,int s,int t,vector <int> &);
void flow(vector < vector < pair < int,int > > > &,int s,int t);
int main()
{
  string reviewers,publications;
  reviewers="reviewer.txt";
  publications="publications.txt";
  ifstream inp(reviewers);

  int K;
  int capasity;
  string input_string;
  inp >> K;
  for(int i=0;i<K;i++)
  {
    inp >> input_string;
    inp >> capasity;
    if(input_string[0]=='P')
      profs.push_back(capasity);
    else if(input_string[3]=='P')
      astprofs.push_back(capasity);
    else
      asts.push_back(capasity);

  }

  inp.close();
  inp.open(publications,ifstream::in);

  inp >> K;
  for(int i=0;i<K;i++)
  {
    inp >> input_string;
    if(input_string[0]=='J')
      journals++;
    else if(input_string[0]=='C')
      confs++;
    else
      works++;

  }
  inp.close();

  vector <vector < pair < int,int > > > graph(K+profs.size()+astprofs.size()+asts.size()+2);
  init_graph(graph);
  int capacities[18][18]={0};
  for(int i=0;i<18;i++)
    for(int j=0;j<graph[i].size();j++)
      capacities[i][graph[i][j].first]=graph[i][j].second;





  return 0;
}


void init_graph(vector < vector < pair < int,int > > > & graph )
{
  //adding edges from source to professors
  for(int i=0;i<profs.size();i++)
  {
    graph[0].push_back(pair <int,int>(i+1,profs[i]));
    //cout <<graph[0][i].first<<'\t'<<graph[0][i].second<<endl;
  }
  //adding edges from source to ast.profs
  for(int i=0;i<astprofs.size();i++)
  {
    graph[0].push_back(pair <int,int> (graph[0].size()+1,astprofs[i]));
    //cout <<graph[0][graph[0].size()-1].first<<'\t'<<graph[0][graph[0].size()-1].second<<endl;
  }

  //adding edges from source to asistans
  for(int i=0;i<asts.size();i++)
  {

    graph[0].push_back(pair <int,int> (graph[0].size()+1,asts[i]));
    //cout <<graph[0][graph[0].size()-1].first<<'\t'<<graph[0][graph[0].size()-1].second<<endl;

  }
  int total_researchers=profs.size()+astprofs.size()+asts.size();
  //adding edges from profs to papers
  for(int i=0;i<profs.size();i++)
  {
    for(int j=0;j<journals+confs+works;j++)
      graph[i+1].push_back(pair <int,int> (total_researchers+j+1,1));

  }

  //adding edges from ast.profs to papers
  for(int i=0;i<astprofs.size();i++)
  {
    for(int j=journals;j<journals+confs+works;j++)
      graph[i+1+profs.size()].push_back(pair <int,int> (total_researchers+j+1,1));

  }
  //adding edges from asistans to papers
  for(int i=0;i<asts.size();i++)
  {
    for(int j=journals+confs;j<journals+confs+works;j++)
      graph[i+1+profs.size()+astprofs.size()].push_back(pair <int,int> (total_researchers+j+1,1));

  }



  int sinkId=graph.size()-1;
  //adding edges from journals to sink
  for(int i=0;i<journals;i++)
  {
    graph[total_researchers+1+i].push_back(pair <int, int> (sinkId,2));
  }

  for(int i=0;i<confs;i++)
  {
    graph[total_researchers+journals+i+1].push_back(pair <int,int> (sinkId,3));
  }
  for(int i=0;i<works;i++)
  {
    graph[sinkId-i-1].push_back(pair <int,int> (sinkId,2));
  }

}


void print_graph(vector < vector < pair < int,int > > > &graph)
{
  /*for(auto q=graph.begin();q!=graph.end();q++)
    for(auto w=q->begin(); w!=q->end(); w++)
        cout <<(*w).first <<'\t'<<(*w).second<<endl;*/

    for(int i=0;i<graph[13].size();i++)
      cout <<graph[13][i].first<<'\t'<<graph[13][i].second<<endl;




}
bool bfs(vector < vector < pair < int,int > > > &graph,int s,int t,vector <int > & path)
{
  path.clear();
  vector <bool> visited(journals+confs+works+2+profs.size()+astprofs.size()+asts.size(),false);
  queue <int> que;
  que.push(s);
  path.push_back(s);
  visited[s]=true;

  while(!que.empty())
  {
    int toque=que.front();
    que.pop();
    for(int i=0;i<graph[toque].size();i++)
    {

      if(!visited[graph[toque][i].first] && graph[toque][i].second > 0) //flow cond will be added. backtracking for path will be added
        {

          que.push(graph[toque][i].first);
          visited[graph[toque][i].first]=true;
          path.push_back(graph[toque][i].first);

        }
    }

  }

  return (visited[t] == true);


}

void flow(vector < vector < pair < int,int > > > &graph,int s,int t)
{
  //declaration tehlikeli!!
  vector < vector < pair < int, int > > > residualG(graph.size(), vector <pair <int,int > >(graph.size()));
  for(int i=0;i<graph.size();i++)
    for(int j=0;j<graph[i].size();j++)
      residualG[i][j]=graph[i][j];

  vector <int>  path;
  int max_flow=0;

  while(bfs(residualG,s,t,path))
  {
    cout <<s <<"\t"<<t<<endl;
    int path_flow=99999;
    int next_node;
    for(int i=0;i<path.size()-1;i++)
    {
      next_node=path[i+1];
      max_flow=min(path_flow,residualG[next_node][path[i]].second);
    }

    for(int i=0;i<path.size()-1;i++)
    {
      next_node=path[i+1];
      residualG[next_node][path[i]].second -= path_flow; // sıkıntı burada
      residualG[path[i]][next_node].second += path_flow;

    }
    max_flow +=path_flow;

  }
}
