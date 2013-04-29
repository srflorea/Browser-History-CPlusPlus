//Florea Alexandru - Ionut
//313CA

#pragma once

#include <stdio.h>

#include "queue.h"

/*functie care returneaza cate cifre are cel mai mare element 
 *dintr-un vector
 */
int nrDigits(int array[], int size)
{
	int max = array[0], nr = 0;
	for(int i = 1; i< size; i++)
	{
		if(array[i] > max)
			max = array[i];
	}

	while(max != 0)
	{
		max = max / 10;
		nr++;
	}
	return nr;
}

/*functie de sortare a unui vector - RADIX SORT
 */
void radixSort(int array[], int size)
{
	Queue<int> q[10];
	int p = 1;
	int tmp, pos;
	
	int x = nrDigits(array, size);

	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < size; j++)
		{
			tmp = array[j];
			pos = (tmp / p) % 10;
			
			if(array[j] < p)
				q[0].enqueue(array[j]);
			else
				q[pos].enqueue(array[j]);
		}
		
		p *= 10;
		
		int k = 0;
		for(int i = 0; i < 10; i++)
		{
			while(!q[i].isEmpty())
				array[k++] = q[i].dequeue();
		}
	}	
}


