#include <stdio.h>        // Libreria estandar para funciones de entrada y salida
#include <stdlib.h>       // Libreia usada para funciones como rand()
#include <pthread.h>      // Libreria para manejar hilos
#include <unistd.h>       // Libreria para usar sleep ()

#define N 5               // Numero de filosos
#define THINKING 0        
#define HUNGRY 1
#define EATING 2

int state[N];
pthread_mutex_t mutex;        
pthread_cond_t condition[N];   

void *philosopher(void *num);
void take_forks(int i);
void put_forks(int i);
void test(int i);
void think(int i);
void eat(int i);

int LEFT(int i) { return (i + N - 1) % N; }
int RIGHT(int i) { return (i + 1) % N; }

int main() {
    pthread_t thread_id[N];
    int phil_id[N];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < N; i++) {
        pthread_cond_init(&condition[i], NULL);
        state[i] = THINKING;
        phil_id[i] = i;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil_id[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < N; i++) pthread_cond_destroy(&condition[i]);

    return 0;
}

void *philosopher(void *num) {
    int i = *(int *)num;
    while (1) {
        think(i);
        take_forks(i);
        eat(i);
        put_forks(i);
    }
}

void take_forks(int i) {
    pthread_mutex_lock(&mutex);

    state[i] = HUNGRY;
    printf("Filósofo %d tiene hambre 🍽️\n", i + 1);
    test(i);

    
    while (state[i] != EATING)
        pthread_cond_wait(&condition[i], &mutex);

    pthread_mutex_unlock(&mutex);
}

void put_forks(int i) {
    pthread_mutex_lock(&mutex);

    state[i] = THINKING;
    printf("Filósofo %d dejó los tenedores 🥢 y está pensando 🧠\n", i + 1);
  
    test(LEFT(i));
    test(RIGHT(i));

    pthread_mutex_unlock(&mutex);
}

void test(int i) {
    
    if (state[i] == HUNGRY && state[LEFT(i)] != EATING && state[RIGHT(i)] != EATING) {
        state[i] = EATING;
        pthread_cond_signal(&condition[i]);
    }
}

void think(int i) {
    printf("Filósofo %d está pensando 🧠\n", i + 1);
    sleep(rand() % 3 + 1);
}

void eat(int i) {
    printf("Filósofo %d está comiendo 🍝\n", i + 1);
    sleep(rand() % 2 + 1);
}
