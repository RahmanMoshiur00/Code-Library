
// LightOJ 1063 - Ant Hills

#include <bits/stdc++.h>
using namespace std;
#define repit(it, x)  for(__typeof__((x).begin()) it = (x).begin(); it != (x).end(); ++it)
#define rep(i, begin, end) for (__typeof(end) i = (begin); i < (end); i += 1)
#define mxn           10010


vector<int> adj[mxn];
int parent[mxn], dis[mxn], low[mxn], tym = 0, artiPoint = 0;
bool vis[mxn], isArtiPoint[mxn];


void ArticulationPoint(int u) //finds articulation points
{
    vis[u] = true;
    low[u] = dis[u] = ++tym;

    int children = 0;

    repit(it, adj[u]){
        int v = *it;
        if(v == parent[u]) continue;
        if(vis[v]) low[u] = min(low[u], dis[v]);
        if(!vis[v]){
            parent[v] = u;
            ArticulationPoint(v);
            low[u] = min(low[u], low[v]);
            children++;

            if(parent[u]!=-1 and dis[u]<=low[v]){ //u is not root and u is an articulation point
                if(!isArtiPoint[u]){ //if u is not already found as articulation point
                    isArtiPoint[u] = true;
                    artiPoint++;
                }
            }
        }
        if(parent[u]==-1 and children>1){ //as, u is root and it has at least 2 children; u is an articulation point
            if(!isArtiPoint[u]){ //if u is not already found as articulation point
                isArtiPoint[u] = true;
                artiPoint++;
            }
        }
    }
}

void solve(int tc)
{
    int n, m, u, v;
    scanf("%d %d", &n, &m);

    rep(i, 0, m){
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    rep(i, 0, n+1) vis[i] = isArtiPoint[i] = false, parent[i] = -1;

    tym = artiPoint = 0;
    ArticulationPoint(1);

    printf("Case %d: %d\n", tc, artiPoint);
    rep(i, 0, n+1) adj[i].clear();
}

int32_t main()
{
    int tc; cin>>tc; rep(t, 1, tc+1) solve(t);

    return 0;
}
