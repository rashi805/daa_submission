#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX 50
#define INF 999999
#define R 6371.0
#define PI 3.14159265358979323846

double toRadians(double deg) {
    return deg * PI / 180.0;
}

double distance(double lat1, double lon1, double lat2, double lon2) {
    double dlat = toRadians(lat2 - lat1);
    double dlon = toRadians(lon2 - lon1);
    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1) * cos(lat2) *
               sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

int main() {
    int n;
    char city[MAX][50];
    double lat[MAX], lon[MAX], cost[MAX][MAX];
    int selected[MAX] = {0};
    double totalCost = 0;
    int edges = 0;

    printf("Enter number of cities: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter city name, latitude and longitude: ");
        scanf("%s %lf %lf", city[i], &lat[i], &lon[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                cost[i][j] = INF;
            else
                cost[i][j] = distance(lat[i], lon[i], lat[j], lon[j]);
        }
    }

    selected[0] = 1;
    while (edges < n - 1) {
        double min = INF;
        int x = -1, y = -1;
        for (int i = 0; i < n; i++) {
            if (selected[i]) {
                for (int j = 0; j < n; j++) {
                    if (!selected[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }
        printf("%s - %s : %.2lf km\n", city[x], city[y], cost[x][y]);
        totalCost += cost[x][y];
        selected[y] = 1;
        edges++;
    }

    printf("Total minimum cost = %.2lf km\n", totalCost);
    return 0;
}
