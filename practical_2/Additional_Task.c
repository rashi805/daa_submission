#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

#define MAX 50
#define INF 999999

// Standard Prim's using array
int prim_array(int n, int graph[MAX][MAX]) {
    int visited[MAX] = {0};
    int cost = 0;
    visited[0] = 1;

    for(int e=0; e<n-1; e++) {
        int min = INF, u=-1,v=-1;
        for(int i=0;i<n;i++) {
            if(visited[i]) {
                for(int j=0;j<n;j++) {
                    if(!visited[j] && graph[i][j] < min) {
                        min = graph[i][j];
                        u=i; v=j;
                    }
                }
            }
        }
        if(u!=-1 && v!=-1) {
            visited[v]=1;
            cost += graph[u][v];
        }
    }
    return cost;
}

// Slightly optimized Prim's (simulate priority queue with key array)
int prim_key(int n, int graph[MAX][MAX]) {
    int key[MAX], parent[MAX];
    bool mstSet[MAX];
    for(int i=0;i<n;i++) {
        key[i]=INF; mstSet[i]=false; parent[i]=-1;
    }
    key[0]=0;
    int cost=0;

    for(int count=0; count<n-1; count++) {
        int min=INF, u=-1;
        for(int i=0;i<n;i++)
            if(!mstSet[i] && key[i]<min) {min=key[i]; u=i;}
        mstSet[u]=true;
        cost += (parent[u]!=-1)?graph[u][parent[u]]:0;
        for(int v=0;v<n;v++) {
            if(graph[u][v] && !mstSet[v] && graph[u][v]<key[v]) {
                key[v]=graph[u][v];
                parent[v]=u;
            }
        }
    }
    return cost;
}

// Simple MSF: run Prim on each component separately
void msf(int n, int graph[MAX][MAX]) {
    int visited[MAX]={0};
    int comp=0;
    for(int start=0; start<n; start++) {
        if(!visited[start]) {
            comp++;
            printf("Component %d:\n", comp);
            visited[start]=1;
            int cost=0;
            for(int e=0;e<n-1;e++) {
                int min=INF,u=-1,v=-1;
                for(int i=0;i<n;i++) {
                    if(visited[i]) {
                        for(int j=0;j<n;j++) {
                            if(!visited[j] && graph[i][j]<min) {
                                min=graph[i][j]; u=i; v=j;
                            }
                        }
                    }
                }
                if(u!=-1 && v!=-1) {
                    visited[v]=1;
                    cost += graph[u][v];
                    printf("%d - %d : %d\n", u, v, graph[u][v]);
                }
            }
            printf("Total MST cost for this component: %d\n\n", cost);
        }
    }
}

int main() {
    int n=6;
    int graph[MAX][MAX] = {
        {0, 4, INF, INF, INF, INF},
        {4, 0, 2, INF, INF, INF},
        {INF, 2, 0, 3, INF, INF},
        {INF, INF, 3, 0, 5, INF},
        {INF, INF, INF, 5, 0, 1},
        {INF, INF, INF, INF, 1, 0}
    };

    clock_t start,end;

    start=clock();
    int cost1=prim_array(n,graph);
    end=clock();
    double time1=(double)(end-start)/CLOCKS_PER_SEC;

    start=clock();
    int cost2=prim_key(n,graph);
    end=clock();
    double time2=(double)(end-start)/CLOCKS_PER_SEC;

    printf("Prim Array MST Cost: %d, Time: %f sec\n", cost1, time1);
    printf("Prim Key-based MST Cost: %d, Time: %f sec\n", cost2, time2);

    printf("\n--- Minimum Spanning Forest Example ---\n");
    int graph2[MAX][MAX] = {
        {0, 2, INF, INF, INF, INF},
        {2, 0, INF, INF, INF, INF},
        {INF, INF, 0, 1, INF, INF},
        {INF, INF, 1, 0, INF, INF},
        {INF, INF, INF, INF, 0, 3},
        {INF, INF, INF, INF, 3, 0}
    };
    msf(6,graph2);

    return 0;
}