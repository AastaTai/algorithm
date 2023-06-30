// https://github.com/ajahuang/UVa/blob/master/UVa%20796%20-%20Critical%20Links.cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static const int Unvisited = -1;

vector<vector<int>> network; // memorize the graph
// for dfs
vector<int> dfsParent;
vector<int> dfsNum;
vector<int> dfsLow;
int dfsCount = 1;
// bridge
vector<pair<int, int>> bridge;


// DFS function
void DFS(int u){
    dfsNum[u] = dfsLow[u] = dfsCount++;
    for(int i=0; i<network[u].size(); i++){
        int v = network[u][i];
        if(dfsNum[v] == Unvisited){
            dfsParent[v] = u;
            DFS(v);
            if(dfsLow[v] > dfsLow[u]){ // v can't reach u
                bridge.push_back(make_pair(min(u,v), max(u,v)));
            }
            dfsLow[u] = min(dfsLow[u], dfsLow[v]);
        }
        else if(v != dfsParent[u]){
            dfsLow[u] = min(dfsLow[u], dfsNum[v]);
        }
    }
}

int main(){
    int n = 0;
    cin >> n;

    //initialize
    network.clear();
    network.resize(n);
    dfsParent.clear();
    dfsParent.resize(n, Unvisited);
    dfsNum.clear();
    dfsNum.resize(n, Unvisited);
    dfsLow.clear();
    dfsLow.resize(n, Unvisited);
    bridge.clear();

    int u, v;
    while(cin >> u >> v){ // how to do EOF
        network[u].push_back(v);
        network[v].push_back(u);
    }

    for(int i=0; i<n; i++){
        if(dfsNum[i] == Unvisited){
            DFS(i);
        }
    }

    sort(bridge.begin(), bridge.end());
    //cout << bridge.size() << endl;
    for(int i=0; i<bridge.size(); i++){
        cout << bridge[i].first << " " << bridge[i].second << endl;
    }
    return 0;
}

/*
14
0 1
0 6
0 5
1 2
1 6
1 7
2 7
2 3
3 4
4 5
6 8
8 9
9 10
8 10

*/
