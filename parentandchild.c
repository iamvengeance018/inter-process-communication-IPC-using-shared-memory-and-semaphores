#include <stdio.h>
#include <unistd.h>

int main(){
    int pipefds[2];
    int returnstatus;
    int pid;
    char writemessage1[20]="Hello";
    char writemessage2[20]="Hi";
    char readmessage[20];
    returnstatus=pipe(pipefds);

    if(returnstatus==-1){
        perror("Unable to create pipe");
        return 1;
    }
    pid=fork();
    if(pid==0){
        read(pipefds[0],readmessage,sizeof(readmessage));
        printf("Child Process - reading from pipe - message1 is %s\n",readmessage);
        read(pipefds[0],readmessage,sizeof(readmessage));
        printf("Child Process - reading from pipe - message2 is %s\n",readmessage);
    }else{
        printf("Parent process - writing to pipe - message1 is %s\n",writemessage1);
        write(pipefds[1],writemessage1,sizeof(writemessage1));
        printf("Parent process - writing to pipe - message2 is %s\n",writemessage2);
        write(pipefds[1],writemessage2,sizeof(writemessage2));
    }
    return 0;
}
