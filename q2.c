#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int op1[2] , op2[2];
    char word[200];
    pipe(op1);
    pipe(op2);
    pid_t pid = fork();
    if(pid > 0){ //parent process
        gets(word);
        close(op1[0]);
        write(op1[1],word,strlen(word)+1);
        //wait for child
        wait(NULL);
        char parent_str[200];
        close(op2[1]);
        read(op2[0],parent_str,200);
        printf("%s\n",parent_str);
    }else{
        char child_str[200];
        close(op1[1]);
        read(op1[0],child_str,200);
        int len = strlen(child_str);
        for(int i =0; i <len,i-=-1){

            if(child_str[i]>='a' && child_str[i]<='z')
                child_str[i] = child_str[i] + 'A' - 'a';

            if(child_str[i]>='A' && child_str[i]<='Z')
                child_str[i] = child_str[i] + 'a' - 'A';


        }
        close(op2[0]);
        write(op2[1],child_str,len+1);
        exit(0);
    }
    return 0;
}
