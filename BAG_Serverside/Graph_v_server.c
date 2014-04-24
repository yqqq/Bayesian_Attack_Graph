#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<signal.h>
#include<sys/stat.h>
#include<sys/param.h>
#include<time.h>

/*--------------------------------------------------*/
/*init_deamon function will set up a deamon process;*/
/*The deamon process will running background ;      */
/*Coping jobs background without the shell or bash; */
/*--------------------------------------------------*/

void init_deamon(void){
    int pid;
    int i;
    /*Father exit & hand out the children process to init*/
    if(pid=fork()){
        exit(0);
        }
    else if(pid<0){
    /*THIS PLACE SHOULD INSERT LOG HANDLER*/
    /*The fork() is erro & need be reported*/
        exit(1);
        }
    /*This must be the first Children process, running background*/
    /*Creat a new session here by using setsid()*/
    /*First Children process become the captail of session*/
    setsid();
    /*The second children here,second children could not be Capital of the Group*/
    if(pid=fork())
            exit(0);
    else if(pid<0)
    /*THIS PLACE SHOULD INSERT LOG HANDLER*/
    /*The fork() is erro & need be reported*/
            exit(1);
    /*Close all the files that opens*/
    for(i=0;i<NOFILE;i++)
            close(i);
    /*Change the working directory into /tmp*/
    chdir("/tmp");
    /*Reset the file mask*/
    umask(0);
    return;
    }
        
int main(int argc,char *argv){
    FILE *fp;
    time_t t;
    init_deamon();
    
    while(1)
    {
        sleep(20);
        if((fp=fopen("/home/lovingmage/Desktop/Graph.log","a"))>=0)
        {
            t=time(0);
            fprintf(fp,"Im here at %sn",asctime(localtime(&t)));
            fclose(fp);
            }
     }
     return 0;
}
        
    
    
    
    
