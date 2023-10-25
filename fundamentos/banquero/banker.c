#include <stdio.h>
#define nproc 4
#define nrec 5

// available resources and its instances
int available[nrec] = {3, 4, 5, 6, 7};

// max demand per process Pi has max demand of resource Rj
int max[nproc][nrec] = 
{
    {0, 1, 2, 3, 4},
    {1, 2, 3, 4, 5},
    {2, 3, 4, 5, 6},
    {3, 4, 5, 6, 7}    
};

// each process Pi has k instance allocated of resource Rj
int allocation[nproc][nrec] =
{
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

// need = max - allocation
int need[nproc][nrec];

/*
function to determine if the system is in a safe state,
it also modifies the safesequence
*/ 
int safeState(int *seq);
int resourceRequest();

int main()
{
    // safe sequence array
    int safeseq[nproc];

    if (safeState(safeseq) == 1)
    {
        printf("The system is a safe state.\nSafe Sequence:\n");
        for (int i = 0; i < nproc - 1; i++)
        {
            printf("P%d => ", safeseq[i]);
        }
        printf("P%d\n", safeseq[nproc - 1]);
    }
    else
    {
        printf("The system is not a safe state.\n");
    }

    
    return 0;
}

int safeState(int *seq)
{
    // finish array
    int finish[nproc] = {0};
    int ifound, safestate;
    int *array = seq;

    // calculate need matrix
    for (int i = 0;  i < nproc; i++)
    {
        for (int j = 0; j < nrec; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // iterate nproc times, so it will write in finish nproc times
    for (int p = 0; p < nproc; p++)
    {
        
        // found a process i that meets the conditions
        for (int i = 0; i < nproc; i++)
        {
            ifound = 1;
            if (finish[i] == 1)
            {
                continue;
            }
            for (int j = 0; j < nrec; j++)
            {
                // if one of the resources instance needed is greater than the available
                // this process is not what we are looking for
                if (need[i][j] > available[j])
                {
                    ifound = 0;
                    break;
                }
            }
            // if we found a process i then we execute step 3
            if (ifound == 1)
            {
                *array = i;
                ++array;   
                for (int j = 0; j < nrec; j++)
                {
                    available[j] += allocation[i][j]; 
                }
                finish[i] = 1;
                continue;
            }
        }
        // if a process i is not found we need to pass to step 4
        if (ifound == 0)
        {
            break;
        }
    }

    // step 4
    for (int i = 0; i < nproc; i++)
    {
        if (finish[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}