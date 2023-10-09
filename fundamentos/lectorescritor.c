#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int rc = 0;

typedef struct data
{
    char name[20];
    char lastname[20];
    int edad;
} Datos;

unsigned int num_writers, num_readers;
FILE *database;

sem_t mutex, db;

void *reader(void *p);
void *writer(void *p);


int main(int argc, char *argv[])
{

}
