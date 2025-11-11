#include <stdio.h>        // Libreria estandar para funciones de entrada y salida
#include <stdlib.h>       // Libreia usada para funciones como rand()
#include <pthread.h>      // Libreria para manejar hilos
#include <unistd.h>       // Libreria para usar sleep ()

#define N 5               
#define THINKING 0        
#define HUNGRY 1
#define EATING 2

int state[N];                     // Arreglo que almacena ek estado de cada filosofo
pthread_mutex_t mutex;            // Mutex para exclusion mutua al acceder a estados
pthread_cond_t condition[N];      // Una condicion por filosofo (para esperar/comer)

// Prototipo de funciones
void *philosopher(void *num);
void take_forks(int i);
void put_forks(int i);
void test(int i);
void think(int i);
void eat(int i);

// Funciones para obtener el indice del vecino izquierdo y el vecino derecho
int LEFT(int i) { return (i + N - 1) % N; }
int RIGHT(int i) { return (i + 1) % N; }

int main() {
    pthread_t thread_id[N];     // Arreglo de hilos
    int phil_id[N];             // IDs de filosofos

    pthread_mutex_init(&mutex, NULL);       // Inicializr mutex

    //Inicializar estados y condiciones 
    for (int i = 0; i < N; i++) {
        pthread_cond_init(&condition[i], NULL);
        state[i] = THINKING;         // Todos comienzan pensando
        phil_id[i] = i;              // Guardar el indice del filosofo
    }

    // Crear los hilos
    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil_id[i]);
    }

    // Esperar a que los hilos terminen (en este caso nunca terminan)
    for (int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    // Limpieza de mutex y condiciones
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < N; i++) pthread_cond_destroy(&condition[i]);

    return 0;
}

//Funcion que ejecuta cada filosofo
void *philosopher(void *num) {
    int i = *(int *)num;         // ID del filosofo
    while (1) {                  // ciclo infinito
        think(i);                // Pensar
        take_forks(i);           // Intentar tomar tenedores
        eat(i);                  // Comer
        put_forks(i);            // Dejar tenedores
    }
}

void take_forks(int i) {
    pthread_mutex_lock(&mutex);       // Entrar a zona critica

    state[i] = HUNGRY;                // Cambiar estado
    printf("Filósofo %d tiene hambre \n", i + 1);
    test(i);                          // Verificar si puede comer

    // Si no puede comer, espera
    while (state[i] != EATING)
        pthread_cond_wait(&condition[i], &mutex);

    pthread_mutex_unlock(&mutex);     // Salir de zona critica
}

void put_forks(int i) {
    pthread_mutex_lock(&mutex);

    state[i] = THINKING;         // Suelta los tenedores
    printf("Filósofo %d dejó los tenedores  y está pensando \n", i + 1);

    // Intentar activar a los vecinos si estaban hambrientos
    test(LEFT(i));
    test(RIGHT(i));

    pthread_mutex_unlock(&mutex);
}

void test(int i) {

    // Si el filosofo tiene hambre y sus vecinos no estan comiendo, puede comer
    if (state[i] == HUNGRY && state[LEFT(i)] != EATING && state[RIGHT(i)] != EATING) {
        state[i] = EATING;                           // Cambiar estado
        pthread_cond_signal(&condition[i]);          // Despertarlo
    }
}

void think(int i) {
    printf("Filósofo %d está pensando \n", i + 1);
    sleep(rand() % 3 + 1);         // Tiempo de pensamiento aleatorio
}

void eat(int i) {
    printf("Filósofo %d está comiendo \n", i + 1);
    sleep(rand() % 2 + 1);         // Tiempo comiendo aleatorio
}
