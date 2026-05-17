#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    int x, y;
    int g, h, f;
    Node* parent;
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

bool isValid(int x, int y, int n, int m, vector<vector<int>>& grid) {
    return (x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 0);
}

void printPath(Node* node) {
    if (node == nullptr) return;
    printPath(node->parent);
    cout << "(" << node->x << "," << node->y << ") ";
}

void AStar(vector<vector<int>>& grid, int sx, int sy, int ex, int ey) {
    int n = grid.size();
    int m = grid[0].size();

    priority_queue<Node*, vector<Node*>, Compare> openList;
    vector<vector<bool>> closedList(n, vector<bool>(m, false));

    Node* start = new Node{sx, sy, 0, heuristic(sx, sy, ex, ey), 0, nullptr};
    start->f = start->g + start->h;
    openList.push(start);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->x == ex && current->y == ey) {
            cout << "Path found: ";
            printPath(current);
            cout << endl;
            return;
        }

        closedList[current->x][current->y] = true;

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!isValid(nx, ny, n, m, grid) || closedList[nx][ny])
                continue;

            int gNew = current->g + 1;
            int hNew = heuristic(nx, ny, ex, ey);
            int fNew = gNew + hNew;

            Node* neighbor = new Node{nx, ny, gNew, hNew, fNew, current};
            openList.push(neighbor);
        }
    }

    cout << "No path found!" << endl;
}

int main() {
    int n, m;
    cout << "Enter grid rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    cout << "Enter grid (0 = free path, 1 = obstacle):" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    int sx, sy, ex, ey;
    cout << "Enter start position (x y): ";
    cin >> sx >> sy;
    cout << "Enter goal position (x y): ";
    cin >> ex >> ey;

    AStar(grid, sx, sy, ex, ey);

    return 0;
}
