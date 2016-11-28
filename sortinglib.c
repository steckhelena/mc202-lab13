#include <stdio.h>
#include "sortinglib.h"

void bubble_sort(int *vec, size_t length) {
    size_t i, new_length;
    int temp;
    do {
        new_length = 0;
        for (i = 1; i < length - 1; i ++) {
            if (vec[i] < vec[i-1]) {
                temp = vec[i];
                vec[i] = vec[i-1];
                vec[i-1] = temp;
                new_length = (size_t)i;
            }
        }
        length = new_length;
    } while (length != 0);
}

void selection_sort(int *vec, size_t length) {
    size_t i, j, jMin;
    int temp;

    for (i = 0; i < length-1; i++) {
        // Assume que o elemento minimo eh o primeiro da parte ainda nao ordenada.
        jMin = i;
        for (j = i+1; j < length; j++) {
            if (vec[j] < vec[jMin]) {
                jMin = j; // Atualiza o elemento minimo.
            }
        }

        // Se o elemento minimo nao for o primeiro entao muda de lugar.
        if (jMin != i) {
            temp = vec[i];
            vec[i] = vec[jMin];
            vec[jMin] = temp;
        }
    }
}

void insertion_sort(int *vec, size_t length) {
    size_t i, j;
    int temp;

    for (i = 1; i < length; i++) {
        temp = vec[i];
        j = i - 1;
        while(j >= 0 && vec[j] > temp) {
            vec[j+1] = vec[j];
            if (j != 0) {
                j = j - 1;
            } else {
                // Previne overflow do size_t.
                break;
            }
        }
        vec[j+1] = temp;
    }
}

void merge_sort(int *vec, size_t start, size_t end) {
    int *temp;
    size_t i, j, k;
    size_t half_len;
    
    if(start == end) return;

    // ordenacao recursiva das duas metades
    half_len = (start + end) / 2;
    merge_sort(vec, start, half_len);
    merge_sort(vec, half_len + 1, end);

    // intercalacao no vetor temporario t
    i = start;
    j = half_len + 1;
    k = 0;
    temp = (int *) malloc(sizeof(int) * (end - start + 1));

    while(i < half_len + 1 || j  < end + 1) {
        if (i == half_len + 1 ) { // i passou do final da primeira metade, pegar v[j]
            temp[k] = vec[j];
            j++;
            k++;
        }
        else {
            if (j == end + 1) { // j passou do final da segunda metade, pegar v[i]
                temp[k] = vec[i];
                i++;
                k++;
            }
            else {
                if (vec[i] < vec[j]) {
                    temp[k] = vec[i];
                    i++;
                    k++;
                }
                else {
                    temp[k] = vec[j];
                    j++;
                    k++;
                }
            }
        }

    }
    // copia vetor intercalado para o vetor original
    for(i = start; i <= end; i++) {
        vec[i] = temp[i - start];
    }
    free(temp);
}

void heap_sort(int *vec, size_t length) {
    size_t i, j;
    int temp;

    for (i = length/2; i >= 0; i--) {
        temp = vec[i];
        j = 2*i + 1;
        while (j < length) {
            if (j < length-1 && vec[j+1] >= vec[j]) {
                j++;
            }
            if (temp > vec[j]) {
                break;
            } else if (temp <= vec[j]) {
                vec[(j-1)/2] = vec[j];
                j = 2*j + 1;
            }
        }
        vec[(j-1)/2] = temp;

        // Previne overflow do size_t
        if (i == 0) {
            break;
        }
    }

    for (i = length-1; i > 0; i--) {
        temp = vec[i];
        vec[i] = vec[0];
        vec[0] = temp;
        j = 1;
        while (j < i) {
            if (j < i-1 && vec[j+1] >= vec[j]) {
                j++;
            }
            if (temp > vec[j]) {
                break;
            } else if (temp <= vec[j]) {
                vec[(j-1)/2] = vec[j];
                j = 2*j + 1;
            }
        }
        vec[(j-1)/2] = temp;
    }
}

void quick_sort(int *vec, size_t start, size_t end) {
    int temp;
    int size = end - start + 1;

    /* Se os tamanhos forem pequenos realiza uma ordenacao manual. */
    if (size <= 1) {
        return;
    } else if (size <= 2) {
        if (vec[start] > vec[end]) {
            temp = vec[start];
            vec[start] = vec[end];
            vec[end] = temp;
        }
        return;
    } else if (size <= 3) {
        if (vec[start] > vec[end - 1]) {
            temp = vec[end-1];
            vec[end-1] = vec[start];
            vec[start] = temp;
        }
        if (vec[start] > vec[end]) {
            temp = vec[start];
            vec[start] = vec[end];
            vec[end] = temp;
        }
        if (vec[end-1] > vec[end]) {
            temp = vec[end];
            vec[end] = vec[end-1];
            vec[end-1] = temp;
        }
    }

    /* Aplica a mediana de 3. */
    size_t mid = (start + end)/2;
    int pivot;

    if (vec[end] < vec[start]) {
        temp = vec[start];
        vec[start] = vec[end];
        vec[end] = temp;
    }
    if (vec[mid] < vec[start]) {
        temp = vec[start];
        vec[start] = vec[mid];
        vec[mid] = temp;
    }
    if (vec[end] < vec[mid]) {
        temp = vec[end];
        vec[end] = vec[mid];
        vec[mid] = temp;
    }

    // Inverte o ultimo elemento
    temp = vec[end-1];
    vec[end-1] = vec[mid];
    vec[mid] = temp;

    // Define o pivot.
    pivot = vec[end-1];

    /* Particiona o array. */
    size_t left = start;
    size_t right = end - 1;

    while (1) {
        while (vec[++left] < pivot); // Anda com o ponteiro da esquerda.
        while (vec[--right] > pivot); // Anda com o ponteiro da direita.
        if (left >= right) { // Para o loop caso os dois ponteiros se encontrem.
            break;
        } else { // Troca os dois elementos caso ainda seja possivel andar.
            temp = vec[left];
            vec[left] = vec[right];
            vec[right] = temp;
        }
    }

    // Restaura o pivot.
    temp = vec[left];
    vec[left] = vec[end-1];
    vec[end-1] = temp;

    quick_sort(vec, start, left-1);
    quick_sort(vec, left+1, end);
}

void counting_sort(int *vec, size_t length, size_t max_value) {
    size_t i;
    int *count = calloc(max_value, sizeof(int));
    int *output = malloc(sizeof(int)*length);

    for (i = 0; i < length; i++) {
        count[vec[i]]++;
    }

    for (i = 1; i <= max_value; i++) {
        count[i] += count[i-1];
    }

    for (i = 0; i < length; i++) {
        output[count[vec[i]] - 1] = vec[i];
        --count[vec[i]];
    }

    for (i = 0; i < length; i++) {
        vec[i] = output[i];
    }

    free(count);
    free(output);
}