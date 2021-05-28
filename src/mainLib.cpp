#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <list>
#include "headers.hpp"

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

list<trabalho *> trabalhosProntos, trabalhosTerminados;
int qtdProcVirtuais = 0;
static pthread_t *pvs; // processadores virtuais
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t unlock = PTHREAD_MUTEX_INITIALIZER;

void *iniciaPV(void *dta) {
  void* res;
  struct Trabalho *t;
  while () {

  }
}

int start (int m) {
  int i, threads;
  pvs = (pthread_t *) malloc(m * sizeof(pthread_t));
  for (i=0; i < m; i++) {
    threads = pthread_create(&pvs[i], NULL, iniciaPV, NULL); //cria thread
    if (threads != 0) {
      return 0;
    }
  } 
  return 1;
}

void finish();

int spawn( struct Atrib* atrib, void *(*t) (void *), void* dta ){
  Trabalho *newTrab = (Trabalho *) malloc(sizeof(Trabalho));
  
}

int sync( int tId, void** res );