#ifndef __FUN_H
#define __FUN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
#include<time.h>
#include <iostream>
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
  char receiver[500];
   std::cout<<"enter the file name along with extension to be received\n";
   std::cin>>receiver;
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

  std::cout<<"here are the logging  %s\n",baz;
  
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
        std::cout<<"Unable to create file.\n";
        exit(EXIT_FAILURE);
    }

     
    /* Input contents from user to store in file */
    //printf("Enter contents to store in file : \n");
    fgets(data, DATA_SIZE, stdin);


    /* Write data to file */
    fputs(data, fPtr);
      
 fwrite(baz , 1 , sizeof(baz)*2 , fPtr );
 fwrite(c , 1 , sizeof(c)*10 , fPtr );

    fclose(fPtr);


    /* Success message */
    std::cout<<"File created and saved successfully. :) \n";

  return;

}

int client()
{
    

time_t t;   
    time(&t);
int loop;
  //we need to enter the number of files thet we need to send to client
  std::cout<<"number of loops\n";
  std::cin>>loop;
       for(int i=0;i<loop;i++)
       {
     //need to enter the server ip address   
    char *ip = "192.168.60.85";
    char arr2[500]="client";
    //port number
    int port = 8080;
    int e;
  //creating the socket
  int sockfd;
  struct sockaddr_in server_addr;
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
    perror("[-]Error in socket\n");
    exit(1);
  }
   std::cout<<"[+]Server socket created successfully.\n";
   system("echo 1 > /sys/class/leds/led6/brightness");
   system("echo 0 > /sys/class/leds/led5/brightness");
   system("echo 0 > /sys/class/leds/led4/brightness");
   
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 //The connect() is used by the client application to establish a connection to a server. 
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) 
  {
    perror("[-]Error in socket");
    exit(1);
  }

 std::cout<<"[+]Connected to Server.\n";
 int flag=1; //connection is done
 system("echo 0 > /sys/class/leds/led6/brightness");
 system("echo 1 > /sys/class/leds/led5/brightness");
 system("echo 1 > /sys/class/leds/led4/brightness");
 //file send
  FILE *fp;
  char stringer[500];
  std::cout<<"enter the file name along with extension to be sent\n";
  std::cin>>stringer;
  char *filename = stringer;
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    perror("[-]Error in reading file.\n");
    exit(1);
  }
 
  send_file(fp, sockfd);
  std::cout<<"[+]File data successfully.\n";
  system("echo 0 > /sys/class/leds/led6/brightness");
  system("echo 0 > /sys/class/leds/led5/brightness");
  system("echo 1 > /sys/class/leds/led4/brightness");
 
  std::cout<<"[+]Closing the connection.\n";
  if(flag==2)
  {
    std::cout<<"The connection status is : communication done successfully\n";
  }
else 
if(flag==1) 
  {
    std::cout<<"The connection status is : connected yet to communicate\n";
  }
else
  {
    std::cout<<"The connection status is : not connected\n";
  }
  close(sockfd);
   
  //log time
  llog(ip,ctime(&t));

}


    return 0;
}
int server()
{
  {

  time_t t;   
    time(&t);
  
  char *ip = "192.168.60.85";
  char arr2[500]="server";
  int port = 8080;
  int e;
  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  FILE *fp;
  socklen_t addr_size;
  char buffer[SIZE];

    //creating socket
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) 
    {
      perror("[-]Error in socket\n");
      exit(1);
    }
    std::cout<<"[+]Server socket created successfully.\n";
    system("echo 1 > /sys/class/leds/led6/brightness");
    system("echo 0 > /sys/class/leds/led5/brightness");
    system("echo 0 > /sys/class/leds/led4/brightness");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    //function binds the socket to the address and port number specified in addr
  
    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e < 0) {
    perror("[-]Error in bind\n");
    exit(1);
  }
  std::cout<<"[+]Binding successfull.\n";
  system("echo 0 > /sys/class/leds/led6/brightness");
  system("echo 1 > /sys/class/leds/led5/brightness");
  system("echo 0 > /sys/class/leds/led4/brightness");
  int flag=1; //connection is done
  int loop;

  std::cout<<"number of loops\n";
  std::cin>>loop;
    
     for(int i=0;i<loop;i++)
     {

        if(listen(sockfd, 10) == 0)
        {
          std::cout<<"[+]Listening....\n";
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
  std::cout<<"[+]Data written in the file successfully.\n";
  system("echo 1 > /sys/class/leds/led6/brightness");
  system("echo 0 > /sys/class/leds/led5/brightness");
  system("echo 1 > /sys/class/leds/led4/brightness");

if(flag==2)
{
  std::cout<<"The connection status is : communication done successfully\n";
}
else if(flag==1)
 {
   std::cout<<"The connection status is : connected yet to communicate\n";
 }
else
  {
    std::cout<<"The connection status is : not connected\n";
  }

  llog(ip,ctime(&t));
}
return 0;
}

}





#endif