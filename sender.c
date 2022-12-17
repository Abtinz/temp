#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
    
    key_t key = ftok("sharedMemoryFile",65);//shread memory key
    int sahred_memory_id = shmget(key,1024,0666|IPC_CREAT);//shared memory id
    char *data = (char*) shmat(sahred_memory_id,(void*)0,0);//data pointer for special shared memory id
    printf("WRITE DATA:");
    gets(data);
    printf("data has been written:%s\n",data);//this is sender so we need to write the data and print it
    shmdt(data);
    return 0;
    
}
