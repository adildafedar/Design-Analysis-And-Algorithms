
/* Adil Dafedar - 123B1F018
ASSIGNMENT 1
Design and implement a sorting algorithm using Merge Sort to efficiently arrange customer
orders based on their timestamps. The solution should handle a large dataset (up to 1 million
orders) with minimal computational overhead. Additionally, analyze the time complexity and
compare it with traditional sorting techniques.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long timestamp;
    char details[100];
} Order;

// Merge two sorted halves
void merge(Order arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    Order *L = malloc(n1 * sizeof(Order));
    Order *R = malloc(n2 * sizeof(Order));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i].timestamp < R[j].timestamp) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Recursive Merge Sort
void mergeSort(Order arr[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int main() {
    int n;
    printf("Enter number of orders: ");
    scanf("%d", &n);

    Order *orders = malloc(n * sizeof(Order));
    printf("Enter timestamp and details:\n");
    for (int i = 0; i < n; i++)
        scanf("%lld %s", &orders[i].timestamp, orders[i].details);

    mergeSort(orders, 0, n - 1);

    printf("\nSorted Orders by Timestamp:\n");
    for (int i = 0; i < n; i++)
        printf("%lld %s\n", orders[i].timestamp, orders[i].details);

    free(orders);
    return 0;
}
