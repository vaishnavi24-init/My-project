#include <iostream>
#include <string>
using namespace std;

#define MAX 20

struct AdjNode {
    int vertex;
    AdjNode *next;
    AdjNode(int v) : vertex(v), next(NULL) {}
};

struct Queue {
    int data[MAX], front, rear;
    Queue() : front(0), rear(0) {}
    bool isEmpty() { return front == rear; }
    void enqueue(int x) { data[rear++] = x; }
    int dequeue() { return data[front++]; }
};

class Graph {
    int n;
    char name[MAX];
    int matrix[MAX][MAX];
    AdjNode *list[MAX];
    bool visited[MAX];

    void resetVisited() {
        for (int i = 0; i < n; i++) visited[i] = false;
    }

    void addToList(int u, int v) {
        AdjNode *node = new AdjNode(v);
        if (list[u] == NULL || list[u]->vertex > v) {
            node->next = list[u];
            list[u] = node;
            return;
        }
        AdjNode *t = list[u];
        while (t->next != NULL && t->next->vertex < v) t = t->next;
        node->next = t->next;
        t->next = node;
    }

    void dfsUtil(int u) {
        visited[u] = true;
        cout << name[u] << " ";
        for (int v = 0; v < n; v++) {
            if (matrix[u][v] == 1 && !visited[v]) dfsUtil(v);
        }
    }

public:
    Graph() : n(0) {}

    void create() {
        int e;
        cout << "Enter number of locations (max " << MAX << "): ";
        cin >> n;
        if (n < 1 || n > MAX) {
            cout << "Invalid number of locations.\n";
            n = 0;
            return;
        }

        for (int i = 0; i < n; i++) {
            name[i] = 'A' + i;
            list[i] = NULL;
            for (int j = 0; j < n; j++) matrix[i][j] = 0;
        }

        cout << "Locations are named A to " << name[n - 1] << ".\n";
        cout << "Enter number of routes (edges): ";
        cin >> e;

        for (int i = 0; i < e; i++) {
            char a, b;
            cout << "Enter route " << i + 1 << " (two locations, e.g. A B): ";
            cin >> a >> b;
            int u = a - 'A', v = b - 'A';

            if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
                cout << "Invalid route ignored.\n";
                continue;
            }
            if (matrix[u][v] == 1) {
                cout << "Route already exists.\n";
                continue;
            }

            matrix[u][v] = matrix[v][u] = 1;
            addToList(u, v);
            addToList(v, u);
        }
        cout << "Graph created.\n";
    }

    void displayMatrix() {
        if (n == 0) {
            cout << "Create the graph first.\n";
            return;
        }
        cout << "\nAdjacency Matrix:\n  ";
        for (int i = 0; i < n; i++) cout << name[i] << " ";
        cout << "\n";
        for (int i = 0; i < n; i++) {
            cout << name[i] << " ";
            for (int j = 0; j < n; j++) cout << matrix[i][j] << " ";
            cout << "\n";
        }
    }

    void displayList() {
        if (n == 0) {
            cout << "Create the graph first.\n";
            return;
        }
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < n; i++) {
            cout << name[i] << " -> ";
            for (AdjNode *t = list[i]; t != NULL; t = t->next) {
                cout << name[t->vertex] << (t->next ? " -> " : "");
            }
            if (list[i] == NULL) cout << "NULL";
            cout << "\n";
        }
    }

    void bfs(char s) {
        if (n == 0) {
            cout << "Create the graph first.\n";
            return;
        }
        int start = s - 'A';
        if (start < 0 || start >= n) {
            cout << "Invalid starting location.\n";
            return;
        }

        resetVisited();
        Queue q;
        visited[start] = true;
        q.enqueue(start);

        cout << "BFS sequence: ";
        while (!q.isEmpty()) {
            int u = q.dequeue();
            cout << name[u] << " ";
            for (AdjNode *t = list[u]; t != NULL; t = t->next) {
                if (!visited[t->vertex]) {
                    visited[t->vertex] = true;
                    q.enqueue(t->vertex);
                }
            }
        }
        cout << "\n";

        for (int i = 0; i < n; i++) {
            if (!visited[i]) cout << "Location " << name[i] << " is not reachable from " << s << ".\n";
        }
    }

    void dfs(char s) {
        if (n == 0) {
            cout << "Create the graph first.\n";
            return;
        }
        int start = s - 'A';
        if (start < 0 || start >= n) {
            cout << "Invalid starting location.\n";
            return;
        }

        resetVisited();
        cout << "DFS sequence: ";
        dfsUtil(start);
        cout << "\n";

        for (int i = 0; i < n; i++) {
            if (!visited[i]) cout << "Location " << name[i] << " is not reachable from " << s << ".\n";
        }
    }
};

int main() {
    Graph g;
    int choice;
    char s;

    do {
        cout << "\n===== CITY AREA GRAPH: BFS AND DFS =====\n"
             << "1. Create graph\n2. Display adjacency matrix\n3. Display adjacency list\n"
             << "4. BFS (adjacency list)\n5. DFS (adjacency matrix)\n6. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                g.create(); 
                break;
            case 2: 
                g.displayMatrix(); 
                break;
            case 3: 
                g.displayList(); 
                break;
            case 4:
                cout << "Enter starting location (A, B, ...): ";
                cin >> s;
                g.bfs(s);
                break;
            case 5:
                cout << "Enter starting location (A, B, ...): ";
                cin >> s;
                g.dfs(s);
                break;
            case 6: 
                cout << "Exiting program.\n"; 
                break;
            default: 
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
