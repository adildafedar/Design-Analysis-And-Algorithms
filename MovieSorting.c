/* Adil Dafedar - 123B1F018
ASSIGNMENT 2
Problem Statement:
Movie Recommendation System Optimization

A popular OTT platform, StreamFlix, offers personalized recommendations by sorting movies
based on user preferences such as IMDB rating, release year, or watch time popularity.
During peak hours, sorting large datasets slows down the system.

As a backend engineer, you must:
- Implement Quick Sort to efficiently sort movies based on user-selected parameters.
- Handle large datasets while maintaining fast response times.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[100];
    float rating;      // IMDB rating
    int year;          // Release year
    int popularity;    // Watch time popularity
} Movie;

// Global variable to control sorting parameter
int sortChoice;

// Compare two movies based on user's choice
int compare(Movie a, Movie b) {
    if (sortChoice == 1) return (a.rating > b.rating);
    if (sortChoice == 2) return (a.year > b.year);
    return (a.popularity > b.popularity);
}

// Partition function for Quick Sort
int partition(Movie arr[], int low, int high) {
    Movie pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compare(arr[j], pivot)) {
            i++;
            Movie temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Movie temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Recursive Quick Sort
void quickSort(Movie arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    printf("Enter number of movies: ");
    scanf("%d", &n);
    Movie *movies = malloc(n * sizeof(Movie));

    printf("\nEnter movie details: <Title Rating Year Popularity>\n");
    for (int i = 0; i < n; i++)
        scanf("%s %f %d %d", movies[i].title, &movies[i].rating, &movies[i].year, &movies[i].popularity);

    printf("\nSort by:\n1. IMDB Rating\n2. Release Year\n3. Popularity\nEnter choice: ");
    scanf("%d", &sortChoice);

    quickSort(movies, 0, n - 1);

    printf("\nSorted Movies:\n");
    for (int i = 0; i < n; i++)
        printf("%s %.1f %d %d\n", movies[i].title, movies[i].rating, movies[i].year, movies[i].popularity);

    free(movies);
    return 0;
}
