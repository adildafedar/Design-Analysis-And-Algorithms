/* Adil Dafedar - 123B1F018
ASSIGNMENT 4
Scenario: Smart Traffic Management for Emergency Vehicles

A smart city uses an intelligent traffic system to help ambulances reach hospitals fast.
The city’s road network is a graph:
- Intersections = Nodes
- Roads = Edges (with weights as travel time, in minutes)

Tasks:
1. Implement Dijkstra’s algorithm to find the shortest path from source (ambulance) to all hospitals.
2. Allow dynamic updates in edge weights (due to changing traffic).
3. Ensure efficiency for large cities (thousands of intersections and roads).
4. Provide a simple visual path output.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Graph structure using adjacency matrix
typedef struct {
    int V;           // number of intersections
    int **time;      // edge weights (travel times)
} Graph;

// Create graph
Graph* createGraph(int V) {
    Graph* g = malloc(sizeof(Graph));
    g->V = V;
    g->time = malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        g->time[i] = malloc(V * sizeof(int));
        for (int j = 0; j < V; j++)
            g->time[i][j] = (i == j) ? 0 : INF;
    }
    return g;
}

// Find vertex with minimum distance not yet visited
int minDistance(int dist[], int visited[], int V) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Print the shortest path from source to destination
void printPath(int parent[], int j) {
    if (parent[j] == -1) return;
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

// Dijkstra’s Algorithm
void dijkstra(Graph* g, int src) {
    int V = g->V;
    int dist[V], visited[V], parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && g->time[u][v] != INF && dist[u] + g->time[u][v] < dist[v]) {
                dist[v] = dist[u] + g->time[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nShortest travel times from Source %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("To %d: Unreachable\n", i);
        else {
            printf("To %d: %d min | Path: %d", i, dist[i], src);
            printPath(parent, i);
            printf("\n");
        }
    }
}

// Update road time dynamically (e.g., due to traffic)
void updateTraffic(Graph* g, int u, int v, int newTime) {
    g->time[u][v] = g->time[v][u] = newTime; // undirected road
    printf("\nTraffic updated: Road %d <-> %d now takes %d minutes.\n", u, v, newTime);
}

int main() {
    int V, E, src;
    printf("Enter number of intersections (nodes): ");
    scanf("%d", &V);
    Graph* g = createGraph(V);

    printf("Enter number of roads: ");
    scanf("%d", &E);
    printf("Enter roads (u v time):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g->time[u][v] = g->time[v][u] = w;
    }

    printf("Enter ambulance start location (source node): ");
    scanf("%d", &src);

    dijkstra(g, src);

    // Example of dynamic traffic update
    int u, v, newTime;
    printf("\nUpdate a road's traffic (u v new_time): ");
    scanf("%d %d %d", &u, &v, &newTime);
    updateTraffic(g, u, v, newTime);

    // Re-run Dijkstra to update shortest paths
    dijkstra(g, src);

    // Cleanup
    for (int i = 0; i < V; i++) free(g->time[i]);
    free(g->time);
    free(g);
    return 0;
}
