#ifndef __LL_H_
#define __LL_H_

#include <stdio.h>
#include <string.h>


template<typename T> struct list_elem {
    T info;
    struct list_elem<T> *next, *prev;
};

template <typename T> class LinkedList 
{

	public:

		  struct list_elem<T> *pfirst, *plast;
		  
		  //constructor
        LinkedList(){
            pfirst = plast = NULL;
        }
		  
		  //adauga un nod la inceputul listei
        void addFirst(T x) {
            struct list_elem<T> *paux;

            paux = new struct list_elem<T>;
            memcpy(&(paux->info), &x, sizeof(T));
            paux->prev = NULL;
            paux->next = pfirst;

            if (pfirst != NULL) pfirst->prev = paux;
            pfirst = paux;

            if (plast == NULL) plast=pfirst;
        }

		  //adauga un nod la sfarsitul listei
        void addLast(T x) {
            struct list_elem<T> *paux;

            paux = new struct list_elem<T>;
            memcpy(&(paux->info), &x, sizeof(T));
            paux->prev = plast;
            paux->next = NULL;

            if (plast != NULL) plast->next = paux;
            plast = paux;
            if (pfirst == NULL) pfirst = plast;
        }

		  //sterge primul nod din lista
        void removeFirst() {
            struct list_elem<T>* paux;

            if (pfirst != NULL) {
                paux = pfirst->next;
                if (pfirst == plast) plast = NULL;
                delete pfirst;
                pfirst = paux;
                if (pfirst != NULL) pfirst->prev = NULL;
            }
            else fprintf(stderr, "Error 101 - The list is empty\n"); }

		  //sterge ultimul nod din lista
        void removeLast() {
            struct list_elem<T> *paux;

            if (plast != NULL) {
                paux = plast->prev;
                if (pfirst == plast) pfirst = NULL;
                delete plast;
                plast = paux;
                if (plast != NULL) plast->next = NULL;
            }
            else fprintf(stderr, "Error 102 - The list is empty\n");
        }
        
		  //returneaza un pointer la prima aparitie a lui x in lista
        struct list_elem<T>* findFirstOccurrence(T x) {
            struct list_elem<T> *paux;
            paux = pfirst;
            while (paux != NULL) {
                if (paux->info == x)
                    return paux;
                paux = paux->next;
            }
            return NULL;
        }

		  //returneaza un pointer la ultima aparitie a lui x in lista
        struct list_elem<T>* findLastOccurrence(T x) {
            struct list_elem<T> *paux;
            paux = plast;
            while (paux != NULL) {
                if (paux->info == x)
                    return paux;
                paux = paux->prev;
            }
            return NULL;
        }

		  //sterge prima aparitie a lui x in lista
        void removeFirstOccurrence(T x) {
            struct list_elem<T> *px;

            px = findFirstOccurrence(x);

            if (px != NULL) {
                if (px->prev != NULL)
                    px->prev->next = px->next;
                if (px->next != NULL)
                    px->next->prev = px->prev;

                if (px->prev == NULL) // px == pfirst
                    pfirst = px->next;

                if (px->next == NULL) // px == plast
                    plast = px->prev;

                delete px;
            }
        }

		  //sterge ultima aparitie a lui x in lista
        void removeLastOccurrence(T x) {
            struct list_elem<T> *px;

            px = findLastOccurrence(x);

            if (px != NULL) {
                if (px->prev != NULL)
                    px->prev->next = px->next;
                if (px->next != NULL)
                    px->next->prev = px->prev;

                if (px->prev == NULL) // px == pfirst
                    pfirst = px->next;

                if (px->next == NULL) // px == plast
                    plast = px->prev;

                delete px;
            }
        }
        
        //verifica daca este goala lista
        bool isEmpty() {
            return (pfirst == NULL);
        }
};
#endif
