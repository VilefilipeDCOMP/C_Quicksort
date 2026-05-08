#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int *array;
    int low;
    int high;
} Array;

typedef struct {
    int *array;
    int posicaoI;
} ArrayRecebido;

void swap(int* a, int* b) {
   int t = *a;
   *a = *b;
   *b = t;
}

int partition (int arr[], int low, int high) {
   int pivot = arr[high];
   int i = (low - 1);
   for (int j = low; j <= high- 1; j++){
      if (arr[j] <= pivot){
         i++;
         swap(&arr[i], &arr[j]);
      }
   }
   swap(&arr[i + 1], &arr[high]);

   Array parametroNew;
   parametroNew.array = parametro->array;
   parametroNew.low = parametro->low;
   parametroNew.high = pi - 1;

   return (i + 1);
}

void *quickSortThread(void *arg){
    Array *parametro = (Array *)arg;
    if (parametro->low < parametro->high){

        long int pi = partition(parametro->array, parametro->low, parametro->high);

        pthread_t worker1, worker2;  

        Array parametroNew;
        parametroNew.array = parametro->array;
        parametroNew.low = parametro->low;
        parametroNew.high = pi - 1;
        
        pthread_create(&worker1, NULL, quickSortThread, &parametroNew);

        pthread_join(worker1, (void **)&ArrayRecebido);


        Array parametroNew2;
        parametroNew2.array = parametro->array;
        parametroNew2.low = pi + 1;
        parametroNew2.high = parametro->high;

        pthread_create(&worker2, NULL, quickSortThread, &parametroNew2);

        pthread_join(worker1, NULL);
        pthread_join(worker2, NULL);
    //   quickSortThread(arr, low, pi - 1);
    //   quickSortThread(arr, pi + 1, high);
    }
    // ArrayRecebido retorno;
    // retorno.array = retorno->array;
    // retorno.posicaoI = parametro->i + 1;

    return retorno;
}

void printArray(int arr[], int size){
   int i;
   for (i=0; i < size; i++)
      printf("%d ", arr[i]);
   printf("\n");
}

int main(){

   long int n = 100000000;
   int *arr = (int*)malloc(n * sizeof(int));
   srand(0);
   long int i;
   for (i = 0; i < n; i++) {
      arr[i] = rand() % n;
   }
   
   
   clock_t start, end;
   double cpu_time_used;
   pthread_t t1;  

   start = clock();

   Array parametro;
   parametro.array = arr;
   parametro.low = 0;
   parametro.high = n-1;

   pthread_create(&t1, NULL, quickSortThread, &parametro);
   end = clock();

   pthread_join(t1, NULL);
  
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   
   printf("CLOCKS_PER_SEC: %ld \n", CLOCKS_PER_SEC);
   printf("CPU time used is: %f \n", cpu_time_used);
   
   return 0;
}