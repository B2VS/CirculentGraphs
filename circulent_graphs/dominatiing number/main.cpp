#include <bits/stdc++.h>

using namespace std;

vector <int> best_set;
int domin = 100, limit, n, m;

bool check(vector <bool> graph, int last)
{
    vector <bool> graph2(n);
    for (int i = 0; i <= last; ++i)
    {
        if (graph[i])
        {
            graph2[i] = true;
            graph2[(i + 1) % n] = true;
            graph2[(i - 1 + n) % n] = true;
            graph2[(i - m + n) % n] = true;
            graph2[(i + m) % n] = true;
        }
    }
    for (int i = 0; i < n; ++i)
        if (!graph2[i])
            return false;
    return true;
}

void cover(vector <bool> graph, int node, int num)
{
    graph[node] = true;
    num += 1;
    if (check(graph, node))
    {
        if (num < domin)
        {
            domin = num;
            best_set.clear();
            for (int i = 0; i < graph.size(); ++i)
                if (graph[i]) best_set.push_back(i);
        }
        /*if (num == domin)
        {
            vector <int> x;
            for (int i = 0; i <= node; ++i)
                if (graph[i])
                    x.push_back(i);
            best_sets.push_back(x);
        }*/
        return;
    }
    if (num == limit)
        return;
    for (int i = node + 1; i < n; ++i)
        cover(graph, i, num);
}

int main()
{
    int first;
    int n1 = 3;
    int n2 = 30;
    m = 3;
    limit = 8;
    for (n = n1; n <= n2; ++n)
    {
        vector <bool> graph(n);
        graph[0] = true;
        for (int i = 1; i < n; ++i)
            cover(graph, i, 1);
        /*for (auto dset: best_sets)
        {
            for (auto ele: dset)
                cout << ele << " ";
            cout << endl;
        }*/
        if (n == n1)
            first = domin;
        cout << n << ". " << domin << " - ";
        for (int i = 0; i < best_set.size(); ++i)
            cout << best_set[i] << " ";
        cout << endl;
        domin = 100;
    }

}
