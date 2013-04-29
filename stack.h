//Florea Alexandru - Ionut
//313CA

#ifndef __STACK__H
#define __STACK__H

#include <stdio.h>

#include "linked_list.h"

template<typename T> class Stack 
{
	private:
		LinkedList<T> LL;
		int size;
		
	public:
		// constructor
		Stack() {
			size = 0;
		}

		// destructor
		~Stack() {}

		// operator de adaugare
		void push(T x) {
			LL.addFirst(x);
			size++;
		}

		// operatorul de stergere
		T pop() {
			if(isEmpty())
			{
				printf("The stack is empty");
				T x;
				return x;
			}
			T x = LL.pfirst->info;
			LL.removeFirst();
			size--;
			return x;
		}

		// operatorul de consultare
		T peek() {
			if(isEmpty())
			{
				printf("The stack is empty");
				T x;
				return x;
			}
			return LL.pfirst->info;
		}
		
		// returneaza cate elemente sunt in stiva
		int sizeStack() {
			return size;
		}

		// operatorul de verificare dimensiune
		bool isEmpty() {
			return  (LL.isEmpty());
		}
		

};

#endif // __STACK__H
