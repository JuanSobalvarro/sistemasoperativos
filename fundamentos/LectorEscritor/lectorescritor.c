#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int num_lectores = 0;
int num_escritores = 0;
sem_t mutex;
sem_t mutex_lectores;
sem_t mutex_escritores;

typedef struct args
{
    char type;
    void (*func_ptr)(void *);
    pthread_t *array;
    int size;
} args;

void *invoke(void *uwuargs);

void *lector(void *arg);
void *escritor(void *arg);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: ./lectorescritor num_lectores num_escritores\n");
        return -1;
    }

    srand(time(NULL));

    int nlectores = atoi(argv[1]);
    int nescritores = atoi(argv[2]);
    
    // initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&mutex_lectores, 0, 1);
    sem_init(&mutex_escritores, 0, 1);

    pthread_t lectorinvoker, escritorinvoker;

    // pointers to the args structure
    args *lectores = malloc(sizeof(args));
    args *escritores = malloc(sizeof(args));

    lectores->type = 'l';
    escritores->type = 'e';

    // allocate arrays and its size
    lectores->array = malloc(sizeof(pthread_t) * nlectores);
    escritores->array = malloc(sizeof(pthread_t) * nescritores);

    // printf("size of pthread_t = %d\n", sizeof(pthread_t));

    lectores->size = nlectores;
    escritores->size = nescritores;

    // assign pointers to functions;
    lectores->func_ptr = &lector;
    escritores->func_ptr = &escritor;

    printf("Entering threads...\n");

    // create the threads that will create the lectors and escritors threads
    printf("Invoking lectors...\n");
    if(pthread_create(&lectorinvoker, NULL, invoke, (void *) lectores) != 0)
    {
        printf("Error creating lectors threads\n");
        return -1;
    }
    printf("Invoking escritors...\n");
    if(pthread_create(&escritorinvoker, NULL, invoke, (void *) escritores))
    {
        printf("Error creating escritors thread\n");
        return -1;
    }

    // Esperar a que los hilos terminen
    pthread_join(lectorinvoker, NULL);
    pthread_join(escritorinvoker, NULL);

    // Destruir los semáforos
    sem_destroy(&mutex);
    sem_destroy(&mutex_lectores);
    sem_destroy(&mutex_escritores);
    free(lectores->array);
    free(escritores->array);
    printf("arrays freed\n");
    free(lectores);
    free(escritores);
    
    return 0;
}

void *invoke(void *uwuargs)
{
    args *uwu = (args *) uwuargs; 
    pthread_t temp;
    for (int i = 0; i < uwu->size; i++)
    {
        
        pthread_create(&temp, NULL, uwu->func_ptr, (void *) i);
        uwu->array[i] = temp;
        printf("invoke %c %d with mem %p\n", uwu->type, i, &uwu->array[i]);
    }

    for (int i = 0; i < uwu->size; i++)
    {
        
        pthread_join(uwu->array[i], NULL);
    }
}


void *lector(void *arg) 
{
    //int uwu = *(int *) arg;
    sem_wait(&mutex);
    ++num_lectores;
    printf("lector %d reading...\n", (int *) arg);
    // simulate operation
    sleep(rand()%3 + 1);
    printf("lector %d finished\n", (int *) arg);
    --num_lectores;
    sem_post(&mutex);
}

void *escritor(void *arg)
{
    //int uwu = *(int *) arg;
    sem_wait(&mutex);
    ++num_escritores;
    printf("escritor %d writing...\n", (int *) arg);
    // simulate operation
    sleep(rand()%3 + 1);
    printf("escritor %d finished\n", (int *) arg);
    --num_escritores;
    sem_post(&mutex);
}