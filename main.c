#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

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
  int a,fd;
  char msg[20],*tmp="/tmp/myfifo";
    system("clear");
    printf("Wanna reset the file ?");
    scanf("%d",&a);
    if(a>0)
    system(">pid.txt");
    
    pid_t pid1=getpid(),pid2=0;
    
    
    fd = open(tmp,O_RDONLY);
    pid_send(pid1);
    while((pid2= pid_get(pid1))==0)
    printf("\nWaiting for a new process");
    printf("\npid2: %ld",pid2);
    

    return 0;
}