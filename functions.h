//Florea Alexandru - Ionut
//313CA

#pragma once

#include <stdio.h>

#include "struct.h"
#include "stack.h"
#include "queue.h"
#include "radixSort.h"

/*functia care returneaza pozitia unui element intr-un vector, sau 0 in
 *cazul in care nu se afla in vector
 */
int posQueue(struct array *arrayWindows, int window_id)
{
	for(int i = 0; i < (*arrayWindows).nrWindows; i++)
	{
		if( arrayWindows->A[i] == window_id)
			return i;
	}
	printf("\n");
	return 0;
}

/*functie care creaza o entitate de tip window, o coada si o stiva si
 *le adauga in vectorul corespunzator fiecaruia
 */
void open_window(struct window *windows, struct array *arrayWindows, 
					  Queue<person> *q, Stack<int> *s, int window_id, 
					  int weight_min, int weight_max, int q_, int k) 
{
	struct window Window;
	Window.windowID = window_id;
	Window.weightMin = weight_min;
	Window.weightMax = weight_max;
	Window.Q = q_;
	Window.K = k;
	Window.packages = 0;
	Window.grams = 0;
	windows[window_id] = Window;
	
	Queue<person> queue;
	q[window_id] = queue;
	
	Stack<int> stack;
	s[window_id] = stack;
	
	arrayWindows->A[arrayWindows->nrWindows++] = window_id;
	radixSort((*arrayWindows).A, (*arrayWindows).nrWindows);
}

/*functie care creaza o entitate de tip person si o adauga in coada
 *corespunzatoare lui window_id
 */
void add_person(Queue<person> *q, int personal_id, int pack_weight, 
                int window_id)
{
	struct person pers;
	pers.ID = personal_id;
	pers.packWeight = pack_weight;
	q[window_id].enqueue(pers);
}

/*functie care proceseaza din coada corespunzatoare lui window_id
 *un numar de n_people
 */
void process(struct window *windows, struct array arrayWindows, 
				 Queue<person> *q, Stack<int> *s, int window_id, int n_people)
{
	for(int i = 0; i < n_people; i++)
	{
		if((q[window_id].front().packWeight < windows[window_id].weightMin) ||
			(q[window_id].front().packWeight > windows[window_id].weightMax))
		{
			int pos = posQueue(&arrayWindows, window_id);
			
			if(pos >= arrayWindows.nrWindows - 1)
			{
				struct person p = q[window_id].dequeue();
				q[arrayWindows.A[0]].enqueue(p);
			} 
			
			else
			{
				struct person p = q[window_id].dequeue();
				q[arrayWindows.A[pos + 1]].enqueue(p);
			}
		}
		
		else
		{ 
			if(((windows[window_id].grams+q[window_id].front().packWeight) >
					 windows[window_id].K)														||
				  ((windows[window_id].packages + 1) > windows[window_id].Q))
			{	
			
				while(!s[window_id].isEmpty())
					s[window_id].pop();
					
				windows[window_id].grams = q[window_id].front().packWeight;
				windows[window_id].packages = 1;
				int weight = q[window_id].dequeue().packWeight;
				s[window_id].push(weight);
			}
			
			else
			{
				windows[window_id].grams += q[window_id].front().packWeight;
				windows[window_id].packages ++;
				int weight = q[window_id].dequeue().packWeight;
				s[window_id].push(weight);
			}
		}			
	}
}

/*functie care proceseaza toata coada corespunzatoare lui window_id
 */
void processAll(struct window *windows, struct array arrayWindows, 
				    Queue<person> *q, Stack<int> *s, int window_id)
{
	while(!q[window_id].isEmpty())
	{
		if((q[window_id].front().packWeight < windows[window_id].weightMin) ||
			(q[window_id].front().packWeight > windows[window_id].weightMax))
		{
			int pos = posQueue(&arrayWindows, window_id);
			
			if(pos >= arrayWindows.nrWindows - 1)
			{
				struct person p = q[window_id].dequeue();
				q[arrayWindows.A[0]].enqueue(p);
			} 
			
			else
			{
				struct person p = q[window_id].dequeue();
				q[arrayWindows.A[pos + 1]].enqueue(p);
			}
		}
		
		else
		{ 
			if(((windows[window_id].grams + q[window_id].front().packWeight) >
				  windows[window_id].K)													  ||
				((windows[window_id].packages + 1) > windows[window_id].Q))
			{	
			
				while(!s[window_id].isEmpty())
					s[window_id].pop();
					
				windows[window_id].grams = q[window_id].front().packWeight;
				windows[window_id].packages = 1;
				int weight = q[window_id].dequeue().packWeight;
				s[window_id].push(weight);
			}
			
			else
			{
				windows[window_id].grams += q[window_id].front().packWeight;
				windows[window_id].packages ++;
				int weight = q[window_id].dequeue().packWeight;
				s[window_id].push(weight);
			}
		}			
	}
}

/*functie care afiseaza starea stivelor de la fiecare ghiseu
 */
void printStacks(Stack<int> *s, struct array arrayWindows)
{
	printf("STACKS:\n");
	for(int i = 0; i < arrayWindows.nrWindows; i++)
	{
		int pos = arrayWindows.A[i];
		Stack<int> backup;
		
		printf("%d: ", pos);
		while(!s[pos].isEmpty())
		{
			printf("%d", s[pos].peek());
			if(s[pos].sizeStack() != 1)
				printf(", ");
			
			backup.push(s[pos].pop());
		}
		printf("\n");
		
		while(!backup.isEmpty())
			s[pos].push(backup.pop());
	}
}

/*functie care afiseaza starea cozilor de la fiecare ghiseu
 */
void printQueues(Queue<person> *q, struct array arrayWindows)
{
	printf("QUEUES:\n");
	for(int i = 0; i < arrayWindows.nrWindows; i++)
	{
		int pos = arrayWindows.A[i];
		Queue<person> backup;
		
		printf("%d: ", pos);
		while(!q[pos].isEmpty())
		{
			printf("(%d, %d)", q[pos].front().ID, q[pos].front().packWeight);
			if(q[pos].sizeQueue() != 1)
				printf(", ");
			
			backup.enqueue(q[pos].dequeue());
		}
		printf("\n");
		
		while(!backup.isEmpty())
			q[pos].enqueue(backup.dequeue());
	}
}

/*functie care afiseaza strea stivelor din fiecare ghiseu si le goleste
 */
void flushStacks(Stack<int> *s, struct array arrayWindows)
{
	printf("FLUSHING:\n");
	for(int i = 0; i < arrayWindows.nrWindows; i++)
	{
		int pos = arrayWindows.A[i];
		
		printf("%d: ", pos);
		while(!s[pos].isEmpty())
		{
			printf("%d", s[pos].peek());
			if(s[pos].sizeStack() != 1)
				printf(", ");
			
			s[pos].pop();
		}
		printf("\n");
	}
}



















