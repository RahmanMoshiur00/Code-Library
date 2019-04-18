/*
Tutorial: https://www.hackerearth.com/practice/notes/mos-algorithm/

-->To apply Mo’s algorithm, you must ensure of three properties:
    1. Array is not modified by queries (i.e. offline query)
    2. Queries are known beforehand
    3. If you know V([L, R]), then you can compute V([L + 1, R]), V([L - 1, R]), V([L, R - 1]) and V([L, R + 1]), each in O(F) time.
*/

// Problem: LightOJ 1188 - Fast Queries, SPOJ - DQUERY

#include <bits/stdc++.h>
using namespace std;
#define int           long long
#define rep(i, begin, end) for(int i = (begin), ed = (end); i < (ed); ++i)



#define mxn           100010 // max size of the input array
#define mxq           50010 // max no. of Query
#define mxv           100010 // max value of the input element

const int block_size = 746;
int arr[mxn]; // input array
int ans[mxq]; // holds required answer for i'th query

struct Query
{
    int l, r, id;
    Query() {}
    Query(int _l, int _r, int _id){
        l = _l, r = _r, id = _id;
    }

    bool operator<(Query b) // MO's sorting order
    {
        if(l/block_size == b.l/block_size) return r < b.r;
        return l/block_size < b.l/block_size;
    }
};

struct MOs // Change this structure as required in the problem
{
    int data[mxv]; // mxv: max value of the input array element
    int answer;

    MOs(){
        memset(data, 0, sizeof data);
        answer = 0;
    }

    void add(int v){
        if(data[v] == 0) answer++;
        data[v]++;
    }
    void remove(int v){
        data[v]--;
        if(data[v]==0) answer--;
    }
    int solution(){
        return answer;
    }
};

void solve(int tc)
{
    /*
        this solve() block remains same almost for all problems of MO's algorithm
    */

    int n, q, l, r;
    scanf("%lld %lld", &n, &q); // n: number of elements, q: number of query

    rep (i, 0, n) scanf("%lld", &arr[i]); // input array

    vector< Query > vq(q);
    rep (i, 0, q) {
        scanf("%lld %lld", &l, &r); // query input
        l--, r--;
        vq[i] = Query(l, r, i);
    }

    sort(vq.begin(), vq.end()); // queries are sorted in MO's order

    MOs result;

    int mo_left = 0, mo_right = -1;
    rep (i, 0, q) {
        int left = vq[i].l;
        int right = vq[i].r;

        while(mo_right < right){
            mo_right++;
            result.add(arr[mo_right]);
        }
        while(mo_right > right){
            result.remove(arr[mo_right]);
            mo_right--;
        }

        while(mo_left < left){
            result.remove(arr[mo_left]);
            mo_left++;
        }
        while(mo_left > left){
            mo_left--;
            result.add(arr[mo_left]);
        }

        ans[vq[i].id] = result.solution();
    }

    rep(i, 0, q) printf("%lld\n", ans[i]);
}

int32_t main()
{
    int tc; cin>>tc;
    rep(t, 1, tc+1){
        cout<<"Case "<<t<<":\n";
        solve(t);
    }

    return 0;
}
