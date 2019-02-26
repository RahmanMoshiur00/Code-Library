
// LightOJ 1210 - Efficient Traffic System  // How to make a directed graph connected, adding minimum edges

#include <bits/stdc++.h>
using namespace std;

#define mxn 100010

vector<int> adj[mxn]; // actual graph
vector<int> trans[mxn]; // transpose graph
stack<int> stk; // holds greatest finishing time nodes in top and least in the bottom
int scc[mxn]; // scc[i] denotes the scc number of node i
int scc_count = 0; // counts total number of scc's
bool vis[mxn]; // visited checker

void dfs(int u)
{
    vis[u] = true;
    for(int i=0, sz = adj[u].size(); i<sz; i++){
        int v = adj[u][i];
        if(!vis[v]) dfs(v);
    }
    stk.push(u);
}

void dfs_scc(int u)
{
    scc[u] = scc_count;
    vis[u] = true;
    for(int i=0, sz = trans[u].size(); i<sz; i++){
        int v = trans[u][i];
        if(!vis[v]) dfs_scc(v);
    }
}

void scc_calculation(int n)
{
    memset(vis, false, sizeof vis);
    for(int i=0; i<n; i++){
        if(!vis[i]) dfs(i);
    }

    scc_count = 0; // counts total number of scc's
    memset(vis, false, sizeof vis);
    while(!stk.empty()){
        int u = stk.top(); stk.pop();
        if(!vis[u]){
            dfs_scc(u);
            scc_count++;
        }
    }
}

int main()
{
    int n, m, u, v;
    cin>>n>>m;

    for(int i=0; i<m; i++){
        cin>>u>>v;
        // directed (u -> v)
        adj[u].push_back(v);
        trans[v].push_back(u);
    }

    scc_calculation(n); // finds all scc for all n nodes

    for(int i=0; i<n; i++) adj[i].clear(), trans[i].clear();
}
