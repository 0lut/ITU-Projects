#include <bits/stdc++.h>
using namespace std;
vector<int> profs, astprofs, asts;
int journals = 0, confs = 0, works = 0;
int V = 0;
int total_researchers;
void init_graph(vector<vector<pair<int, int>>> &);
void print_graph(vector<vector<pair<int, int>>> &);  // for debugging purposes
bool bfs(vector<vector<pair<int, int>>> &, int s, int t, vector<int> &,
         vector<vector<int>> &);
void flow(vector<vector<pair<int, int>>> &, int s, int t);
int main(int argc, char *argv[]) {
  string reviewers, publications;
  reviewers = argv[1];
  publications = argv[2];
  ifstream inp(reviewers);

  int K;
  int capasity;
  string input_string;
  inp >> K;
  for (int i = 0; i < K; i++) {
    inp >> input_string;
    inp >> capasity;
    if (input_string[0] == 'P')
      profs.push_back(capasity);
    else if (input_string[3] == 'P')
      astprofs.push_back(capasity);
    else
      asts.push_back(capasity);
  }

  inp.close();
  inp.open(publications, ifstream::in);

  inp >> K;
  for (int i = 0; i < K; i++) {
    inp >> input_string;
    if (input_string[0] == 'J')
      journals++;
    else if (input_string[0] == 'C')
      confs++;
    else
      works++;
  }
  inp.close();
  V = K + profs.size() + astprofs.size() + asts.size() + 2;
  vector<vector<pair<int, int>>> graph(V);
  init_graph(graph);
  flow(graph, 0, V - 1);

  return 0;
}

void init_graph(vector<vector<pair<int, int>>> &graph) {
  // adding edges from source to professors
  for (int i = 0; i < profs.size(); i++) {
    graph[0].push_back(pair<int, int>(i + 1, profs[i]));
    // cout <<graph[0][i].first<<'\t'<<graph[0][i].second<<endl;
  }
  // adding edges from source to ast.profs
  for (int i = 0; i < astprofs.size(); i++) {
    graph[0].push_back(pair<int, int>(graph[0].size() + 1, astprofs[i]));
    // cout
    // <<graph[0][graph[0].size()-1].first<<'\t'<<graph[0][graph[0].size()-1].second<<endl;
  }

  // adding edges from source to asistans
  for (int i = 0; i < asts.size(); i++) {
    graph[0].push_back(pair<int, int>(graph[0].size() + 1, asts[i]));
    // cout
    // <<graph[0][graph[0].size()-1].first<<'\t'<<graph[0][graph[0].size()-1].second<<endl;
  }
  total_researchers = profs.size() + astprofs.size() + asts.size();
  // adding edges from profs to papers
  for (int i = 0; i < profs.size(); i++) {
    for (int j = 0; j < journals + confs + works; j++)
      graph[i + 1].push_back(pair<int, int>(total_researchers + j + 1, 1));
  }

  // adding edges from ast.profs to papers
  for (int i = 0; i < astprofs.size(); i++) {
    for (int j = journals; j < journals + confs + works; j++)
      graph[i + 1 + profs.size()].push_back(
          pair<int, int>(total_researchers + j + 1, 1));
  }
  // adding edges from asistans to papers
  for (int i = 0; i < asts.size(); i++) {
    for (int j = journals + confs; j < journals + confs + works; j++)
      graph[i + 1 + profs.size() + astprofs.size()].push_back(
          pair<int, int>(total_researchers + j + 1, 1));
  }

  int sinkId = graph.size() - 1;
  // adding edges from journals to sink
  for (int i = 0; i < journals; i++) {
    graph[total_researchers + 1 + i].push_back(pair<int, int>(sinkId, 2));
  }

  for (int i = 0; i < confs; i++) {
    graph[total_researchers + journals + i + 1].push_back(
        pair<int, int>(sinkId, 3));
  }
  for (int i = 0; i < works; i++) {
    graph[sinkId - i - 1].push_back(pair<int, int>(sinkId, 2));
  }
}

void print_graph(vector<vector<pair<int, int>>> &graph) {
  /*for(auto q=graph.begin();q!=graph.end();q++)
    for(auto w=q->begin(); w!=q->end(); w++)
        cout <<(*w).first <<'\t'<<(*w).second<<endl;*/

  for (int i = 0; i < graph[13].size(); i++)
    cout << graph[13][i].first << '\t' << graph[13][i].second << endl;
}
bool bfs(vector<vector<pair<int, int>>> &graph, int s, int t, vector<int> &path,
         vector<vector<int>> &residualG) {
  vector<bool> visited(graph.size(), false);
  queue<int> que;
  que.push(s);
  visited[s] = true;

  while (!que.empty()) {
    int toque = que.front();
    que.pop();
    for (int i = 0; i < graph[toque].size(); i++) {
      if (!visited[graph[toque][i].first] &&
          residualG[toque][graph[toque][i].first] >
              0)  // if there is a path, i from to toque
      {
        que.push(graph[toque][i].first);
        path[graph[toque][i].first] = toque;
        visited[graph[toque][i].first] = true;
      }
    }
  }

  return visited[t];
}

void flow(vector<vector<pair<int, int>>> &graph, int s, int t) {
  vector<vector<int>> residualG(V, vector<int>(V, 0));
  for (int i = 0; i < V; i++)
    for (int j = 0; j < graph[i].size(); j++)
      residualG[i][graph[i][j].first] = graph[i][j].second;

  vector<int> path(graph.size(), 0);

  while (bfs(graph, s, t, path, residualG)) {
    int path_flow = 9999;
    int next_node;
    for (int i = t; i != s; i = path[i]) {
      next_node = path[i];
      path_flow =
          min(residualG[next_node][i],
              path_flow);  // finding the minimum flow to form augmenting path.
    }

    for (int i = t; i != s;
         i = path[i])  // iterating through path and augmenting paths
    {
      next_node = path[i];
      residualG[next_node][i] = residualG[next_node][i] - path_flow;
      residualG[i][next_node] = residualG[i][next_node] + path_flow;
    }
  }
  string outputMessage = "";
  bool flag = false;
  for (int i = total_researchers + 1; i < V - 1; i++) {
    if (i <= total_researchers + journals)
      outputMessage =
          "Journal " + to_string(i - total_researchers) + " is assigned to: ";
    else if (total_researchers + journals < i &&
             i <= total_researchers + journals + confs)
      outputMessage = "ConfProc" + to_string(i - total_researchers - journals) +
                      " is assigned to: ";
    else
      outputMessage = "WorkProc" +
                      to_string(i - total_researchers - journals - confs) +
                      " is assigned to: ";
    for (int j = 1; j < total_researchers + 1; j++) {
      if (residualG[i][j]) {
        flag = true;
        if (j <= profs.size())
          outputMessage += "Professor" + to_string(j) + ", ";
        else if (profs.size() < j && j <= profs.size() + astprofs.size())
          outputMessage += "AstProf" + to_string(j - profs.size()) + ", ";
        else
          outputMessage +=
              "Asistant" + to_string(j - profs.size() - astprofs.size()) + ", ";
      }
    }

    if (!flag)
      outputMessage = string(outputMessage, 0, 10) + " is not assigned";
    cout << outputMessage << endl;
    flag = false;
  }
}
