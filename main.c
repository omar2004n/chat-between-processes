#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<time.h>


int pid_send(pid_t id)
{
    FILE *f;
    char c='|';
    f=fopen("pid.txt","a");
    fprintf(f,"%ld|",id);
    fclose(f);
    return 0;
    
}

int pid_get(pid_t pid1)
{
    FILE *f;
    char c,pid[40];
    int a=0,i=0; 

    f = fopen("pid.txt","r");
    while((c=getc(f))!=EOF)
    {
    
      if(c=='|')
      {
        pid[i]='\0';
        i=0;
        if(atoi(pid)!=pid1)
        {fclose(f); return atoi(pid);}
        }
      else{
      pid[i]=c;
      i++;}
    }
    
    fclose(f);
    return 0;
}

int main()
{
    int a, fd, i = 0;
    char msg[100], *tmp = "/tmp/myfifo";
    pid_t pid1 = getpid(), pid2 = 0;

    system("clear");
    printf("Wanna reset the 'pid.txt' file ?");
    scanf("%d", &a);
    if (a > 0)
        system(">pid.txt");

    pid_send(pid1);
    while ((pid2 = pid_get(pid1)) == 0)
    {
        printf("\nWaiting for a new process");
        sleep(1);
    }
    printf("\nConnected with PID %ld", pid2);

    if (access(tmp, F_OK) == -1)
    {
        fd = mkfifo(tmp, 0666);
        if (fd == -1)
        {
            printf("\nError creating FIFO file");
            exit(1);
        }
    }

    while (1)
    {
        if (a == 0)
        {
            fd = open(tmp, O_RDONLY);
            if (fd == -1)
            {
                printf("\nError opening FIFO file");
                exit(1);
            }
            if (read(fd, msg, sizeof(msg)) > 0)
                printf("\nReceived: %s", msg);
            close(fd);
            a = 1;
        }
        else
        {
            fd = open(tmp, O_WRONLY);
            if (fd == -1)
            {
                printf("\nError opening FIFO file");
                exit(1);
            }
            printf("\nSend: ");
            scanf("%s", msg);
            if (write(fd, msg, sizeof(msg)) == -1)
            {
                printf("\nError writing to FIFO file");
                exit(1);
            }
            close(fd);
            a = 0;
        }
    }

    return 0;
}
