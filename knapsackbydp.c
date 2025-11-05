/*Adil Dafedar - 123B1F018
ASSIGNMENT 6
Scenario: Disaster Relief Resource Allocation

Objective:
- A relief truck has limited capacity W kg.
- There are N types of essential items, each with:
    - weight[i] in kg
    - utility[i] value (importance)
- Maximize total utility value without exceeding truck capacity.

Approach:
- 0/1 Knapsack: each item can be included (1) or excluded (0)
- Dynamic Programming used for efficiency
*/

#include <stdio.h>
#include <stdlib.h>

int knapsack(int W, int N, int weight[], int utility[], int taken[]) {
    int i, w;
    int dp[N + 1][W + 1];

    for (i = 0; i <= N; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) dp[i][w] = 0;
            else if (weight[i - 1] <= w) {
                int include = utility[i - 1] + dp[i - 1][w - weight[i - 1]];
                int exclude = dp[i - 1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            } else dp[i][w] = dp[i - 1][w];
        }
    }

    w = W;
    for (i = N; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            taken[i - 1] = 1; 
            w -= weight[i - 1];
        } else taken[i - 1] = 0;
    }

    return dp[N][W]; 
}

int main() {
    int N, W;

    printf("Enter number of item types: ");
    scanf("%d", &N);
    int weight[N], utility[N], taken[N];

    printf("Enter weight and utility value for each item:\n");
    for (int i = 0; i < N; i++)
        scanf("%d %d", &weight[i], &utility[i]);

    printf("Enter truck capacity (kg): ");
    scanf("%d", &W);

    int maxUtility = knapsack(W, N, weight, utility, taken);

    printf("\nMaximum utility value = %d\n", maxUtility);
    printf("Items to load in truck:\n");
    for (int i = 0; i < N; i++)
        if (taken[i])
            printf("Item %d (Weight: %d, Utility: %d)\n", i + 1, weight[i], utility[i]);

    return 0;
}
