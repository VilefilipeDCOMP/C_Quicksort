/*
 * Utiliza o enderenço do array original, modificando-o diretamente. 
 
 * Como compilar: gcc -o out QuicksortPthread.c -lpthread
 * Como executar: ./out
 * clear && gcc -o out QuicksortPthread.c -lpthread && ./out
 */


#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// UPDATE
// CRIA UM LIMITE PARA QUE O QUICKSORT NÃO FAÇA THREADS INFINITAMENTE
#define THRESHOLD 10000

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

int partition (int *arr, int low, int high) {
   int pivot = arr[high];
   int i = (low - 1);
   for (int j = low; j <= high- 1; j++){
      if (arr[j] <= pivot){
         i++;
         swap(&arr[i], &arr[j]);
      }
   }
   swap(&arr[i + 1], &arr[high]);

   return (i + 1);
}

void quickSort(int arr[], long int low, long int high){
   if (low < high){
      long int pi = partition(arr, low, high);
      quickSort(arr, low, pi - 1);
      quickSort(arr, pi + 1, high);
   }
}

void *quickSortThread(void *arg){
   Array *parametro = (Array *)arg;
   if ((parametro->low < parametro->high) && ((parametro->high - parametro->low) > THRESHOLD)) {
      long int pi = partition(parametro->array, parametro->low, parametro->high);

      pthread_t worker1, worker2;  

      Array parametroNew;
      parametroNew.array = parametro->array;
      parametroNew.low = parametro->low;
      parametroNew.high = pi - 1;
      
      pthread_create(&worker1, NULL, quickSortThread, &parametroNew);

      Array parametroNew2;
      parametroNew2.array = parametro->array;
      parametroNew2.low = pi + 1;
      parametroNew2.high = parametro->high;

      pthread_create(&worker2, NULL, quickSortThread, &parametroNew2);

      pthread_join(worker1, NULL);
      pthread_join(worker2, NULL);
   } else {
      long int pi = partition(parametro->array, parametro->low, parametro->high);
      quickSort(parametro->array, parametro->low, pi - 1);
      quickSort(parametro->array, pi + 1, parametro->high);

   }
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

   Array parametro;
   parametro.array = arr;
   parametro.low = 0;
   parametro.high = n-1;
   
   start = clock();
   pthread_create(&t1, NULL, quickSortThread, &parametro);
   pthread_join(t1, NULL);
   end = clock();

   // printArray(arr, n);
  
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   
   printf("CLOCKS_PER_SEC: %ld \n", CLOCKS_PER_SEC);
   printf("CPU time used is: %f \n", cpu_time_used);
   
   return 0;
}