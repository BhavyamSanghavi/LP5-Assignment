#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int n = 5;
vector<vector<int>> graph = {
    {1,2}, {0,3,4}, {0}, {1}, {1}
};

vector<bool> visited(n, false);

// Sequential DFS
void dfs_seq(int node) {
    visited[node] = true;
    cout << node << " ";

    for (int neigh : graph[node]) {
        if (!visited[neigh]) {
            dfs_seq(neigh);
        }
    }
}

// Parallel DFS
void dfs_par(int node) {
    visited[node] = true;
    cout << node << " ";

    #pragma omp parallel for
    for (int i = 0; i < graph[node].size(); i++) {
        int neigh = graph[node][i];

        if (!visited[neigh]) {
            dfs_par(neigh);
        }
    }
}

// Sequential BFS
void bfs_seq(int root) {
    vector<bool> vis(n, false);
    queue<int> q;

    q.push(root);
    vis[root] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for (int neigh : graph[node]) {
            if (!vis[neigh]) {
                vis[neigh] = true;
                q.push(neigh);
            }
        }
    }
}

// Parallel BFS
void bfs_par(int root) {
    vector<bool> vis(n, false);
    queue<int> q;

    q.push(root);
    vis[root] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph[node].size(); i++) {
            int neigh = graph[node][i];

            if (!vis[neigh]) {
                #pragma omp critical
                {
                    if (!vis[neigh]) {
                        vis[neigh] = true;
                        q.push(neigh);
                    }
                }
            }
        }
    }
}

int main() {
    double start, end;

    // Sequential DFS
    fill(visited.begin(), visited.end(), false);
    cout << "Sequential DFS: ";
    start = omp_get_wtime();
    dfs_seq(0);
    end = omp_get_wtime();
    cout << "\nTime: " << end - start << "\n\n";

    // Parallel DFS
    fill(visited.begin(), visited.end(), false);
    cout << "Parallel DFS: ";
    start = omp_get_wtime();
    dfs_par(0);
    end = omp_get_wtime();
    cout << "\nTime: " << end - start << "\n\n";

    // Sequential BFS
    cout << "Sequential BFS: ";
    start = omp_get_wtime();
    bfs_seq(0);
    end = omp_get_wtime();
    cout << "\nTime: " << end - start << "\n\n";

    // Parallel BFS
    cout << "Parallel BFS: ";
    start = omp_get_wtime();
    bfs_par(0);
    end = omp_get_wtime();
    cout << "\nTime: " << end - start << "\n";

    return 0;
}