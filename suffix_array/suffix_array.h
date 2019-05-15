#ifndef __SUFFIX_ARRAY_H__
#define __SUFFIX_ARRAY_H__

struct node {
    int index;
    int rank[2];
};
 
bool cmp(const node &a, const node &b) {
    if(a.rank[0] != b.rank[0]) return a.rank[0] < b.rank[0];
    if(a.rank[1] != b.rank[1]) return a.rank[1] < b.rank[1];
    return a.index < b.index;
}
 
vector<int> quickSortSuffix(vector<int> &r) {
    int n = r.size();
    vector<node> a(n);
    for(int i=0; i<n; i++){
        a[i].index = i;
        a[i].rank[0] = r[i];
        a[i].rank[1] = i<n-1?r[i+1]:-1;
    }
    sort(a.begin(), a.end(), cmp);
    vector<int> ind(n);
    for(int k = 2; k<n; k*=2) {
        int rank = 0;
        int pre_rank = a[0].rank[0];
        a[0].rank[0] = 0;
        ind[a[0].index] = 0;
        for(int i=1; i<n; i++) {
            if(pre_rank == a[i].rank[0] && a[i-1].rank[1] == a[i].rank[1]) {
                pre_rank = a[i].rank[0];
                a[i].rank[0] = rank;
            } else {
                pre_rank = a[i].rank[0];
                a[i].rank[0] = ++rank;
            }
            ind[a[i].index] = i;
        }
        if(rank == n)break;
        
        for(int i = 0; i<n; i++){
            int j = a[i].index;
            if(j+k<n){
                j = ind[j+k];
                a[i].rank[1] = a[j].rank[0];
            } else {
                a[i].rank[1] = -1;
            }
        }
        sort(a.begin(), a.end(), cmp);
    }
    vector<int> sa(n);
    for(int i = 0; i<n; i++)sa[i] = a[i].index;
    return sa;
}
 
vector<int> radixSuffix(vector<int> &r, int m) {
    // m large elements in array r and large than or equal r.size()
    // m = max(m, r.size())
    int n = r.size();
    vector<int> count(m, 0); // radix sort count array
    vector<int> wv(r); // keyword value
    vector<int> sa(n); // suffix array : sa[i] means the ith rank element's index is sa[i]
    vector<int> rank(n); // rank array: rank[i] the rank of ith element is rank[i]
    // size 1 suffix radix sort
    for(int i = 0; i<n; i++) {
        rank[i] = wv[i];
        count[wv[i]]++;
    }
    for(int i = 1; i<m; i++) count[i]+=count[i-1];
    for(int i = n-1; i>=0; i--) sa[--count[wv[i]]] = i;
    vector<int> second_sa(n); // suffix array by second key word
    vector<int> new_rank(n); // store new_rank
    auto cmp = [&](int a, int b, int l) {
        if(rank[a]!=rank[b]) return false;
        if(a+l>=n && b+l>=n) return true;
        if(a+l>=n || b+l>=n) return false;
        return rank[a+l] == rank[b+l];
    };
    for(int p = 0, j = 1; p<n; j*=2, m=p)
    {
        // second key word sort
        p = 0;
        for(int i = n-j; i<n; i++)second_sa[p++] = i;
        for(int i = 0; i<n; i++)if(sa[i]>=j)second_sa[p++] = sa[i]-j;
        // first keyword sort
        for(int i = 0; i<m; i++)count[i] = 0;
        for(int i = 0; i<n; i++)wv[i] = rank[second_sa[i]];
        for(int i = 0; i<n; i++)count[wv[i]]++;
        for(int i = 1; i<m; i++)count[i]+=count[i-1];
        for(int i = n-1; i>=0; i--)sa[--count[wv[i]]] = second_sa[i];
        new_rank[sa[0]] = 0;
        p = 1;
        for(int i = 1; i<n; i++)
        {
            new_rank[sa[i]] = cmp(sa[i-1], sa[i], j)?p-1:p++;
        }
        rank.swap(new_rank);
    }
    return sa;
}
 
vector<int> calcHeight(vector<int> &sa, vector<int> &r)
{
    int n = sa.size();
    vector<int> height(n);
    vector<int> rank(n);
    for(int i = 0; i<n; i++)rank[sa[i]] = i;
    int k = 0;
    for(int i = 0; i<n; i++){
        int cur = rank[i];
        if(cur == 0) {
            height[cur] = 0;
            k = 0;
        } else {
            if(k>0)k--;
            int j = sa[cur-1];
            while(i+k<n && j+k<n && r[i+k] == r[j+k])k++;
            height[cur] = k;
        }
    }
    return height;
}
 
class Solution {
public:
    string longestDupSubstring(string S) {
        int n = S.size();
        if(n==0) return "";
        vector<int> r(n);
        for(int i = 0; i<n; i++)r[i] = S[i]-'a';
        auto ret = radixSuffix(r, max(n+1, 27));
        auto height = calcHeight(ret, r);
        int ans = 0, ans_index = 0;
        for(int i = 1; i<n; i++){
            if(height[i] > ans) {
                ans_index = i;
                ans = height[i];
            }
        }
        if(ans == 0) return "";
        return S.substr(ret[ans_index], ans);
    }
#endif
