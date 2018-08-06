#include <bits/stdc++.h>

using namespace std;

int n_start = 3, n_end = 50;
int m = 4;
int n;

int cover(vector <bool> &ds)
{
    vector <bool> graph(n, false);
    for (int i = 0; i < n; ++i)
        if (ds[i])
        {
            graph[(i - m + 8*n) % n] = true;
            graph[(i - 1 + n) % n] = true;
            graph[i] = true;
            graph[(i + 1) % n] = true;
            graph[(i + m) % n] = true;
        }
    for (int i = 0; i < n; ++i)
        if (graph[i] == false) return i;
    return 0;
}

bool check(int dn, vector <bool> &ds, int pos = 1)
{
    if (dn == 0) return cover(ds) == 0;
    for (int i = pos; n - i >= dn - 1; ++i)
    {
        ds[i] = true;
        if (check(dn - 1, ds, i + 1)) return true;
        ds[i] = false;
    }
    return false;
}

void findChildren(vector <bool> &ds, vector <int> &children)
{
    int i = cover(ds);
    if (!ds[(i - m + 8*n) % n]) children.push_back((i - m + 8*n) % n);
    if (!ds[(i - 1 + n) % n]) children.push_back((i - 1 + n) % n);
    children.push_back(i);
    if (!ds[(i + 1) % n]) children.push_back((i + 1) % n);
    if (!ds[(i + m) % n]) children.push_back((i + m) % n);
    sort(children.begin(), children.end());
}

bool check2(int dn, vector <bool> &ds)
{
    if (dn == 0) return cover(ds) == 0;
    vector <int> children;
    findChildren(ds, children);
    /*cout << endl;
    for (int i = 0; i < dn; ++i)
        cout << " ";
    for (int i = 0; i < children.size(); ++i)
        cout << children[i] << " ";*/
    for (auto child: children)
    {
        ds[child] = true;
        if (check2(dn - 1, ds)) return true;
        ds[child] = false;
        //cout << endl;
    }
    return false;
}

bool fastSearch(int dn, vector <bool> &ds, int pos = 1)
{
    if (dn == 0) return cover(ds) == 0;
    for (int i = pos; i + dn < n; ++i)
    {
        if (ds[i]) continue;
        ds[i] = true;
        if (fastSearch(dn - 1, ds, pos + 1)) return true;
        ds[i] = false;
    }
    return false;
}

int main()
{
    for (n = n_start; n <= n_end; ++n)
    {
        if (n % 5 == 1) cout << endl;
        cout << n << ". ";
        int dn = 1 + (n - 1) / 5;
        vector <bool> ds(n, false);
        for (; ; ++dn)
        {
            //for (int i = 0; i < n; ++i)
            //    ds[i] = !(i % 5);
            //if (fastSearch(dn - (n - 1) / 5 - 1, ds, 1)) break;

            for (auto ele: ds) ele = false;
            ds[0] = true;
            if (check2(dn - 1, ds)) break;
        }
        cout << dn << " - ";
        for (int i = 0; i < n; ++i)
            if (ds[i]) cout << i << " ";
        cout << endl;
    }
}
