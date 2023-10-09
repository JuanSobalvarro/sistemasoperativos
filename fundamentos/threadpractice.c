#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int value = 0;
void *runner(void *param); // thread

int main(int argc, char *argv[])
{
    int pid;
    pthread_t tid;
    pthread_attr_t attr;

    pid = fork();
    
    if (pid == 0) 
    { 
        // son process 
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, NULL);
        pthread_join(tid, NULL);
        printf ("son: value = %d\n", value);
        return -1;
    }
    else if (pid > 0) 
    {
        wait(NULL);
        printf ("parent: value = %d\n", value);
    }
}

void *runner(void *param)
{
    value = 5;
    pthread_exit(0);
}