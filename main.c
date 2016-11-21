//
//  main.c
//  OS_01
//
//  Created by 윤찬미 on 2016. 4. 21..
//  Copyright © 2016년 윤찬미. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct parameters
{
    int from;
    int to;
} parameters;

typedef struct Thirdparameters
{
    int from1;
    int from2;
    int from3;
} Thirdparameters;

void *Sort(parameters *);
int Small(int *,int *,int *);
int TwoSmall(int *,int *);
void *Merge(Thirdparameters *);

int arr[1010];
int i;
static int sol=0;
int main() {
    freopen("input.txt","r",stdin);
    
    while(scanf("%d",&arr[i])!=EOF)
        i++;

    int a=i-1;
    a=a/3;
    int t1=i%3;
    
    parameters *data1 = (parameters *) malloc (sizeof(parameters));
    parameters *data2 = (parameters *) malloc (sizeof(parameters));
    parameters *data3 = (parameters *) malloc (sizeof(parameters));

    data1->from = 0;
    data1->to = a-1;
    
    data2->from = data1->to +1;
    data2->to = data2->from + a-1;
    
    data3->from = data2->to + 1;
    data3->to = i-1;
    
    if(t1==2)
        data2->to++;

    
    
    Thirdparameters *alldata=(Thirdparameters *) malloc (sizeof(Thirdparameters));
    
    alldata->from1=data1->from;
    alldata->from2=data2->from;
    alldata->from3=data3->from;

    pthread_t tid1; pthread_t tid2;
    pthread_t tid3; pthread_t tid4;
    
    while(sol!=3) {
    pthread_create(&tid1, NULL, Sort, data1);
    pthread_create(&tid2, NULL, Sort, data2);
    pthread_create(&tid3, NULL, Sort, data3);
        
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
        
    }
    
   pthread_create(&tid4,NULL,Merge, alldata);
    pthread_join(tid4,NULL);
    
    return 0;
}

void *Sort(parameters *P)
{
    int start=P->from;
    int end=P->to;
    int k,j,temp=0;
    for(k=start;k<=end;k++)
    {
        for(j=start;j<end;j++)
        {
            if(arr[j+1]<arr[j])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    
    sol++;
    
    pthread_exit(0);
    
}

int Small(int *n1,int *n2,int *n3)
{
    int min=arr[*n1];
    
    if(min>arr[*n2])
        min=arr[*n2];
    
    if(min>arr[*n3])
        min=arr[*n3];
    
    
    if(min==arr[*n1])
        (*n1)++;
    else if(min==arr[*n2])
        (*n2)++;
    else if(min==arr[*n3])
        (*n3)++;
    
    
    return min;
}

int TwoSmall(int *n1,int *n2)
{
    int min=arr[*n1];
    
    if(min>arr[*n2])
        min=arr[*n2];
    
    if(min==arr[*n1])
        (*n1)++;
    else if(min==arr[*n2])
        (*n2)++;
    
    return min;
}


void *Merge(Thirdparameters *T)
{
    int merge[1010];
    int start[3];
    int cnt=0;
    start[0]=T->from1;
    start[1]=T->from2;
    start[2]=T->from3;
    
  
    while (start[0]!=T->from2 || start[1]!=T->from3 || start[2]!=i)
    {
        if(start[0]==T->from2 && start[1]!=T->from3 && start[2]!=i)
             merge[cnt++]=TwoSmall(&start[1],&start[2]);

        else if(start[0]!=T->from2 && start[1]==T->from3  && start[2]!=i )
            merge[cnt++]=TwoSmall(&start[0],&start[2]);

        
        else if(start[0]!=T->from2 && start[1]!=T->from3 && start[2]==i )
            merge[cnt++]=TwoSmall(&start[0],&start[1]);
        
        
        else if(start[0]!=T->from2 && start[1]==T->from3 &&start[2]==i)
            merge[cnt++]=arr[start[0]++];
        
        
        else if(start[0]==T->from2 &&start[1]!=T->from3 &&start[2]==i)
            merge[cnt++]=arr[start[1]++];
        
        
        else if(start[0]==T->from2 && start[1]==T->from3 && start[2]!=i)
            merge[cnt++]=arr[start[2]++];
        
        else
            merge[cnt++]=Small(&start[0],&start[1],&start[2]);
        
    }

   
    for(int j=0;j<i;j++)
        printf("%d ",merge[j]);
    puts("");
    
    pthread_exit(0);
    
}


