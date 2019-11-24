/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

//the thread function
void *connection_handler(void *);

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, *new_sock;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    //ACCEPTING ARGUMENTS FROM COMMAND LINE
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    //CREATING SOCKET SERVER
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    //The bzero() function erases the data in the n bytes of the memory
    //starting at the location pointed to by s, by writing zeros (bytes
    //containing '\0') to that area.
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    //DEFINING SOCKET FAMILY, ADDRESS & PORT
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //Server and client will start interacting with each other after the bind function and it
    //is the most important  session.
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    //It puts the server socket in a passive mode, where it waits for
    //the client to approach the server to make a connection.
    //The backlog, defines the maximum length to which the queue
    //of pending connections for sockfd may grow.
    listen(sockfd,5);


    clilen = sizeof(cli_addr);


    char *message;

    while((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,  &clilen)))
    {

        if (newsockfd < 0)
            error("ERROR on accept");
        puts("Connection accepted");
        //Reply to the client
        message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
        write(newsockfd , message , strlen(message));

        pthread_t sniffer_thread;
        new_sock = (int*)malloc(sizeof(int));
        *new_sock = new_socket;



    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];

    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    write(sock , message , strlen(message));

    message = "Now type something and i shall repeat what you type \n";
    write(sock , message , strlen(message));

    //read function is used to read the buffer data or receive data
    bzero(buffer,256);
    n = read(sock,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);

    //write function is used to send the data.
    n = write(sock,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
//    //Receive a message from client
//    while( (read_size = recv(sock , client_message , 2000 , 0)) < 0 )
//    {
//        //Send the message back to client
//        write(sock , client_message , strlen(client_message));
//    }

//    if(read_size == 0)
//    {
//        puts("Client disconnected");
//        fflush(stdout);
//    }
//    else if(read_size == -1)
//    {
//        perror("recv failed");
//    }

    //Free the socket pointer
    free(socket_desc);

    return 0;
}
