#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 100

void prims(int n, int dist[MAX][MAX]) {
    bool visited[MAX] = {false};
    int near[MAX];
    int edges = 0;
    int total_cost = 0;
    int i, nextv;

    visited[0] = true;
    for (i = 1; i < n; i++) {
        near[i] = 0;  
    }

    printf("Edges in the MST:\n");

    while (edges < n - 1) {
        int min = INT_MAX;
        nextv = -1;

       
        for (i = 1; i < n; i++) {
            if (!visited[i] && dist[i][near[i]] < min) {
                min = dist[i][near[i]];
                nextv = i;
            }
        }

        if ( nextv != -1) {
            printf("F%d - F%d : %d\n", near[nextv] + 1, nextv + 1, min);
            total_cost += min;
            visited[nextv] = true;
            edges++;

            for (i = 1; i < n; i++) {
                if (!visited[i] && dist[i][nextv] < dist[i][near[i]]) {
                    near[i] = nextv;
                }
            }
        }

       
        printf("Near array: ");
        for (i = 0; i < n; i++) {
            if (visited[i])
                printf(" S ");
            else
                printf("F%d ", near[i] + 1);
        }
        printf("\n");
    }

    printf("Total minimum ink length: %d\n", total_cost);
}

int main() {
    int n;
    int dist[MAX][MAX];
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter the distance matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &dist[i][j]);

    prims(n, dist);

    return 0;
}