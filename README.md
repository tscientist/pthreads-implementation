#  Implementação com Pthreads - SO


#### Funcionalidades:

- Programa executa o Fibonacci.
- Utiliza como algoritmo de escalonamento: FILA

Desenvolvimento de um código em um modelo onde **n** tarefas são executadas sobre **m** processadores virtuais (pvs).

#### Limitações:
- O programa não consegue encontrar o exato resultado do fibonacci, pois ocorrem alguns erros relacionados aos lock's e unlock's.

## Instalação

Para executar o programa você precisa ter o g++ instalado e estar em ambiente linux, pois o pthread é feito para o posix(linux).

É preciso clonar o repositório para testar. No terminal digite: 

```sh
git clone https://github.com/tscientist/implementation_pthreads.git
```
Para utilizar o makefile é preciso instalar 
```sh
sudo apt install make
```

## Testes

Para compilar digite: 

```sh
make all
```

E para rodar o fibonacci: 

```sh
make input
```


