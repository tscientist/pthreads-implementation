#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
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
list<trabalho *> trabalhosProntos, trabalhosTerminados;
static pthread_t *pvs; // processadores virtuais
pthread_mutex_t iniciados = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
pthread_mutex_t finalizados = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
bool fim = false;

void *iniciaPV(void *dta);

void armazenaResultados(struct Trabalho *trabalho);

int start (int m) {
  int i, threads;
  pvs = (pthread_t *) malloc(m * sizeof(pthread_t));
  qtdProcVirtuais = m;
  fim = 0;
  for (i=0; i < m; i++) {
    threads = pthread_create(&pvs[i], NULL, iniciaPV, NULL);
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

void *iniciaPV(void *dta) {
  void* res;
  //struct Trabalho *t;
  while ((fim == false) && (trabalhosProntos.size() != NULL)) {
    pthread_mutex_lock(&iniciados);
    //t = pegaTrabalho(trabalhosProntos);
    pthread_mutex_unlock(&iniciados);
    res = armazenaResultados(t);
  }
  return NULL;
}

void armazenaResultados(struct Trabalho *trabalho) {  
  void* res;  
  res = trabalho->f(trabalho->dta);  
  pthread_mutex_lock(&finalizados);  
  trabalho->res = res;
  trabalhosTerminados.push_front(trabalho);  
  pthread_mutex_unlock(&finalizados);
}