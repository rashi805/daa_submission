#include <stdio.h>
#include <time.h>

#define MAX 50

typedef struct {
    int weight;
    int profit;
    float ratio;
} Item;

void swap(Item *a, Item *b) {
    Item t = *a; *a = *b; *b = t;
}

void sortByWeight(Item a[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j].weight > a[j+1].weight)
                swap(&a[j], &a[j+1]);
}

void sortByProfit(Item a[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j].profit < a[j+1].profit)
                swap(&a[j], &a[j+1]);
}

void sortByRatio(Item a[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j].ratio < a[j+1].ratio)
                swap(&a[j], &a[j+1]);
}

float knapsack(Item a[], int n, int cap) {
    float profit = 0; int w = 0;
    for(int i=0;i<n;i++) {
        if(w + a[i].weight <= cap) {
            w += a[i].weight;
            profit += a[i].profit;
        } else {
            int r = cap - w;
            profit += a[i].profit * ((float)r / a[i].weight);
            break;
        }
    }
    return profit;
}

int main() {
    int n, cap;
    Item a[MAX];
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter capacity: ");
    scanf("%d", &cap);
    for(int i=0;i<n;i++) {
        scanf("%d %d", &a[i].weight, &a[i].profit);
        a[i].ratio = (float)a[i].profit / a[i].weight;
    }

    sortByWeight(a,n);
    clock_t s1=clock(); float p1=knapsack(a,n,cap); clock_t e1=clock();
    sortByProfit(a,n);
    clock_t s2=clock(); float p2=knapsack(a,n,cap); clock_t e2=clock();
    sortByRatio(a,n);
    clock_t s3=clock(); float p3=knapsack(a,n,cap); clock_t e3=clock();

    printf("Method 1 (Min weight): Profit = %.2f, Time = %f sec\n",p1,(double)(e1-s1)/CLOCKS_PER_SEC);
    printf("Method 2 (Max profit): Profit = %.2f, Time = %f sec\n",p2,(double)(e2-s2)/CLOCKS_PER_SEC);
    printf("Method 3 (Profit/weight): Profit = %.2f, Time = %f sec\n",p3,(double)(e3-s3)/CLOCKS_PER_SEC);

    if(p1>=p2 && p1>=p3) printf("Best Method = Min weight\n");
    else if(p2>=p1 && p2>=p3) printf("Best Method = Max profit\n");
    else printf("Best Method = Profit/weight ratio\n");
    return 0;
}