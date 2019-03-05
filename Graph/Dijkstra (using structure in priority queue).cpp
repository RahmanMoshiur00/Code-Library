
// LightOJ 1099 - Not the Best
// finding second best path

#include <bits/stdc++.h>
using namespace std;

#define INF           1000000007
#define mxn           5010

vector< pair<int,int> > adj[mxn];
bool vis[2][mxn];
int dist[2][mxn];

struct node{
    int t, w, u;
    node(int _t, int _w, int _u){
        t = _t, w = _w, u = _u;
    }
};

bool operator<(node a, node b){ // decides which element is the bottom element of priority queue(min priority queue)
    if(a.t != b.t) return a.t > b.t;
    if(a.w != b.w) return a.w > b.w;
    if(a.u != b.u) return a.u > b.u;
}

void dijkstra(int source)
{
    for(int i=0; i<mxn; i++){
        dist[0][i] = dist[1][i] = INF;
        vis[0][i] = vis[1][i] = false;
    }

    priority_queue< node > pq;
    dist[0][source] = 0;
    pq.push(node(0, dist[0][source], source));

    while(!pq.empty()){
        node nd = pq.top(); pq.pop();
        int t = nd.t, w = nd.w, u = nd.u;

        if(vis[t][u]) continue;
        else vis[t][u] = true;

        for(int i=0; i<adj[u].size(); i++){
            int v = adj[u][i].first , w = adj[u][i].second;

            int val = dist[t][u] + w;

            if(val < dist[0][v]){
                dist[1][v] = dist[0][v];
                pq.push(node(1, dist[1][v], v));

                dist[0][v] = val;
                pq.push(node(0, dist[0][v], v));
            }
            else if(val>dist[0][v] and val<dist[1][v]){ // use (val>=dist[0][v] and val<dist[1][v]) if second shortest path value can have same weight(in case of several shortest paths exist) of the shortest path
                dist[1][v] = val;
                pq.push(node(1, dist[1][v], v));
            }
        }
    }
}

void solve(int tc)
{
    int n, m, u, v, w;
    cin>>n>>m;

    for(int i=0; i<m; i++){
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    // http://lbv-pc.blogspot.com/2012/06/not-best.html

    dijkstra(1);

    cout<<"Case "<<tc<<": "<<dist[1][n]<<endl;

    for(int i=0; i<mxn; i++) adj[i].clear();
}

int32_t main()
{
    int tc; cin>>tc;
    for(int t=1; t<=tc; t++) solve(t);

    return 0;
}
