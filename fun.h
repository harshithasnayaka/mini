#ifndef __FUN_H
#define __FUN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
#include<time.h>

int client()
{
    // printf("im inside client\n");

time_t t;   
    time(&t);
int loop;

  printf("number of loops\n");
  scanf("%d",&loop);
       for(int i=0;i<loop;i++)
       {
    char *ip = "192.168.60.74";
    // char sip[200];
    // char *ip = sip;

     char arr2[500]="client";

  int port = 8080;
  int e;
 
  int sockfd;
  struct sockaddr_in server_addr;
//   FILE *fp;
//  char stringer[500];
//  printf("enter the file name along with extension to be sent\n");
//  scanf("%s",stringer);
//   char *filename = stringer;
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
    perror("[-]Error in socket\n");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
   system("echo 1 > /sys/class/leds/led6/brightness");
        system("echo 0 > /sys/class/leds/led5/brightness");
        system("echo 0 > /sys/class/leds/led4/brightness");
   
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
//  printf("The connection has been established succesfully between client and server\n");
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }

 printf("[+]Connected to Server.\n");
  int flag=1; //connection is done
     system("echo 0 > /sys/class/leds/led6/brightness");
        system("echo 1 > /sys/class/leds/led5/brightness");
        system("echo 1 > /sys/class/leds/led4/brightness");

    

    
           FILE *fp;
 char stringer[500];
 printf("enter the file name along with extension to be sent\n");
 scanf("%s",stringer);
  char *filename = stringer;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.\n");
    exit(1);
  }
 
  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");
    system("echo 0 > /sys/class/leds/led6/brightness");
        system("echo 0 > /sys/class/leds/led5/brightness");
        system("echo 1 > /sys/class/leds/led4/brightness");
 
  printf("[+]Closing the connection.\n");
  if(flag==2){printf("The connection status is : communication done successfully\n");}
else if(flag==1) {printf("The connection status is : connected yet to communicate\n");}
else{printf("The connection status is : not connected\n");}
  close(sockfd);
   

  llog(ip,ctime(&t));

     }


    return 0;
}
int server()
{


    {
// printf("im inside server\n");
  time_t t;   
    time(&t);
  
  char *ip = "192.168.60.215";
    // char rip[200];
    //  char *ip = rip;
    char arr2[500]="server";
     int port = 8080;
     int e;
     int sockfd, new_sock;
     struct sockaddr_in server_addr, new_addr;
     FILE *fp;
     socklen_t addr_size;

     char buffer[SIZE];

    
    
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
    perror("[-]Error in socket\n");
    exit(1);


    }
    //  printf("The connection has been established succesfully between client and server");
    printf("[+]Server socket created successfully.\n");
      system("echo 1 > /sys/class/leds/led6/brightness");
        system("echo 0 > /sys/class/leds/led5/brightness");
        system("echo 0 > /sys/class/leds/led4/brightness");
   


   
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    
    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e < 0) {
    perror("[-]Error in bind\n");
    exit(1);
  }
  printf("[+]Binding successfull.\n");
    system("echo 0 > /sys/class/leds/led6/brightness");
        system("echo 1 > /sys/class/leds/led5/brightness");
        system("echo 0 > /sys/class/leds/led4/brightness");
 int flag=1; //connection is done

int loop;

  printf("number of loops\n");
  scanf("%d",&loop);
    
     for(int i=0;i<loop;i++)
     {

if(listen(sockfd, 10) == 0){
 printf("[+]Listening....\n");
   system("echo 1 > /sys/class/leds/led6/brightness");
        system("echo 1 > /sys/class/leds/led5/brightness");
        system("echo 0 > /sys/class/leds/led4/brightness");
 flag=3; //connected but ready to communication. 
 }
 else
 {
 perror("[-]Error in listening\n");
   system("echo 0 > /sys/class/leds/led6/brightness");
        system("echo 1 > /sys/class/leds/led5/brightness");
        system("echo 1 > /sys/class/leds/led4/brightness");
    exit(1);
 }
 
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock);
  flag=2; //communication started and finished
  printf("[+]Data written in the file successfully.\n");
    system("echo 1 > /sys/class/leds/led6/brightness");
        system("echo 0 > /sys/class/leds/led5/brightness");
        system("echo 1 > /sys/class/leds/led4/brightness");
//   printf("number of loops");
//   scanf("%d",&loop);




  if(flag==2){printf("The connection status is : communication done successfully\n");}
else if(flag==1) {printf("The connection status is : connected yet to communicate\n");}
else{printf("The connection status is : not connected\n");}


llog(ip,ctime(&t));
     }



return 0;
}

}



void send_file(FILE *fp, int sockfd)
{
  int n;
  char data[SIZE] = {0};
 
  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) 
    {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

void write_file(int sockfd){
  int n;
  FILE *fp;
//   char *filename = "recv.txt";

char receiver[500];
   printf("enter the file name along with extension to be received\n");
 scanf("%s",receiver);
  char *filename = receiver;
  char buffer[SIZE];
 
  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}

void llog(char *baz,char *c)


{    

  printf("here are the logging  %s\n",baz);
  // printf("%c\n", *arr3);
  // printf("%c\n", arr3);

 #define DATA_SIZE 10000
   char data[DATA_SIZE];
    FILE * fPtr;
 //char str[] = "client adress= 192.168.60.39";

    /* 
     * Open file in w (write) mode. 
     * "data/file1.txt" is complete path to create file
     */
    fPtr = fopen("log.txt", "a+");


    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

     
    /* Input contents from user to store in file */
    printf("Enter contents to store in file : \n");
    fgets(data, DATA_SIZE, stdin);


    /* Write data to file */
    fputs(data, fPtr);
      
 fwrite(baz , 1 , sizeof(baz)*2 , fPtr );
 fwrite(c , 1 , sizeof(c)*10 , fPtr );

    /* Close file to save file data */
    fclose(fPtr);


    /* Success message */
    printf("File created and saved successfully. :) \n");

  return;

}
#endif
    


