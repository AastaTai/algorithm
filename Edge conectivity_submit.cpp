// memory out of range
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    int V = 0;
    cin >> V;
    vector<int> graph[V]; // Adj list
    int connevtivity = V+1;

	int a, b;
	while(true){
        cin >> a >> b;
        //if(a==999) break;
        graph[a].push_back(b); // a to b
        graph[b].push_back(a); // b to a
	}

	// run Max Flow for v-1 times
	for(int i=1; i<V; i++){
        int rGraph[V][V];
        for(int n=0; n<V; n++){
            for(int m=0; m<V; m++){
                rGraph[n][m] = 0;// initialize have not been gone
            }
        }
        int maxFlow = 0;
        int parent[V];
        bool BFS = true;

        while(BFS){
            BFS = false;
            bool visit[V];
            for(int n=0; n<V; n++){
                visit[n] = false; //initialize not visit
                parent[n] = -1; //initialize no parent
            }
            queue<int> q;
            // do BFS
            q.push(0);
            visit[0] = true;
            while (!q.empty() && !BFS) {
                int u = q.front();
                q.pop();

                for (int v = 0; v < graph[u].size(); v++) { // run the neighbor
                    if (visit[graph[u][v]] == false && rGraph[u][graph[u][v]] == 0) {
                        parent[graph[u][v]] = u;
                        visit[graph[u][v]] = true;
                        if (graph[u][v] == i) {
                            BFS = true;
                            break;
                        }
                        q.push(graph[u][v]);
                    }
                }
            }
            if(BFS){ // calculate max flow
                maxFlow += 1;
                for(int j = i; j != 0; j = parent[j]){
                    rGraph[parent[j]][j] = 1; // have been gone
                }
            }
        }
        //cout << "The maximum possible flow is " << maxFlow << endl;
        if(connevtivity > maxFlow) connevtivity = maxFlow; // choose the smallest
	}
    cout << connevtivity << endl;
    return 0;
}
