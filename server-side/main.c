#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define BUFFSIZE 4096
#define MAX_LINE 4096
#define LINSTENPORT 7788
#define SERVERPORT 8877

ssize_t total=0;

int main()
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address, clientaddr;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    char filename[BUFFSIZE] = {0};
    if (recv(new_socket, filename, BUFFSIZE, 0) == -1)
    {
        perror("Can't receive filename");
        exit(1);
    }
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        perror("Can't open file");
        exit(1);
    }

    char addr[INET_ADDRSTRLEN];
    printf("Start receive file: %s from %s\n", filename, inet_ntop(AF_INET, &clientaddr.sin_addr, addr, INET_ADDRSTRLEN));
    ssize_t n;
        char buff[MAX_LINE] = {0};
        while ((n = recv(new_socket, buff, MAX_LINE, 0)) > 0)
        {
            total+=n;
            if (n == -1)
            {
                perror("Receive File Error");
                exit(1);
            }

            if (fwrite(buff, sizeof(char), n, fp) != n)
            {
                perror("Write File Error");
                exit(1);
            }
            memset(buff, 0, MAX_LINE);
        }
    printf("Receive Success, NumBytes = %ld\n", total);

    //    valread = read( new_socket , buffer, 1024);
    //    printf("%s\n",buffer );
    //    recv(new_socket , hello , strlen(hello) , 0 );
    //    printf("Hello message sent\n");
    //    printf("It is me         Ismoil\n");
    return 0;
}
