Que hace el algoritmo del banquero?

El algoritmo del banquero se usa en la asignacion de recursos y evitar el interbloqueo(deadlock).

Simula la asignacion de recursos para la cantidad maxima de estos antes de hacer un check de safe state
para ver por actividades potenciales y ver si la asignacion deberia ser permitida y continuar.

Algoritmo para comprobar si el sistema esta en un estado seguro(safe state):

1. tenemos dos arrays, work y finish, de tama;o m y n:
work = available
finish = false

2. Iterar hasta encontrar una 'i' en que:
    A. finish[i] = false & need[i] <= work // para cada elemento j need[i][j] <= work[j]
        // donde need es la matriz nprocesos x nrecursos need = max - allocation
    B. si no es encontrado un i pasar al paso 4

3. actualizar work
    A. work = work + allocation
    B. finish[i] = true
    C. pasar a paso 2
4. Iterar en todos los elementos i
    A. si finish[i] = true // para todos los elementos
    El sistema esta en estado seguro(safe state)

Resource-request algoritmo:
    // donde request[i] es el array request del processi. Osea request[i][j] = k significa que
    // el proceso i quiere k instancias del recurso j
    1. Si request[i] <= need[i]
        A. ir a paso 2. Si es false significa que el proceso ha pedido mas de lo que necesita
        por lo tanto hay una error, asi que lanzar ERROR.
    2. Si request[i] <= Available
        A. Ir a paso 3. Sino el proceso debe esperar debido a que los recursos estan ocupados.
    3. Ahora el sistema debe pretender que haber asignado los recursos pedidos por el proceso
    modificando los estados de las matrices
        A. available = available - request[i]
        B. allocation[i] = allocation[i] + request[i]
        C. need[i] = need[i] - request[i] 


TESTCASES

CASO 1: estado inseguro
#define nproc 4
#define nrec 5

// available resources and its instances
int available[nrec] = {0, 1, 2, 3, 4};

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

CASO 2: seguro P1 => P3 => P4 => P0 => P2
#define nproc 5
#define nrec 3

int available[nrec] = { 3, 3, 2 };

int max[nproc][nrec] =
{
    { 7, 5, 3 }, 
    { 3, 2, 2 },
    { 9, 0, 2 },
    { 2, 2, 2 },
    { 4, 3, 3 }
};

int allocation[nproc][nrec] =
{
    { 0, 1, 0 },
    { 2, 0, 0 },
    { 3, 0, 2 },
    { 2, 1, 1 },
    { 0, 0, 2 }
};

CASO 3: seguro P1 => P3 => P4 => P0 => P2
#define nproc 5
#define nrec 3 

int available[3] = { 2, 3, 2 }; 

int max[5][3] = 
{ 
    { 7, 6, 3 },  
    { 3, 2, 2 },  
    { 8, 0, 2 },  
    { 2, 1, 2 },  
    { 5, 2, 3 } 
};

int allocation[5][3] = 
{ 
    { 0, 0, 1 },  
    { 3, 0, 0 }, 
    { 1, 0, 1 }, 
    { 2, 3, 2 }, 
    { 0, 0, 3 } 
};

CASO 4: seguro P0 => P1 => P2 => P3
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