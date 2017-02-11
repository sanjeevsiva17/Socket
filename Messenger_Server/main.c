/*
Server Code for TCP/IP connection using Sockets
Created by : Sanjeev
Date : 1/2/2017
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<sys/uio.h>

void error_msg(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])  //argc and argv to pass IP address and port number in runtime... argc has number of arguments argv accepts all arguments
{
    int sockfd, newsockfd, portno, clilen, sockbn; //sockfd is for socket,sockbn is for bind, newsockfd is for listen,
    char buffer[256]; //message
    struct sockaddr_in serv_Addr;
    struct sockaddr_in cli_Addr;
    int n; //for reading message and writing message
    char msg[256];

    if(argc < 2)
    {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET is ip address, sock_stream is TCP,

    if(sockfd < 0)
    {
        error_msg("Error openening socket"); //if socket is not created
    }

    bzero((char*)&serv_Addr,sizeof(serv_Addr)); //server addresses as zero

    portno = atoi(argv[1]); //atoi converts char array to integer, argv[1] will have port number

    serv_Addr.sin_family = AF_INET;
    serv_Addr.sin_addr.s_addr = INADDR_ANY;
    serv_Addr.sin_port = htons(portno); //portno is int and htons is network type.. read BEEj's guide

    sockbn = bind(sockfd,(struct sockaddr *)&serv_Addr, sizeof(serv_Addr));  //bind the socket
    if(sockbn<0)
    {
        error_msg("Error on binding");
    }

    listen(sockfd,10); //a server can handle 10 clients now
    clilen = sizeof(cli_Addr);

    socklen_t socket_length = sizeof(cli_Addr);
    newsockfd = accept(sockfd,(struct sockaddr *)&cli_Addr, &socket_length);

    if(newsockfd<0)
    {
        error_msg("Error.. Cannot accept ");
    }

    bzero(buffer,256); // making message empty

    struct iovec buffer_info;
    buffer_info.iov_base = buffer;
    buffer_info.iov_len = 255;
    n = readv(newsockfd,&buffer_info,1);  //reading the message

    if(n<0)
    {
        error_msg("Error reading from socket");
    }

    printf("%s",buffer);

    bzero(buffer,256); // making message empty
    printf("Please Enter message");
    fgets(buffer,255,stdin);
    buffer_info.iov_len = strlen(buffer);
    n = writev(sockfd,&buffer_info,1);//write message

    if(n<0)
    {
        error_msg("Error Writing message");
    }

    return 0;

}
