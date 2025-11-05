/*Adil Dafedar - 123B1F018
ASSIGNMENT 3
Scenario: Emergency Relief Supply Distribution

A devastating flood has hit multiple villages, and the rescue team must load supplies
(food, medicine, water) onto a boat with a maximum weight capacity W.

Each supply item has:
- weight (w[i]) in kilograms
- utility value (v[i]) indicating importance
- a flag showing if it's divisible (e.g., food/water) or not (e.g., medicine)

Task:
1. Implement Fractional Knapsack to maximize total utility value.
2. Allow fractional selection for divisible items.
3. Prioritize high-value items while staying within weight limit.
*/

#include <stdio.h>
#include <stdlib.h>

// Structure for supply items
typedef struct {
    char name[50];
    float weight, value;
    int divisible; // 1 = can divide, 0 = must take whole
} Item;

// Comparator: Sort by value/weight ratio (descending)
int compare(const void *a, const void *b) {
    float r1 = ((Item *)a)->value / ((Item *)a)->weight;
    float r2 = ((Item *)b)->value / ((Item *)b)->weight;
    return (r2 > r1) - (r2 < r1); // descending order
}

// Fractional Knapsack function
float fractionalKnapsack(Item items[], int n, float capacity) {
    qsort(items, n, sizeof(Item), compare);
    float totalValue = 0.0;

    for (int i = 0; i < n && capacity > 0; i++) {
        if (items[i].weight <= capacity) {
            // Take whole item
            capacity -= items[i].weight;
            totalValue += items[i].value;
            printf("Taken: %s (full)\n", items[i].name);
        } else {
            if (items[i].divisible) {
                // Take fractional part
                float fraction = capacity / items[i].weight;
                totalValue += items[i].value * fraction;
                printf("Taken: %s (%.2f%%)\n", items[i].name, fraction * 100);
                capacity = 0;
            } else {
                printf("Skipped: %s (not divisible, too heavy)\n", items[i].name);
            }
        }
    }
    return totalValue;
}

int main() {
    int n;
    float W;

    printf("Enter number of supply items: ");
    scanf("%d", &n);

    Item *items = malloc(n * sizeof(Item));
    for (int i = 0; i < n; i++) {
        printf("\nEnter name, weight, value, divisible(1=yes,0=no): ");
        scanf("%s %f %f %d", items[i].name, &items[i].weight, &items[i].value, &items[i].divisible);
    }

    printf("\nEnter boat capacity (kg): ");
    scanf("%f", &W);

    float maxValue = fractionalKnapsack(items, n, W);

    printf("\nMaximum total utility value = %.2f\n", maxValue);

    free(items);
    return 0;
}
