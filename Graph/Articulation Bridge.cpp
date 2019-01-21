// LightOJ 1026 - Critical Links

#include <bits/stdc++.h>
using namespace std;
#define repit(it, x)  for(__typeof__((x).begin()) it = (x).begin(); it != (x).end(); ++it)
#define rep(i, begin, end) for (__typeof(end) i = (begin); i < (end); i += 1)
#define all(a)        a.begin(), a.end()
#define mxn           100010


vector<int> adj[mxn];
bool vis[mxn];
int parent[mxn], dis[mxn], low[mxn], tym = 0;
vector< pair<int, int> > bridge;


void ArticulationBridge(int u) //finds articulation bridges
{
    vis[u] = true;
    low[u] = dis[u] = ++tym;

    repit(it, adj[u])
    {
        int v = *it;
        if(parent[u] == v){
            continue;
        }
        if(vis[v]){ //back edge
            low[u] = min(low[u], dis[v]);
        }
        if(!vis[v]){
            parent[v] = u;
            ArticulationBridge(v);
            low[u] = min(low[u], low[v]);

            if(dis[u]<low[v]){ //u-v is an articulation bridge
                bridge.push_back({min(u, v), max(u, v)});
            }
        }
    }
}


void solve(int tc)
{
    int n, u, v, k;
    scanf("%d", &n);

    rep(i, 0, n){
        scanf("%d (%d)", &u, &k);
        rep(j, 0, k){
            scanf("%d", &v);
            adj[u].push_back(v);
        }
    }

    rep(i, 0, mxn) vis[i] = false, parent[i] = -1;

    tym = 0;
    rep(i, 0, n){
        if(!vis[i]){
            ArticulationBridge(i);
        }
    }

    sort(all(bridge));

    int sz = bridge.size();

    printf("Case %d:\n", tc);
    printf("%d critical links\n", sz);

    rep(i, 0, sz) printf("%d - %d\n", bridge[i].first, bridge[i].second);

    rep(i, 0, n) adj[i].clear();
    bridge.clear();
}

int32_t main()
{
    int tc; cin>>tc; rep(t, 1, tc+1) solve(t);

    return 0;
}
