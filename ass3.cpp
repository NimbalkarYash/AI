#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<vector<int>> buildGraph(int n) {
    int e;
    cout << "Enter number of connections: ";
    cin >> e;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter cost of each connection (u v weight):\n";
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; 
    }

    return graph;
}

// SELECTION SORT
void selectionSort() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter mark of each student:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }

    cout << "Sorted list of marks:\n";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    cout << " Highest marks secured by a student: " << arr[n-1];
}

// PRIM'S MST
void primMST() {
    int n;
    cout << "Enter number of buildings: ";
    cin >> n;

    int e;
    cout << "Enter number of connections: ";
    cin >> e;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter cost of each connection (b1 b2 cost):\n";
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; 
    }
 
    vector<int> key(n, INT_MAX), parent(n, -1);
    vector<bool> mstSet(n, false);

    key[0] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!mstSet[v] && (u == -1 || key[v] < key[u]))
                u = v;

        mstSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int total = 0;
    cout << "Edges in MST:\n";
    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << " : "
             << graph[i][parent[i]] << endl;
        total += graph[i][parent[i]];
    }

    cout << "Total cost for the connection = " << total << endl;
}

//  KRUSKAL'S MST 
struct Edge {
    int u, v, w;
};

int findParent(int v, vector<int>& parent) {
    if (parent[v] == v)
        return v;
    return parent[v] = findParent(parent[v], parent);
}

void kruskalMST() {
    int n, e;
    cout << "Enter number of buildings: ";
    cin >> n;
    cout << "Enter number of connections: ";
    cin >> e;

    vector<Edge> edges(e);

    cout << "Enter cost of each connection (b1 b2 weight):\n";
    for (int i = 0; i < e; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    vector<int> parent(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    int total = 0;
    cout << "Edges in MST:\n";

    for (auto &edge : edges) {
        int pu = findParent(edge.u, parent);
        int pv = findParent(edge.v, parent);

        if (pu != pv) {
            cout << edge.u << " - " << edge.v << " : "
                 << edge.w << endl;
            total += edge.w;
            parent[pv] = pu;
        }
    }

    cout << "Total cost for the connection = " << total << endl;
}

//  DIJKSTRA  
void dijkstra() {
    int n;
    cout << "Enter number of buildings: ";
    cin >> n;

    vector<vector<int>> graph = buildGraph(n);

    int src;
    cout << "Enter source building: ";
    cin >> src;

    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!visited[v] && (u == -1 || dist[v] < dist[u]))
                u = v;

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "Shortest complete connection from source building:\n";
    for (int i = 0; i < n; i++)
        cout << "building " << i << " : " << dist[i] << endl;
}


int main() {
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Selection Sort\n";
        cout << "2. Prim's Minimum Spanning Tree\n";
        cout << "3. Kruskal's Minimum Spanning Tree\n";
        cout << "4. Dijkstra's Shortest Path Algorithm\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: selectionSort(); break;
            case 2: primMST(); break;
            case 3: kruskalMST(); break;
            case 4: dijkstra(); break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
