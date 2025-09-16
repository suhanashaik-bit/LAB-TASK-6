#include <stdio.h>
int partitioning(int arr[],int left,int right){
   int pivot;
   int i,j;
   pivot=arr[left];
   i=left;
   j=right;
   while(i<j){
       while(arr[i]<=pivot && i<right){
           i++;
       }
       while(arr[j]>pivot){
           j--;
       }
       if(i<j){
           int temp=arr[i];
           arr[i]=arr[j];
           arr[j]=temp;
       }
   }
   arr[left]=arr[j];
   arr[j]=pivot;
   return j;
}
void QuickSort(int arr[],int left,int right){
   int p;
   if(left<right){
       p=partitioning(arr,left,right);
       QuickSort(arr,left,p-1);
       QuickSort(arr,p+1,right);
   }
}
int main(){
   int n;
   printf("Enter the number of elements: ");
   scanf("%d",&n);
   int arr[n];
   for(int i=0;i<n;i++){
       printf("Enter element %d: ",i+1);
       scanf("%d",&arr[i]);
   }
   printf("Before Sorting: ");
   for(int i=0;i<n;i++){
       printf("%d ",arr[i]);
   }
   QuickSort(arr,0,n-1);
   printf("\nAfter Sorting: ");
   for(int i=0;i<n;i++){
       printf("%d ",arr[i]);
   }
   return 0;
}


