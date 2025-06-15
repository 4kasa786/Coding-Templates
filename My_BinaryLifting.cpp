#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include "KasaTemplate.cpp"
#else
#define debug(...)
#define debugArr(arr, n)
#endif

signed main()
{

    int n, q;
    cin >> n >> q;
    vector<vector<int>> kasa(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int x;
        cin >> x;
        kasa[i].push_back(x);
        kasa[x].push_back(i);
    }
    kasa[1].push_back(0); // Adding a dummy parent for the root node
    int kth = log2(n) + 1;
    vector<int> values(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> values[i];
    values[0] = 1e9;
    vector<vector<int>> par(n + 1, vector<int>(kth, 0));
    vector<vector<int>> mini(n + 1, vector<int>(kth, 1e9)); // to store the minimum
    // value in the path from the node to its 2^i th ancestor
    vector<int> depth(n + 1, 0);

    auto dfs = [&](int parent, int currentNode, auto &&dfs) -> void
    {
        par[currentNode][0] = parent;
        mini[currentNode][0] = min(values[currentNode], values[parent]);
        // initiaxlize th mini value upto the parent node to the
        //  minimum of the current node, parent node and the 2^0 th ancestor of the current node
        depth[currentNode] = depth[parent] + 1;

        for (int i = 1; i < kth; i++)
        {
            int p = par[currentNode][i - 1];
            par[currentNode][i] = par[p][i - 1];
            mini[currentNode][i] = min(mini[currentNode][i - 1], mini[p][i - 1]);
        }

        for (auto neighbour : kasa[currentNode])
        {
            if (neighbour != parent)
            {
                dfs(currentNode, neighbour, dfs);
            }
        }
    };

    dfs(0, 1, dfs); // start DFS from the root node (1) with parent 0
    debug(depth);
    debug(par);
    debug(mini);

    auto LCA = [&](int u, int v) -> int
    {
        if (u == v) // if both nodes are same,
            return u;
        if (depth[u] < depth[v])
            swap(u, v); // make sure u is deeper than v

        int diff = depth[u] - depth[v];

        for (int i = kth - 1; i >= 0; i--)
        {
            int setBit = 1 << i;
            if (setBit & diff) // if the ith bit is set in diff ,we need to go up in the tree
            {
                u = par[u][i]; // jump to the 2^i th ancestor of u
            }
        }

        // after this both u and v are at the same depth
        if (u == v) // if both nodes are same after going up
            return u;

        for (int i = kth - 1; i >= 0; i--)
        {
            if (par[u][i] != par[v][i])
            {
                // if the 2^i th ancestor of u and v are not same
                // and they are not 0 (means they are not root node)
                // and they are not same as u and v
                // then we need to go up in the tree
                u = par[u][i]; // jump to the 2^i th ancestor of u
                v = par[v][i]; // jump to the 2^i th ancestor of v
            }
        }

        return par[u][0]; // return the parent of u which is the LCA of u and v
    };

    auto minBinaryLifting = [&](int u, int v) -> int
    {
        if (u == v)
            return values[u];
        // if both u and v are same then return there value

        if (depth[u] < depth[v])
            swap(u, v);
        // means u has greater depth

        int diff = depth[u] - depth[v];
        int ans = 1e9;
        for (int i = kth - 1; i >= 0; i--)
        {
            int setBit = 1 << i;
            if (diff & setBit)
            {
                ans = min(ans, mini[u][i]);
                u = par[u][i];
            }
        }
        // now both the nodes are at the same position
        if (u == v)
        {
            return min(ans, values[u]);
        }

        for (int i = kth - 1; i >= 0; i--)
        {
            if (par[u][i] != par[v][i])
            {
                ans = min({ans, mini[u][i], mini[v][i]});
                u = par[u][i];
                v = par[v][i];
            }
        }

        return min({ans, mini[u][0], mini[v][0]});
    };

    while (q--)
    {
        int u, v;
        cin >> u >> v;
        debug(minBinaryLifting(u, v));
    }
}