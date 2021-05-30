#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <list>
#include "headers.hpp"
using namespace std;

struct Trabalho {
   int tid; // id da thread
   void* (*f)(void*); // função a ser executada
   void* dta; // Parâmetro da função
   void* res; // Retorno de função
};

int qtdProcVirtuais = 0;
int idTrabalho = 0;
list<struct Trabalho *> trabalhosProntos, trabalhosTerminados;
static pthread_t *pvs; // processadores virtuais
pthread_mutex_t iniciados = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
pthread_mutex_t finalizados = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
bool fim = false;

void *iniciaPV(void *dta);

void armazenaResultados(struct Trabalho *trabalho);

struct Trabalho *iniciaTrabalho();

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

int spawn(struct Atrib* atrib, void *(*t) (void *), void* dta ) {
	pthread_mutex_lock(&iniciados);

  struct Trabalho *trab;
	trab = (Trabalho *)malloc(sizeof(struct Trabalho));
	idTrabalho++;

    trab->tid = idTrabalho;
    trab->f = t;
    trab->dta = dta;

	trabalhosProntos.push_front(trab);

	pthread_mutex_unlock(&iniciados);

	return idTrabalho;
}

int sync( int tId, void** res ) {
  Trabalho *resTrab, *trab;
  list<Trabalho *>::iterator search;
  //caso 2 - busca na lista de trabalhos terminados
for (search = trabalhosTerminados.begin(); search != trabalhosTerminados.end(); ++search) {
    if ((*search)->tid == tId) {
      pthread_mutex_lock(&iniciados);
      trab = *search;
      trabalhosTerminados.erase(search);
      *res = trab->res;
      pthread_mutex_unlock(&iniciados);
    }
  }

  //caso 1 - busca na lista de trabalhos prontos o 2 vem primeiro pois caso ache nele não é necessario executar nenhum outro.
  for (search = trabalhosProntos.begin(); search != trabalhosProntos.end(); ++search) {
    if ((*search)->tid == tId) {
      pthread_mutex_lock(&iniciados);
      trab = *search;
      armazenaResultados(trab);
      *res = trab->res;
      trabalhosProntos.erase(search);
      pthread_mutex_unlock(&iniciados);
    }
  }

  //caso 3 - resolver a tarefa em execução e retornar
  pthread_mutex_lock(&iniciados);
  resTrab = iniciaTrabalho();
  pthread_mutex_unlock(&iniciados);
  if (resTrab != NULL) {
    pthread_mutex_lock(&iniciados);
    armazenaResultados(resTrab);
    *res = resTrab->res;
    pthread_mutex_unlock(&iniciados);
  }
}

void *iniciaPV(void *dta) {
  void* res;
  struct Trabalho *t;
  while ((fim == false) && (trabalhosProntos.size() != NULL)) {
    pthread_mutex_lock(&iniciados);
    t = iniciaTrabalho();
    pthread_mutex_unlock(&iniciados);
    armazenaResultados(t);
  }
  return NULL;
}

void armazenaResultados(struct Trabalho *trabalho) {  
  void * res;  
  res = trabalho->f(trabalho->dta);  
  pthread_mutex_lock(&finalizados);  
  trabalho->res = res;
  trabalhosTerminados.push_front(trabalho);  
  pthread_mutex_unlock(&finalizados);
}

struct Trabalho *iniciaTrabalho() {
  if (trabalhosProntos.empty()) {
    return NULL;
  }
  struct Trabalho *trabalho = trabalhosProntos.front();
  trabalhosProntos.pop_front();
  return trabalho;
}