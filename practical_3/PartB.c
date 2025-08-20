#include <stdio.h>

typedef struct {
    int start, finish, profit, index;
} Activity;

void swap(Activity *a, Activity *b) {
    Activity t=*a; *a=*b; *b=t;
}

void sortByFinish(Activity a[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j].finish > a[j+1].finish)
                swap(&a[j], &a[j+1]);
}

int main() {
    int n=11;
    Activity a[11]={{1,4,10,1},{3,5,15,2},{0,6,14,3},{5,7,12,4},
                    {3,9,20,5},{5,9,30,6},{6,10,32,7},{8,11,28,8},
                    {8,12,30,9},{2,14,40,10},{12,16,45,11}};
    sortByFinish(a,n);
    int totalProfit=0,count=0;
    printf("Selected activities:\n");
    int last=0;
    printf("A%d [start=%d, finish=%d, profit=%d]\n",a[0].index,a[0].start,a[0].finish,a[0].profit);
    totalProfit+=a[0].profit; count=1;
    for(int i=1;i<n;i++) {
        if(a[i].start>=a[last].finish) {
            printf("A%d [start=%d, finish=%d, profit=%d]\n",a[i].index,a[i].start,a[i].finish,a[i].profit);
            totalProfit+=a[i].profit; count++; last=i;
        }
    }
    printf("\nTotal selected = %d\nTotal profit = %d\n",count,totalProfit);
    return 0;
}