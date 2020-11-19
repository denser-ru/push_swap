//
// Created by Cheyenne Ayako on 11/19/20.
//

#include <stdio.h>
//#include "push_swap.h"

void merge(int arr[], int l, int m, int h)
{
	int		arr1[20];
	int		arr2[20];
	int		n1, n2 , i, j, k;
	n1 = m - l + 1 ;
	n2 = h - m;

	i = 0;
	while (i < n1)
	{
		arr1[i] = arr[l + i];
		++i;
	}
	j = 0;
	while (j < n2)
	{
		arr2[j] = arr[m + j + 1];
		++j;
	}
	arr1[i] = 9999;
	arr2[j] = 9999;
	i = 0;
	j = 0;
	k = l;
	while (k <= h)
	{
		if(arr1[i] <= arr2[j])
			arr[k] = arr1[i++];
		else
			arr[k] = arr2[j++];
		++k;
	}
}

void merge_sort(int arr[], int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		merge_sort(arr, low, mid);
		merge_sort(arr,mid + 1, high);
		merge(arr, low, mid, high);
	}
}


int main()
{
	int		arr[20] = {6, 12, 16, 20, 5, 18, 10, 13, 19, 4, 2, 14, 8, 7, 3, 15, 17, 1, 11, 9};
	int n = 20,i;
	printf("\n\t\t\t------Merge Sorting------\n\n");
	printf("Entered the elements:\n");
	for(i=0; i < n; i++)
	{
		printf("\t%d",arr[i]);
	}
	merge_sort(arr,0,n-1);
	printf("\n\n\t\t\t-----Merge Sorted Elements-----\n\n");
	printf("Sorted array:\n");
	for(i=0; i < n; i++)
	{
		printf("\t%d",arr[i]);
	}
	putchar('\n');
	return (0);
}
