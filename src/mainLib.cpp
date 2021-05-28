#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <list>
#include "headers.hpp"
using namespace std;

struct Atrib{
	int p; // prioridade da tarefa
	int c; // custo computacional
};

struct Trabalho {
   int tid; // id da thread
   void* (*f)(void*); // função a ser executada
   void* dta; // Parâmetro da função
   void* res; // Retorno de função
};

int qtdProcVirtuais = 0;
int idTrabalho = 0;
static pthread_t *pvs; // processadores virtuais

list <Trabalho *> trabalhosProntos, trabalhosTerminados;

pthread_mutex_t iniciados = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t finalizados = PTHREAD_MUTEX_INITIALIZER;

void *iniciaPV(void *dta) {
	void* res;
	struct Trabalho *t;
	while () {

	}
}

int start (int m) {
	int i, threads;
	pvs = (pthread_t *) malloc(m * sizeof(pthread_t));
	qtdProcVirtuais = m;
	for (i=0; i < m; i++) {
		threads = pthread_create(&pvs[i], NULL, iniciaPV, NULL); //cria thread
		if (threads != 0) {
			return 0;
		}
	} 
	return 1;
}

void finish(){
	while (qtdProcVirtuais >= 0) {
		qtdProcVirtuais--;
	}
};

int spawn( struct Atrib* atrib, void *(*t) (void *), void* dta ) {
	pthread_mutex_lock(&iniciados);

    Trabalho *trab;
	trab = (Trabalho *)malloc(sizeof(Trabalho));
	idTrabalho++;

    trab->tid = idTrabalho;
    trab->f = t;
    trab->dta = dta;

	prontos.push_front(trab);

	pthread_mutex_unlock(&iniciados);

	return idTrabalho;
}

int sync( int tId, void** res );
