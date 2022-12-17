#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    
    //the two process and pipelines
    int op1[2] , op2[2];
    //shared data
    char word[200];
    
    //pipes created with two chanels
    pipe(op1);
    pipe(op2);
    
    /*
       HERE WE CREATE OUR CHILD PROCESS FOR PIPE COMINICUATION
       pip id > 0 --> we have a child and this is parent process
       pip id == 0 --> we have a child and this is parent
    */
    pid_t pid = fork();
    if(pid > 0){ //parent process
        gets(word); //our input
        close(op1[0]); // this channel is closed for pipeline data sharing
        write(op1[1],word,strlen(word)+1); // writing our data on sender channel
        wait(NULL);//wait for child
        char parent_str[200];
        close(op2[1]);
        read(op2[0],parent_str,200); //read from second side channel of pipline
        printf("%s\n",parent_str); // the resault
    }

    else if(pid == 0){//child process
        char child_str[200];
        close(op1[1]);
        read(op1[0],child_str,200);//read from parent process
        int len = strlen(child_str);//for iteration
        for(int i =0; i <len,i-=-1){
            //for lower case chars
            if(child_str[i]>='a' && child_str[i]<='z')
                child_str[i] = child_str[i] + 'A' - 'a';
            //for upper case chars
            if(child_str[i]>='A' && child_str[i]<='Z')
                child_str[i] = child_str[i] + 'a' - 'A';

        }
        close(op2[0]);
        write(op2[1],child_str,len+1);//write on pipeline (new data)
        exit(0);//terminate child
    }
    return 0;
}
