#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>

#define SEM_KEY 0x1234
#define SHM_KEY 0x5678
#define SHM_SIZE 1024
#define IPC_ERROR_CODE -1

#define writer 0
#define reader 1

union semaphore{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

void sem_op(int semid, int operation){
    struct sembuf sb = {0, operation, 0};
    semop(semid, &sb, 1);
}

int main(){
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == IPC_ERROR_CODE) {
        printf("Error in creating shared memory segment\n");
        exit(1);
    }

    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == IPC_ERROR_CODE) {
        printf("Error in getting semaphore identifier\n");
        exit(1);
    }

    union semaphore sem_union;
    sem_union.val = 1;
    if(semctl(semid, 0, SETVAL, sem_union) == IPC_ERROR_CODE) {
        printf("Error in initializing semaphore\n");
        exit(1);
    }

    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)IPC_ERROR_CODE) {
        printf("Error in attaching shared memory segment to the process\n");
        exit(1);
    }

    #if writer
        sem_op(semid, -1);
        strcpy(shm_ptr, "Hello from writer process!");
        sem_op(semid, 1);
        shmdt(shm_ptr);
    #endif

    #if reader
        sem_op(semid, -1);
        printf("Reader process read: %s\n", shm_ptr);
        sem_op(semid, 1);
        shmdt(shm_ptr);
    #endif

    return 0;
}
