#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <memory.h>
#include "sortinglib.h"

#define BILLION 1E9

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int *new_rand_array(size_t size) {
    int i;
    int *arr = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++) {
        arr[i] = rand();
    }

    return arr;
}

int *intdup(int const *vec, size_t size) {
    int *p = malloc(size * sizeof(int));
    memcpy(p, vec, size * sizeof(int));
    return p;
}

void multidup(int const *vec, int **out, size_t size, int times) {
    int i;
    for (i = 0; i < times; i++) {
        out[i] = intdup(vec, size);
    }
}

void free_multidup(int **vec, int times) {
    int i;
    for (i = 0; i < times; i++) {
        free(vec[i]);
    }
}

int main(void) {
    // Variaveis de controle.
    int i = 1, j, z;
    int iterations = 5;
    unsigned int seed = 20398457;
    // Vetores utilizados para ordenacao.
    int *vetor, **copias;
    // Variaveis para medicao do tempo de execucao.
    struct timespec request_start, request_end;
    double accum;
    // Variaveis que definem o tamanho do vetor atual.
    size_t base_tam, real_tam;

    srand(seed);

    // Imprime o numero de iteracoes e a seed do srand.
    printf("Seed-%u\n", seed);
    printf("Iterations-%d\n", iterations);

    copias = malloc(sizeof(int*)*iterations);
    while (pow(10,i) <= 10000000) {
        base_tam = (size_t) pow(10, i);

        for (j = 1; j < 2; j++) {
            // Gera um array randomico do tamanho especificado.
            real_tam = base_tam*j;
            if (real_tam > 10000000) {
                break;
            }
            vetor = new_rand_array(real_tam);

            // Imprime o tamanho do vetor atual.
            printf("%zu\n", real_tam);

            /* Testa cada um dos algoritmos de ordenacao */

            if (real_tam <= 50000) {
                multidup(vetor, copias, real_tam, iterations);
                clock_gettime(CLOCK_MONOTONIC, &request_start);
                for (z = 0; z < iterations; z++) {
                    bubble_sort(copias[z], real_tam);
                }
                clock_gettime(CLOCK_MONOTONIC, &request_end);
                accum = (request_end.tv_sec - request_start.tv_sec) +
                        (request_end.tv_nsec - request_start.tv_nsec) / BILLION;
                printf("Bubble Sort-%lf\n", accum);
                free_multidup(copias, iterations);
            }

            if (real_tam <= 50000) {
                multidup(vetor, copias, real_tam, iterations);
                clock_gettime(CLOCK_MONOTONIC, &request_start);
                for (z = 0; z < iterations; z++) {
                    selection_sort(copias[z], real_tam);
                }
                clock_gettime(CLOCK_MONOTONIC, &request_end);
                accum = (request_end.tv_sec - request_start.tv_sec) +
                        (request_end.tv_nsec - request_start.tv_nsec) / BILLION;
                printf("Selection Sort-%lf\n", accum);
                free_multidup(copias, iterations);
            }

            if (real_tam <= 70000) {
                multidup(vetor, copias, real_tam, iterations);
                clock_gettime(CLOCK_MONOTONIC, &request_start);
                for (z = 0; z < iterations; z++) {
                    insertion_sort(copias[z], real_tam);
                }
                clock_gettime(CLOCK_MONOTONIC, &request_end);
                accum = (request_end.tv_sec - request_start.tv_sec) +
                        (request_end.tv_nsec - request_start.tv_nsec) / BILLION;
                printf("Insertion Sort-%lf\n", accum);
                free_multidup(copias, iterations);
            }

            multidup(vetor, copias, real_tam, iterations);
            clock_gettime(CLOCK_MONOTONIC, &request_start);
            for (z = 0; z < iterations; z++) {
                merge_sort(copias[z], 0, real_tam-1);
            }
            clock_gettime(CLOCK_MONOTONIC, &request_end);
            accum = (request_end.tv_sec - request_start.tv_sec) + (request_end.tv_nsec - request_start.tv_nsec)/BILLION;
            printf("Merge Sort-%lf\n", accum);
            free_multidup(copias, iterations);

            multidup(vetor, copias, real_tam, iterations);
            clock_gettime(CLOCK_MONOTONIC, &request_start);
            for (z = 0; z < iterations; z++) {
                heap_sort(copias[z], real_tam);
            }
            clock_gettime(CLOCK_MONOTONIC, &request_end);
            accum = (request_end.tv_sec - request_start.tv_sec) + (request_end.tv_nsec - request_start.tv_nsec)/BILLION;
            printf("Heap Sort-%lf\n", accum);
            free_multidup(copias, iterations);

            multidup(vetor, copias, real_tam, iterations);
            clock_gettime(CLOCK_MONOTONIC, &request_start);
            for (z = 0; z < iterations; z++) {
                quick_sort(copias[z], 0, real_tam-1);
            }
            clock_gettime(CLOCK_MONOTONIC, &request_end);
            accum = (request_end.tv_sec - request_start.tv_sec) + (request_end.tv_nsec - request_start.tv_nsec)/BILLION;
            printf("Quick Sort-%lf\n", accum);
            free_multidup(copias, iterations);

            multidup(vetor, copias, real_tam, iterations);
            clock_gettime(CLOCK_MONOTONIC, &request_start);
            for (z = 0; z < iterations; z++) {
                qsort(copias[z], real_tam, sizeof(int), cmpfunc);
            }
            clock_gettime(CLOCK_MONOTONIC, &request_end);
            accum = (request_end.tv_sec - request_start.tv_sec) + (request_end.tv_nsec - request_start.tv_nsec)/BILLION;
            printf("C stdlib.h qsort-%lf\n", accum);
            free_multidup(copias, iterations);
        }
        i++;
    }
    free(copias);

    return 0;
}