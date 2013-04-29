#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "struct.h"
#include "stack.h"
#include "queue.h"
#include "functions.h"
	
int main(int argc, char *argv[])
{
	char word[20]; //primul cuvant de pe fiecare linie din fisierul de intrare
	FILE *f = fopen(argv[1], "r");
	
	int N;
	fscanf(f, "%d\n", &N);
	
	struct window *windows = new struct window[N]; //vector de ghisee
	Queue<person> *q = new Queue<person>[N]; //vector de cozii
	Stack<int> *s = new Stack<int>[N]; //vector de stive
	struct array arrayWindows; //retine cate ghisee au fost deschise si ID-urile
	arrayWindows.nrWindows = 0;
	arrayWindows.A = new int[N];
		
	//citirea si interpretarea fisierului de input	
	while(fscanf(f, "%s", word) == 1)
	{
		if(strcmp(word, "OPEN_WINDOW") == 0)
		{
			int window_id, weight_min, weight_max, q_, k;
			fscanf(f, "%d%d%d%d%d", &window_id, &weight_min, &weight_max, &q_, &k);
			open_window(windows, &arrayWindows, q, s, window_id, weight_min,
						   weight_max, q_, k);
		}
						
		else if(strcmp(word, "ADD_PERSON") == 0)		
		{
			int personal_id, package_weight, window_id;
			fscanf(f, "%d%d%d", &personal_id, &package_weight, &window_id);
			add_person(q, personal_id, package_weight, window_id);
		}
			
		else if(strcmp(word, "PROCESS") == 0)
		{
			int window_id, n_people;
			fscanf(f, "%d%d", &window_id, &n_people);
			process(windows, arrayWindows, q, s, window_id, n_people);
		}
		
		else if(strcmp(word, "PROCESS_ALL") == 0)
		{
			int window_id;
			fscanf(f, "%d", &window_id);
			processAll(windows, arrayWindows, q, s, window_id);
		}
		
		else if(strcmp(word, "PRINT_QUEUES") == 0)
			printQueues(q, arrayWindows);
		
		else if(strcmp(word, "PRINT_STACKS") == 0)
			printStacks(s, arrayWindows);
		
		else if(strcmp(word, "FLUSH_STACKS") == 0)
			flushStacks(s, arrayWindows);
	}
	
	fclose(f);
	
	return 0;
}
