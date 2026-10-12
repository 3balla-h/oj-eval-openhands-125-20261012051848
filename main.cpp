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
        // Direct access - if not found, create new entry
        if (parent[x] == 0 && rank.find(x) == rank.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
        // Path compression with iterative approach to avoid deep recursion
        int root = x;
        while (parent[root] != root) {
            root = parent[root];
        }
        
        // Compress path
        while (parent[x] != x) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        
        return root;
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
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
        
        // Store equality and inequality constraints
        vector<pair<int, int>> equals;
        vector<pair<int, int>> not_equals;
        
        // Read all constraints
        for (int i = 0; i < n; i++) {
            int x = readInt();
            int y = readInt();
            int e = readInt();
            
            if (e == 1) {
                equals.push_back({x, y});
            } else {
                not_equals.push_back({x, y});
            }
        }
        
        // Use Union-Find to process all equality constraints
        UnionFind uf;
        
        // First, process all equality constraints
        for (auto& p : equals) {
            uf.unite(p.first, p.second);
        }
        
        // Check if any inequality constraint violates the equivalence classes
        bool valid = true;
        for (auto& p : not_equals) {
            if (uf.connected(p.first, p.second)) {
                valid = false;
                break;
            }
        }
        
        puts(valid ? "YES" : "NO");
    }
    
    return 0;
}