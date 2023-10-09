#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

typedef sem_t Semaphore;

typedef struct {
    double balance;
    Semaphore *S;
} Account;

void wait(Semaphore *S);
void signal(Semaphore *S);
double withdraw(Account *acct, double amt);
Account *make_account(double balance);
Semaphore *make_semaphore(int value);

int main()
{
    Account *acc1 = make_account(20000);
    Account *acc2 = make_account(10000);
    return 0;
}

void signal(Semaphore *S)
{
    int n = sem_post(S);
    if (n != 0) printf("sem_post FAILED");
}

void wait(Semaphore *S)
{
    int n = sem_wait(S);
    
    if (n != 0)
    {
        printf("sem_wait FAILED");
    }
}

Account *make_account(double balance)
{
    Account *acc = malloc(sizeof(Account));
    acc->balance = balance;
    acc->S = make_semaphore(1);
}

double withdraw(Account *acct, double amt)
{
    double bal;
    wait(acct->S);
    bal = acct->balance;
    bal -= amt;
    acct->balance = bal;
    acct->balance = bal;
    signal(acct->S);
    return bal;
}

Semaphore *make_semaphore(int value)
{
    Semaphore *sem = check_malloc(sizeof(Semaphore));
    int n = sem_init(sem, 0, value);
    if (n != 0) perror_exit("sem_init failed");
    return sem;
}