#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_NAME "/my_named_sem"
#define SHM_KEY 0x5678
#define SHM_SIZE 1024
#define writer 0
#define reader 1

int main(){
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        printf("Error in creating shared memory segment\n");
        exit(1);
    }
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) {
        printf("Error in attaching shared memory segment to the process\n");
        exit(1);
    }
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 3);
    if (sem == SEM_FAILED) {
        printf("Error in sem_open\n");
        exit(1);
    }
#if writer
    if (sem_wait(sem) == -1) {
        printf("Error in sem_wait\n");
        exit(1);
    }
    strcpy(shm_ptr, "Hello from writer process!");
    printf("Writer process wrote to shared memory.\n");
    if (sem_post(sem) == -1) {
        printf("Error in sem_post\n");
        exit(1);
    }
    shmdt(shm_ptr);
#endif
#if reader
    if (sem_wait(sem) == -1) {
        printf("Error in sem_wait\n");
        exit(1);
    }
    printf("Reader process read: %s\n", shm_ptr);
    if (sem_post(sem) == -1) {
        printf("Error in sem_post\n");
        exit(1);
    }
    shmdt(shm_ptr);
#endif
    if (sem_close(sem) == -1) {
        printf("Error in sem_close\n");
        exit(1);
    }
    return 0;
}
