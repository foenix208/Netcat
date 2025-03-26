#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>


int nt_serveur(){
    fprintf(stderr,"Netcat serveur : \n");
    return 0;
}

int nt_client(char *host,char *port){
    int err;
    struct addrinfo hints, *info, *ai;
    struct sockaddr_in addr;
    int sock;

    bzero(&hints, sizeof(hints));
    hints.ai_family =   AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    
    if ((err = getaddrinfo(host, NULL, &hints, &info)) != 0){
        fprintf(stderr, "getaddrinfo: %s: %s\n", host, gai_strerror(err));
        exit(EXIT_FAILURE);
    }
    {
        void *addr;
        char ip[INET_ADDRSTRLEN];
        addr = &(((struct sockaddr_in *)info->ai_addr)->sin_addr);
        inet_ntop(info->ai_family, addr, ip, sizeof(ip));
        printf("Netcat Client %s (%s)\n", host, ip);
    }

    if((sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }  

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1312);
    //inet_pton(AF_INET,host,&addr.sin_addr);

    if(connect(sock,(struct sockaddr * )&addr,sizeof(addr)) < 0){
        perror("connect");
        exit(EXIT_FAILURE);
    
    }
    for(;;){
        
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        nt_serveur();
    else if (argc == 3)
        nt_client(argv[1],argv[2]);
    else{
        fprintf(stderr,"Arguments invalide");
        exit(EXIT_FAILURE);
    }
    return 0;
}
// sockstring
