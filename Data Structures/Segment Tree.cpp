/*
    Problem: Codeforces 915E - Physical Education Lessons
    Category: Segment Tree
*/

#include <bits/stdc++.h>
using namespace std;


const int mxn = 300010;

int query[mxn][3], tmp[2*mxn];

struct Array
{
    int l, r;
} arr[2*2*mxn]; // depending on this array, segment-tree is built

struct tree
{
    int l, r, val, lazy;
} seg[4*2*2*mxn]; // segment-tree (size = 4x, where 'x' is the size of array depending on which segment-tree will be built)


void build(int ind, int l, int r)
{
    if(l == r){
        seg[ind].l = arr[l].l;
        seg[ind].r = arr[l].r;
        seg[ind].val = seg[ind].r - seg[ind].l + 1;
        seg[ind].lazy = -1;
        return;
    }

    int mid = (l+r) >> 1;
    int left = ind << 1;
    int right = ind << 1 | 1;

    build(left, l, mid);
    build(right, mid+1, r);

    seg[ind].l = seg[left].l;
    seg[ind].r = seg[right].r;
    seg[ind].val = seg[ind].r - seg[ind].l + 1;
    seg[ind].lazy = -1;
}

void propagate(int ind, int l, int r) // propagation function
{
    if(seg[ind].lazy == -1) return;

    int left = ind << 1;
    int right = ind << 1 | 1;

    seg[ind].val = (seg[ind].lazy == 1) ? 0 : seg[ind].r - seg[ind].l + 1;

    if(l != r) seg[left].lazy = seg[right].lazy = seg[ind].lazy;

    seg[ind].lazy = -1;
}

void update(int ind, int l, int r, int ql, int qr, int op)
{
    if(seg[ind].lazy != -1) propagate(ind, l, r); // if current node has lazy value, we need to propagate

    if(seg[ind].l>=ql && seg[ind].r<=qr){
        seg[ind].lazy = op;
        propagate(ind, l, r);
        return;
    }

    int mid = (l+r) >> 1;
    int left = ind << 1;
    int right = ind << 1 | 1;

    //updating only required segment(s)
    if(ql <= seg[left].r) update(left, l, mid, ql, qr, op);
    if(qr >= seg[right].l) update(right, mid+1, r, ql, qr, op);

    //as, we're updating current node based on both the left and right child, we need to check if both of them has lazy value
    if(seg[left].lazy != -1) propagate(left, l, mid);
    if(seg[right].lazy != -1) propagate(right, mid+1, r);

    seg[ind].val = seg[left].val + seg[right].val;
}

void solve(int tc)
{
    int n, q; scanf("%d %d", &n, &q);

    int cnt = 0;
    for(int i=1; i<=q; i++){
        scanf("%d %d %d", &query[i][0], &query[i][1], &query[i][2]);
        tmp[++cnt] = query[i][0];
        tmp[++cnt] = query[i][1];
    }

    tmp[++cnt] = 1;
    tmp[++cnt] = n;

    sort(tmp+1, tmp+1+cnt);

    cnt = unique(tmp+1, tmp+1+cnt) - (tmp+1);

    int total = 0;
    for(int i=1; i<=cnt; i++){
        if(tmp[i] - tmp[i-1] > 1){ // if gap between two segment is greater then 1, then we need to store the gap as another segment in the segment tree
                                   // for example, 1 2 5; our leaf segments in the segment tree will be (1,1), (2,2), (3,4), (5,5)
            arr[++total].l = tmp[i-1] + 1;
            arr[total].r = tmp[i] - 1;
        }
        arr[++total].l = tmp[i];
        arr[total].r = tmp[i];
    }

    build(1, 1, total);

    for(int i=1; i<=q; i++){
        int l = query[i][0];
        int r = query[i][1];
        int op = query[i][2];

        update(1, 1, total, l, r, op);

        printf("%d\n", seg[1].val);
    }
}

int32_t main()
{
    solve(1);

    return 0;
}
