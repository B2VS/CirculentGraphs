#include <bits/stdc++.h>

using namespace std;

int n_start = 14, n_end = 150;
int n, m = 7;
vector <int> DN(1000);
int combos = 0;

void findDN()
{
    for (n = n_start; n <= n_end; ++n)
    {
        DN[n] = 1 + (n - 1) / 5;
        if (n % 5 == 1 && n > 81) DN[n] += 2;
        else if (n % 5 >= 2 && n != 18 && n != 22 && n != 27) DN[n] += 1;
        else if (n == 21 || n == 41 || n == 46 || n == 51 || n == 56 || n == 61 || n == 66 ||
                 n == 71 || n == 76 || n == 81) DN[n] += 1;
    }
}

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

void findChildren(vector <bool> &ds, vector <int> &children)
{
    int i = cover(ds);
    if (!ds[(i - m + 8*n) % n])
        if (ds[(i - m + 8*n + 1) %n] || ds[(i - m + 8*n - 1) % n]) children.push_back((i - m + 8*n) % n + n);
        else children.push_back((i - m + 8*n) % n);
    if (!ds[(i - 1 + n) % n])
        if (ds[(i - 2 + n) % n]) children.push_back((i - 1 + n) % n + n);
        else children.push_back((i - 1 + n) % n);
    children.push_back(i);
    if (!ds[(i + 1) % n])
        if (ds[(i + 2) % n]) children.push_back((i + 1) % n + n);
        else children.push_back((i + 1) % n);
    if (!ds[(i + m) % n])
        if (!ds[(i + m + 1) % n] || !ds[(i + m - 1) % n]) children.push_back((i + m) % n + n);
        else children.push_back((i + m) % n);
    sort(children.begin(), children.end());
    for (int i = 0; i < children.size(); ++i)
        children[i] = (children[i] % n);
}

bool treeSearch(int dn, vector <bool> &ds)
{
    if (dn == 0) return cover(ds) == 0;
    vector <int> children;
    findChildren(ds, children);
    for (auto child: children)
    {
        ds[child] = true;
        if (treeSearch(dn - 1, ds)) return true;
        ds[child] = false;
    }
    return false;
}

bool predictStart2(vector <bool> &ds, int counter = 1, int pos = 0)
{
    if (pos == 0)
        for (int i = 0; i < n; ++i) ds[i] = false;
    ds[0] = true;
    if (counter == DN[n] || pos + 4 > n)
        return treeSearch(DN[n] - counter, ds);
    ds[pos + 5] = true;
    if (predictStart2(ds, counter + 1, pos + 5)) return true;
    ds[pos + 5] = false;
    ds[pos + 4] = true;
    if (predictStart2(ds, counter + 1, pos + 4)) return true;
    ds[pos + 4] = false;
    return false;
}

bool predictStart(vector <bool> &ds, int base = 0)
{
    if (base == 2 && predictStart2(ds)) return true;
    int i;
    for (i = 0; i < n - 5 * base; ++i)
        ds[i] = !(i%5);
    for (; i < n; ++i) ds[i] = false;
    return treeSearch(DN[n] - (n - 1) / 5 + base  - 1, ds);
}

int main()
{
    findDN();
    for (n = n_start; n <= n_end; ++n)
    {
        if (n % 5 == 1) cout << endl;
        cout << n << ". ";
        vector <bool> ds(n, false);
        for (int i = 0; !predictStart(ds, i); ++i);
        cout << DN[n] << " - ";
        for (int i = 0; i < n; ++i)
            if (ds[i]) cout << i << " ";
        cout << endl;
    }
}
