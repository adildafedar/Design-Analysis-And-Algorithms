/*Adil Dafedar - 123B1F018
ASSIGNMENT 5
Scenario: SwiftCargo Logistics Route Optimization

SwiftCargo delivers packages across multiple cities organized in stages:
  - Stage 1: Source Warehouses
  - Stage 2: Transit Hubs
  - Stage 3: Delivery Centers
Each package must pass through at least one node in every stage to reach its destination.

Goals:
1. Model the network as a directed, weighted multistage graph.
2. Find the least-cost route using Dynamic Programming.
3. Support real-time updates and scale to thousands of nodes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct {
    int u, v, cost;
} Edge;

void findOptimalRoute(int n, int e, Edge edges[], int source, int destination) {
    int cost[n];        
    int next[n];        
    for (int i = 0; i < n; i++) {
        cost[i] = (i == destination) ? 0 : INF;
        next[i] = -1;
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j < e; j++) {
            if (edges[j].u == i && edges[j].v < n && cost[edges[j].v] != INF) {
                int newCost = edges[j].cost + cost[edges[j].v];
                if (newCost < cost[i]) {
                    cost[i] = newCost;
                    next[i] = edges[j].v;
                }
            }
        }
    }

    printf("\nMinimum delivery cost from City %d to City %d = %d\n", source, destination, cost[source]);

    printf("Optimal route: %d", source);
    int current = next[source];
    while (current != -1) {
        printf(" -> %d", current);
        current = next[current];
    }
    printf("\n");
}

int main() {
    int n, e, source, destination;

    printf("Enter number of cities (nodes): ");
    scanf("%d", &n);
    printf("Enter number of routes (edges): ");
    scanf("%d", &e);

    Edge *edges = malloc(e * sizeof(Edge));
    printf("\nEnter routes (from to cost):\n");
    for (int i = 0; i < e; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost);

    printf("\nEnter source city: ");
    scanf("%d", &source);
    printf("Enter destination city: ");
    scanf("%d", &destination);

    findOptimalRoute(n, e, edges, source, destination);

    int u, v, newCost;
    printf("\nUpdate route cost (u v newCost): ");
    scanf("%d %d %d", &u, &v, &newCost);
    for (int i = 0; i < e; i++)
        if (edges[i].u == u && edges[i].v == v)
            edges[i].cost = newCost;

    printf("\nRecomputing after update...\n");
    findOptimalRoute(n, e, edges, source, destination);

    free(edges);
    return 0;
}
