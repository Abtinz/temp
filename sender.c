#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
    key_t key = ftok("sharedMemoryFile",65);
    int sahred_memory_id = shmget(key,1024,0666|IPC_CREAT);
    char *data = (char*) shmat(sahred_memory_id,(void*)0,0);
    printf("WRITE DATA:");
    gets(data);
    printf("data has been written:%s\n",data);
    shmdt(data);

    return 0;
}
