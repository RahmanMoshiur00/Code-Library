#include <bits/stdc++.h>
using namespace std;

#define INF           1000000007
#define mxn           100010


vector< pair<int, pair<int, int> > > edge; // stores edges
vector<int> adj[mxn]; // forms graph to run dfs_bellmanFord()
int dist[mxn]; // dist[i] is the minimum possible distance for node i from source node
int n, m; // n - number of nodes, m - number of edges
bool vis[mxn];


void dfs_bellmanFord(int u) // sets vis[i]=true for all i nodes reachable from source node
{
    vis[u] = true;
    for(int i=0, sz=adj[u].size(); i<sz; i++){
        int v = adj[u][i];
        if(!vis[v]) dfs_bellmanFord(v);
    }
}
void bellmanFord(int source)
{
    memset(vis, false, sizeof vis);
    dfs_bellmanFord(source); // sets vis[i]=true for all i nodes reachable from source node

    for(int i=0; i<mxn; i++) dist[i] = INF;
    dist[source] = 0;

    for(int i=0; i<n-1; i++){
        bool relaxed = false;
        for(int j=0, sz=edge.size(); j<sz; j++){
            int u = edge[j].first, v = edge[j].second.first, w = edge[j].second.second;
            if(vis[u]==true and dist[u]+w<dist[v]){
                // why checking (vis[u]==true) : if u can be reached by source, only then u->v edge can be relaxed
                // what happens if (vis[u]==true) is not checked: if an edge x->y with negative weight w and x can't be reached from source, but x-y will be relaxed, which is wrong... e.g. LightOJ 1074
                dist[v] = dist[u] + w;
                relaxed = true;
            }
        }
        if(!relaxed) return;
    }

    bool cycleFound = false;
    for(int j=0, sz=edge.size(); j<sz; j++){
        int u = edge[j].first, v = edge[j].second.first, w = edge[j].second.second;
        if(vis[u]==true and dist[u]+w<dist[v]){
            // why checking (vis[u]==true) : if u can be reached by source, only then u->v edge can be relaxed
            // what happens if (vis[u]==true) is not checked: if an edge x->y with negative weight w and x can't be reached from source, but x-y will be relaxed, which is wrong... e.g. LightOJ 1074
            dist[v] = dist[u] + w;
            cycleFound = true; // cycle is found which is reachable from source node
        }
    }

    //do anything based on cycleFound value
}



int main()
{
    //build graph

    //call bellmanFord(source);
}
