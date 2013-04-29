#ifndef __QUEUE__H
#define __QUEUE__H

#include <iostream>
#include "linked_list.h"

using namespace std;

template <typename T> class Queue 
{
	private:
		LinkedList<T> ll;
		int size;

	public:
		// Constructor
		Queue() {
			size = 0;
		}
	
		// Destructor
		~Queue() {}
			
		// Adauga in coada
		void enqueue(T x) 
		{
			ll.addLast(x);
			size++;
		}	
	
		// Extrage din coada
		T dequeue() 
		{
			if(isEmpty())
			{
				cout << "The queue is empty!\n";
				T x;
				return x;
			}
			T x = ll.pfirst->info;
			ll.removeFirst();
			size--;
			return x;
		}
	
		// Afla primul element
		T front() {
			if(isEmpty())
			{
				cout << "The queue is empty!\n";
				T x;
				return x;
			}
			return ll.pfirst->info;
		}
		
		//Returneaza cate elemente sunt in coada
		int sizeQueue() {
			return size;
		}
	
		//Verifica daca este goala coada
		bool isEmpty() {
			return (ll.isEmpty());
		}
		
};

#endif // __QUEUE__H






