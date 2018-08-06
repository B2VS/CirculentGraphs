#include <bits/stdc++.h>

using namespace std;

int m = 9;

bool check(vector <bool> &graph, int n)
{
    vector <bool> graph2(n + m);
    for (int i = 0; i < n; ++i)
    {
        if (graph[i])
        {
            graph2[i] = true;
            graph2[(i + n - 1) % n] = true;
            graph2[(i + 1) % n] = true;
            graph2[(i + m) % n] = true;
            graph2[(i - m + n) % n] = true;
        }
    }
    for (int i = 0; i < n; ++i)
        if (!graph2[i])
            return false;
    return true;
}

int find_nodef(vector <bool> &graph, int n)
{
    vector <bool> graph2(n + m);
    for (int i = 0; i <= n; ++i)
    {
        if (graph[i])
        {
            graph2[i] = true;
            graph2[i + 1] = true;
            graph2[i + m] = true;
            if (i >= 1)
                graph2[i - 1] = true;
            if (i >= m)
                graph2[i - m] = true;
        }
    }
    for (int i = 0; ; ++i)
        if (!graph2[i])
            return i;
}

double best_ratio = 0.5;
vector <int> best_set;

void cover(vector <bool> graph, int node)
{
    graph[node] = true;
    if (node > 20)
        return;
    if (node > m && check(graph, node))
    {
        vector <int> x;
        for (int i = 0; i <= node; ++i)
            if (graph[i])
                x.push_back(i);
        double ra = (double)(x.size() - 1) / (double)x[x.size() - 1];
        //cout << ra << endl;
        if (ra < best_ratio)
        {
            best_ratio = ra;
            best_set.clear();
            for (int i = 0; i < x.size(); ++i)
                best_set.push_back(x[i]);
        }
        return;
    }
    //cout << "Marked " << node << ": ";
    int nodef = find_nodef(graph, node);
    //cout << "nodef = " << nodef << "... Going from " << node + 1 << " to " << nodef + m << endl;
    for (int i = node + 1; i <= nodef + m + 1; ++i)
    {
        //cout << nodef << ") ";
        cover(graph, i);
    }
}

int main()
{
    vector <bool> graph(1000);
    graph[0] = true;
    //int best = 0;
    for (int i = 1; i <= 3 + m; ++i)
        cover(graph, i);
    cout << "best ratio: " << best_ratio << endl;
    for (auto ele: best_set)
        cout << ele << " ";
    //cout << best;

}
