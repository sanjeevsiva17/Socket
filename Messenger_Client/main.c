/*
Client Code for TCP/IP connection using Sockets
Created by : Sanjeev
Date : 1/2/2017
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
void error_msg(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])  //argc and argv to pass IP address and port number in runtime... argc has number of arguments argv accepts all arguments
{
    int sockfd, portno; //sockfd is for socket,sockbn is for bind, newsockfd is for listen,
    char buffer[256]; //message
    struct sockaddr_in serv_Addr;
    struct hostent *server;

    int n; //for reading message and writing message
    char msg[256];

    if(argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]); //atoi converts char array to integer, argv[1] will have port number

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET is ip address, sock_stream is TCP,

    if(sockfd < 0)
    {
        error_msg("Error openening socket"); //if socket is not created
    }

    server = gethostbyname(argv[1]);

    if(server == NULL)
    {
        error_msg("Host not found");
    }


    bzero((char*)&serv_Addr,sizeof(serv_Addr)); //server addresses as zero

    serv_Addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list,(char *)&serv_Addr.sin_addr.s_addr,server->h_length);
    serv_Addr.sin_port = htons(portno);
    if(connect(sockfd,&serv_Addr,sizeof(serv_Addr))<0)
    {
        error_msg("Error Connecting");
    }

    bzero(buffer,256); // making message empty
    printf("Please Enter message");
    fgets(buffer,255,stdin);
    n = writev(sockfd,buffer,strlen(buffer));
     if(n<0)
    {
        error_msg("Error reading from socket");
    }
      bzero(buffer,256); // making message empty

    n = readv(sockfd,buffer,255);  //reading the message

    if(n<0)
    {
        error_msg("Error reading from socket");
    }

     printf("%s",buffer);

    return 0;

}
