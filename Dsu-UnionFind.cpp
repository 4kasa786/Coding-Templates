class UnionFind
{
private:
    vector<int> parent, rank; // parent array and rank array for union-find

public:
    UnionFind(int n)
    {
        parent.assign(n, 0);
        rank.assign(n, 0); // initialize the parent and rank arrays
        for (int i = 0; i < n; i++)
            parent[i] = i; // each node is its own parent initially
    }
    int findSet(int v)
    {
        if (parent[v] == v)
            return v;

        return parent[v] = findSet(parent[v]); // path compression
    }

    bool isSameSet(int a, int b)
    {
        return findSet(a) == findSet(b);
    }

    void unionSet(int a, int b)
    {
        if (!isSameSet(a, b))
        {
            int rootA = findSet(a);
            int rootB = findSet(b);
            if (rank[rootA] > rank[rootB])
                parent[rootB] = rootA; // attach smaller rank tree under larger rank tree
            else
            {
                parent[rootA] = rootB; // attach smaller rank tree under larger rank tree
                if (rank[rootA] == rank[rootB])
                    rank[rootB]++; // increment rank if both trees have the same rank
            }
        }
    }
};
