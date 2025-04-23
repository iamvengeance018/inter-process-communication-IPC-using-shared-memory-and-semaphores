#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

#define SHM_KEY 0x5678
#define SHM_SIZE 1024
#define writer 0
#define reader 1

int main() {
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        printf("Error creating shared memory\n");
        exit(1);
    }

    void *shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
        printf("Error attaching shared memory\n");
        exit(1);
    }

    sem_t *sem = (sem_t *)shm_ptr;
    char *message = (char *)(shm_ptr + sizeof(sem_t));

#if writer
    if (sem_init(sem, 1, 3) == -1) {
        printf("Error initializing semaphore\n");
        exit(1);
    }

    if (sem_wait(sem) == -1) {
        printf("Error in sem_wait\n");
        exit(1);
    }

    strcpy(message, "Hello from writer process!");
    printf("Writer wrote to shared memory\n");

    if (sem_post(sem) == -1) {
        printf("Error in sem_post\n");
        exit(1);
    }

    shmdt(shm_ptr);

    if (sem_destroy(sem) == -1) {
        printf("Error in sem_destroy\n");
        exit(1);
    }

    shmctl(shmid, IPC_RMID, NULL);
#endif

#if reader
    if (sem_wait(sem) == -1) {
        printf("Error in sem_wait\n");
        exit(1);
    }

    printf("Reader read: %s\n", message);

    if (sem_post(sem) == -1) {
        printf("Error in sem_post\n");
        exit(1);
    }

    shmdt(shm_ptr);
#endif

    return 0;
}
