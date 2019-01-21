
// LightOJ 1003 - Drunk

#include <bits/stdc++.h>
using namespace std;
#define repit(it, x)  for(__typeof__((x).begin()) it = (x).begin(); it != (x).end(); ++it)
#define rep(i, begin, end) for (__typeof(end) i = (begin); i < (end); i += 1)
#define mxn           10010

vector<int> adj[mxn];
int parent[mxn];
bool vis[mxn], inStack[mxn], isCycle = false;

void dfs(int u)
{
    vis[u] = true;
    inStack[u] = true; // u is now pushed into the dfs stack

    repit(it, adj[u]){
        int v = *it;
        if(!vis[v]){
            parent[v] = u; // parent[] is needed only for immediate next "else if"
            dfs(v);
        }
        //else if(parent[u] == v){ ///if this "else if" is present then, "1 -> 2 = 3" graph does not contain any cycle
        //    continue; //why this else if is commented here? ::Answer:: See 2nd sample test case [LightOJ 1003 - Drunk]
        //}
        else if(inStack[v]){ //if previous "else if" is not present then, "1 -> 2 = 3" graph contains a cycle[because of (2 = 3) edge]
            isCycle = true;
        }
    }

    inStack[u] = false;
}


void solve(int tc)
{
    int m, n = 0; cin>>m;
    map<string, int> idx;

    string u, v;
    rep(i, 0, m){
        cin>>u>>v;
        if(idx.find(u) == idx.end()) idx[u] = n++;
        if(idx.find(v) == idx.end()) idx[v] = n++;
        adj[idx[u]].push_back(idx[v]);
    }

    cout<<"Case "<<tc<<": ";

    rep(i, 0, mxn) parent[i] = -1, vis[i] = inStack[i] = false;

    rep(i, 0, n){
        isCycle = false;
        dfs(i);
        if(isCycle) break;
    }

    if(isCycle) cout<<"No"<<endl;
    else cout<<"Yes"<<endl;

    rep(i, 0, n) adj[i].clear();
    idx.clear();
}

int32_t main()
{
    int tc; cin>>tc; rep(t, 1, tc+1) solve(t);

    return 0;
}
