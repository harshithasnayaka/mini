#include"fun.h"

int client();
int server();

int error();
void send_file(FILE *fp, int sockfd);
void write_file(int sockfd);
void logchar(char *baz,char *c);
//void llog(char *baz,char *c);

int main()
{
    char mode[3]; //default no connection needed or abort
    char ping[2] ;//success or failure yes or no
    int flag,loop;
      time_t t;   
    time(&t);
       printf("\ndate and time: %s", ctime(&t));


    printf("do you want to continue with client server connection?[y or n]\n");
    scanf("%s",mode);
    if(( strcmp(mode,"n")==0)&&(strcmp(ping,"n")==0))
    {
        flag =0;
        system("echo 1 > /sys/class/leds/led6/brightness");
        system("echo 1 > /sys/class/leds/led5/brightness");
        system("echo 1 > /sys/class/leds/led4/brightness");
    }
    if(( strcmp(mode,"n")==0)&&(strcmp(ping,"y")==0))
    {
        flag =1;
          system("echo 1 > /sys/class/leds/led6/brightness");
        system("echo 1 > /sys/class/leds/led5/brightness");
        system("echo 1 > /sys/class/leds/led4/brightness");
    }
    if(( strcmp(mode,"y")==0)&&(strcmp(ping,"n")==0))
    {
        flag =2;
        
    }
    if(( strcmp(mode,"y")==0)&&(strcmp(ping,"y")==0))
    {
        flag =3;
    }

    
    if(strcmp(mode,"y")==0)
    {
        char choice[3];
        printf("How do you want to continue? as server please press s as client please press c");
        scanf(" %s",choice);
        // char *ip = "192.168.60.41";
        char sip[200];
        // printf("Enter ip address of the client which is sending file system {other system }\n");

        // scanf("%s",sip);
        // char *ip = "192.168.60.79";
        char rip[200];
        
        // printf("enter  ip address of the server which is reciving {your system}\n");
        // scanf("%s",rip);
        
        










        if(flag==3){printf("connection is established but user is ready to connect\n");}
        if(strcmp(choice,"s")==0)
        {
            server();
        }
        else if (strcmp(choice,"c")==0)

        {
            client();
        }


    }
  
    else if(flag==0)
    
    {printf("connection is not established and user refused to connect\n");}
    else if(flag==1){printf("connection is established but user refused to connect\n");}
    else if(flag==2){printf("USer wants communication but connection is not available");}
    else{printf("Sorry!connection is not established\n");}
    flag=4;
    return 0;

}


