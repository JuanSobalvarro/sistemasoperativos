#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int num_lectores = 0;
int num_escritores = 0;
sem_t mutex_lectores;
sem_t mutex_escritores;

void *lector(void *arg);
void *escritor(void *arg);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: ./lectorescritor num_lectores num_escritores\n");
        return -1;
    }

    int nlectores = atoi(argv[1]);
    int nescritores = atoi(argv[2]);
    
    // initialize semaphores
    sem_init(&mutex_lectores, 0, 1);
    sem_init(&mutex_escritores, 0, 1);

    int lectorid[nlectores], escritorid[nescritores];

    pthread_t lectores[nlectores];
    pthread_t escritores[nescritores];

    for (int i = 0; i < nlectores; i++)
    {
        lectorid[i] = i;
        pthread_create(&lectores[i], NULL, lector,(void *) &lectorid[i]);
    }

    for (int i = 0; i < nescritores; i++)
    {
        escritorid[i] = i;
        pthread_create(&escritores[i], NULL, escritor,(void *) &escritorid[i]);
    }

    // Esperar a que los hilos terminen (esto nunca sucede en este ejemplo)
    for (int i = 0; i < nlectores; ++i) {
        pthread_join(lectores[i], NULL);
    }

    for (int i = 0; i < nescritores; ++i) {
        pthread_join(escritores[i], NULL);
    }

    // Destruir los semáforos
    sem_destroy(&mutex_lectores);
    sem_destroy(&mutex_escritores);

    return 0;
}

void *lector(void *arg)
{
    int uwu = *(int *) arg;
    while(1)
    {
        sem_wait(&mutex_lectores);
        num_lectores++;
        if (num_lectores == 1) {
            sem_wait(&mutex_escritores);  // Bloquear escritores si es el primer lector
        }
        sem_post(&mutex_lectores);

        // seccion critica para lectores
        printf("Lector %d en la seccion critica\n", uwu);
        sleep(1);

        sem_wait(&mutex_lectores);
        num_lectores--;
        if (num_lectores == 0)
        {
            sem_post(&mutex_escritores);
        }
        sem_post(&mutex_lectores);

        printf("Lector %d fuera de la seccion critica\n", uwu);
    }
}

void *escritor(void *arg)
{
    int uwu = *(int *) arg;
    while (1)
    {
        sem_wait(&mutex_escritores);
        num_escritores++;

        printf("Escritor %d en la seccion critica\n", uwu);
        sleep(1);
        printf("Escritor %d fuera de la seccion critica\n", uwu);

        num_escritores--;
        sem_post(&mutex_escritores);
    }
}