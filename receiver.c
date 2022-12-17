#include "protocol.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
    key_t key = ftok("sharedMemoryFile",65);//shread memory key
    int sahred_memory_id = shmget(key,1024,0666|IPC_CREAT);//shared memory id
    char *data = (char*) shmat(sahred_memory_id,(void*)0,0);//data pointer for special shared memory id
    printf("data read from memory:%s\n",data);//this is receiver so we need to read the data and print it
    /*
         detaches from the calling process's address space the shared 
         memory segment located at the address specified by the argument shmaddr
    */
    shmdt(data);
    shmctl(sahred_memory_id,IPC_RMID,NULL); //Shared memory segment to be removed and its free!
    return 0;
}
