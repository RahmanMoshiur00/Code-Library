
// LightOJ 1041	- Road Construction

#include <bits/stdc++.h>
using namespace std;
#define repit(it, x)  for(__typeof__((x).begin()) it = (x).begin(); it != (x).end(); ++it)
#define perit(it, x)  for(__typeof__((x).rbegin()) it = (x).rbegin(); it != (x).rend(); ++it)
#define rep(i, begin, end) for(int i = (begin); i < (end); ++i)
#define per(i, end, begin) for(int i = (end)-1; i >= (begin); --i)
#define mem(a, v)     for(int i=0, sz=sizeof(a)/sizeof(*a); i<sz; i++){ a[i] = v; }
#define INF           1000000007
#define mxn           55


vector<pair<int, int> > adj[mxn];
bool vis[mxn];
int key[mxn];

int prim(int s) //prim algo finds mst of the component where s(source) node is in
{
    mem(vis, false);
    mem(key, INF);
    key[s] = 0;

    priority_queue<pair<int, int> > pq;
    pq.push({key[s], s});

    int res = 0;
    while(!pq.empty()){
        pair<int, int> p = pq.top(); pq.pop();
        int cost = -p.first, u = p.second;

        if(vis[u]) continue; // u is already taken in the MST
        vis[u] = true; // adding u to the mst
        res += cost;  // cost for adding node u to the mst

        repit(it, adj[u]){
            int v = it->first, w = it->second;
            if(!vis[v] and key[v]>w){
                key[v] = w;
                pq.push({-key[v], v});
            }
        }
    }

    return res;
}

void solve(int tc)
{
    int m, u, v, w;
    cin>>m;

    string su, sv;
    map<string, int> mp;

    int node = 0;
    rep(i, 0, m){ // edge input
        cin>>su>>sv>>w;

        if(mp.find(su) == mp.end()) mp[su] = node++;
        if(mp.find(sv) == mp.end()) mp[sv] = node++;

        u = mp[su], v = mp[sv];

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int mst = prim(0); //finds mst of the component where 0 node is present

    bool impossible = false;
    rep(i, 0, node){ // if more than one component is present, then answer is not possible
        if(!vis[i]){
            impossible = true;
            break;
        }
    }

    cout<<"Case "<<tc<<": ";
    if(impossible) cout<<"Impossible"<<endl;
    else cout<<mst<<endl;

    rep(i, 0, node) adj[i].clear();
}

int32_t main()
{
    int tc; cin>>tc; rep(t, 1, tc+1) solve(t);
    return 0;
}
