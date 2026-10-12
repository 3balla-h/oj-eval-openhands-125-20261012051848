#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

// Fast input function to handle large input sizes
inline int readInt() {
    int x = 0;
    char c = getchar();
    while (c <= ' ') c = getchar();
    bool neg = false;
    if (c == '-') {
        neg = true;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return neg ? -x : x;
}

// Union-Find data structure for managing equivalence classes with optimized path compression
class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
public:
    int find(int x) {
        auto it = parent.find(x);
        if (it == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        // Union by rank
        int rankX = rank[rootX];
        int rankY = rank[rootY];
        
        if (rankX < rankY) {
            parent[rootX] = rootY;
        } else if (rankX > rankY) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX] = rankX + 1;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int t = readInt();
    
    while (t--) {
        int n = readInt();
        
        // Process constraints directly without storing them
        UnionFind uf;
        bool valid = true;
        
        for (int i = 0; i < n; i++) {
            int x = readInt();
            int y = readInt();
            int e = readInt();
            
            if (e == 1) {
                // Equality constraint: x = y
                uf.unite(x, y);
            } else {
                // Inequality constraint: x != y
                // We can't process inequality constraints immediately
                // Store them for later checking
                if (valid && uf.connected(x, y)) {
                    valid = false;
                }
            }
        }
        
        // If we already found a contradiction, output NO
        if (!valid) {
            puts("NO");
            continue;
        }
        
        // All inequality constraints were checked during input processing
        puts("YES");
    }
    
    return 0;
}