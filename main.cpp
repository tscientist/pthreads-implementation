#include <stdio.h>
#include <stdlib.h>
#include "headers.hpp"

void *fibo(void *dta);

int main(){
    Atrib escalo;
    int n, *r, id;
    int nThreads,response_spawn;
    int fib;
    
    printf("Escolha o fibinho para ser calculado: \n");
    scanf("%d",&fib);

    printf("Escolha o numero de THREADS: \n");
    scanf("%d",&nThreads);


    start(nThreads);
    escalo.p = 0;
    escalo.c = fib;

    response_spawn = spawn(&escalo,fibo,&fib);
    sync(response_spawn,(void **)&r);
		printf("Fibonacci (%d) = %d \n", n, *r);
		finish();
    return 0;
}

void *fibo(void *dta)
{
	int *n = (int *)dta;
	int *n1, *n2, *r1, *r2;
	int *r = (int *)malloc(sizeof(int));
	struct Atrib a1, a2;
	int t1, t2;

	if (*n <= 2)
	{
		*r = 1;
	}
	else
	{
		n1 = (int *)malloc(sizeof(int));
		r1 = (int *)malloc(sizeof(int));
		r2 = (int *)malloc(sizeof(int));
		*n1 = (*n) - 1;
		a1.p = 0;
		a1.c = *n1;
		t1 = spawn(&a1, fibo, (void *)n1);
		n2 = (int *)malloc(sizeof(int));
		*n2 = *n - 2;
		a2.p = 0;
		a1.c = *n2;
		t2 = spawn(&a2, fibo, (void *)n2);
		sync(t1, (void **)&r1);
		sync(t2, (void **)&r2);
		printf("%p\n %p ", r1, r2);
		*r = *r1 + *r2;
		free(r1);
		free(r2);
		free(n1);
		free(n2);
	}
	return r;
}
