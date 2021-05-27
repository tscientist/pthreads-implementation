#include <pthread.h>

int start (int m);
//lança o núcleo de execução, instanciando os 'M' processadores virtuais - retorno = 0(falha) ou 1(deu bom)
void finish();
//retorna após todos os PV terem terminado sua execução
int spawn( struct Atrib* atrib, void *(*t) (void *), void* dta );
//lança a execução da tarefa descrita - atrib = atributos(struct), t = função a ser executada, dta = parametros da função, retorno = 0(falha) ou 1(deu bom)
int sync( int tId, void** res );
//invoca a thread que deve ser sincronizada - tId = ID da thread, res = resultado da execução da thread, retorno = 0(falha) ou 1(deu bom) 