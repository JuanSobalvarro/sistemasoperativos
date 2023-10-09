#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

pthread_mutex_t cerrojo;

void P(int i);

int main(int argc, char *argv[])
{
    pthread_mutex_init(&cerrojo, NULL);

    pid_t son = fork();
    pid_t son1 = fork();

    printf("son %d in p %d\n", son, getpid());
    printf("son1 %d in p %d\n", son1, getpid());

    if (son < 0 || son1 < 0)
    {
        printf("Error forking process");
        return -1;
    }
    //P(getpid());

    return 0;
}

void P(int i)
{
    int llavei = i;
    while (true)
    {
        pthread_mutex_lock(&cerrojo);
        printf("Proceso %d currently working\n", i);
        // Sección crítica uwu nya
        printf("Proceso %d finished working\n", i);
        pthread_mutex_unlock(&cerrojo);
        break;
    }
}
