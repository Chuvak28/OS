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



#define PORT 4547

int parseARGS(char **args, char *line)
{
    int tmp = 0;
    args[tmp] = strtok(line, ":" );
    while ((args[++tmp] = strtok(NULL, ":" )) != NULL);
    return tmp -1;
}

int main()
{
    char *header[4096];
    int listenSOCKET, connectSOCKET;
    socklen_t clientADDRESSLENGTH;
    struct sockaddr_in clientADDRESS, serverADDRESS;
    char recvBUFF[4096];
    char *filename, *filesize;
    FILE *recvFILE;
    int received = 0;
    char tempstr[4096];

    int count1=1, count2=1, percent;

    listenSOCKET = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSOCKET <0)
    {
        printf("Cannot create socket\n");
        close(listenSOCKET);
        return 1;
    }

    serverADDRESS.sin_family = AF_INET;
    serverADDRESS.sin_addr.s_addr = htonl(INADDR_ANY);
    serverADDRESS.sin_port = htons(PORT);

    if (bind(listenSOCKET, (struct sockaddr *)&serverADDRESS, sizeof(serverADDRESS))<0)
    {
        printf("Cannot bind socket\n");
        close(listenSOCKET);
        return 1;
    }

    listen(listenSOCKET, 5);
    clientADDRESSLENGTH = sizeof(clientADDRESS);
    connectSOCKET = accept(listenSOCKET,(struct sockaddr *)&clientADDRESS, &clientADDRESSLENGTH);
    if (connectSOCKET<0)
    {
        printf("Cannot accpet connection\n");
        close(listenSOCKET);
        return 1;
    }

    while(1)
    {
        if(recv(connectSOCKET, recvBUFF, sizeof(recvBUFF),0))
        {
            if(!strncmp(recvBUFF,"FBEGIN",6))
            {
                recvBUFF[strlen(recvBUFF)-2] = 0;
                parseARGS(header, recvBUFF);
                filename = header[1];
                filesize = header[2];
            }
            recvBUFF[0] = 0;
            recvFILE = fopen(filename, "w");
            percent = atoi(filesize)/100;
            printf("Current percent value: %d\n",percent);
            while(1)
            {
                if(recv(connectSOCKET,recvBUFF,1,0) != 0)
                {
                    fwrite(recvBUFF,sizeof(recvBUFF[0]),1,recvFILE);
                    if(count1==count2)
                    {
                        printf("33[0;0H");
                        printf("\33[2J");
                        printf("Filename: %s\n", filename);
                        printf("Filesize: %d Kb\n", atoi(filesize)/1024);
                        printf("Percent: %d%% (%d Kb)\n", count1/percent,count1/1024);
                        count1+=percent;
                        printf("Show count1 value: %d\n",count1);
                    }
                    count2++;
                    printf("Show count2 value: %d\n", count2);
                    received++;
                    recvBUFF[0] = 0;
                }
                else
                {
                    close(listenSOCKET);
                    return 0;
                }
            }
            close(listenSOCKET);
        }
        else
        {
            printf("Client dropped connection\n");
        }
        return 0;
    }
}




//the thread function
//void *connection_handler(void *);
/*

int parseARGS(char **args, char *line)
{
    int tmp = 0;
    args[tmp] = strtok(line, ":" );
    while ((args[++tmp] = strtok(NULL, ":" )) != NULL);
    return tmp -1;
}


int main(int argc, char *argv[])
{
    char *header[4096];
    char *filename, *filesize;
    FILE *recvFILE;
    int received = 0;
    char tempstr[4096];
    int count1=1, count2=1, percent;
    char recvBUFF[4096];
    int listenSOCKET, connectSOCKET,portno;
    //int sockfd, newsockfd,  *new_sock;
    char buffer[256];
    struct sockaddr_in serverADDRESS, clientADDRESS;
    int n;
    socklen_t clientADDRESSLENGTH;


    //ACCEPTING ARGUMENTS FROM COMMAND LINE
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    //CREATING SOCKET SERVER
    listenSOCKET = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSOCKET <0)
    {
        printf("Cannot create socket\n");
        close(listenSOCKET);
        return 1;
    }

    //The bzero() function erases the data in the n bytes of the memory
    //starting at the location pointed to by s, by writing zeros (bytes
    //containing '\0') to that area.
    bzero((char *) &serverADDRESS, sizeof(serverADDRESS));
    portno = atoi(argv[1]);
    //DEFINING SOCKET FAMILY, ADDRESS & PORT
    serverADDRESS.sin_family = AF_INET;
    serverADDRESS.sin_addr.s_addr = INADDR_ANY;
    serverADDRESS.sin_port = htons(portno);

    //Server and client will start interacting with each other after the bind function and it
    //is the most important  session.
    if (bind(listenSOCKET, (struct sockaddr *) &serverADDRESS, sizeof(serverADDRESS)) < 0)
    {
        printf("Cannot bind socket\n");
        close(listenSOCKET);
        return 1;
    }

    //It puts the server socket in a passive mode, where it waits for
    //the client to approach the server to make a connection.
    //The backlog, defines the maximum length to which the queue
    //of pending connections for sockfd may grow.
    listen(listenSOCKET,5);


    clientADDRESSLENGTH = sizeof(clientADDRESS);


    connectSOCKET = accept(listenSOCKET,(struct sockaddr *)&clientADDRESS, &clientADDRESSLENGTH);
    if (connectSOCKET<0)
    {
        printf("Cannot accpet connection\n");
        close(listenSOCKET);
        return 1;
    }
    while(1)
    {
        if(recv(connectSOCKET, recvBUFF, sizeof(recvBUFF),0))
        {
            if(!strncmp(recvBUFF,"FBEGIN",6))
            {
                recvBUFF[strlen(recvBUFF)-2] = 0;
                parseARGS(header, recvBUFF);
                filename = header[1];
                filesize = header[2];
            }
            recvBUFF[0] = 0;
            recvFILE = fopen(filename, "w");
            percent = atoi(filesize)/100;
            printf("Current percent value: %d\n",percent);
            while(1)
            {
                if(recv(connectSOCKET,recvBUFF,1,0) != 0)
                {
                    fwrite(recvBUFF,sizeof(recvBUFF[0]),1,recvFILE);
                    if(count1==count2)
                    {
                        printf("33[0;0H");
                        printf("\33[2J");
                        printf("Filename: %s\n", filename);
                        printf("Filesize: %d Kb\n", atoi(filesize)/1024);
                        printf("Percent: %d%% (%d Kb)\n", count1/percent,count1/1024);
                        count1+=percent;
                        printf("Show count1 value: %d\n",count1);
                    }
                    count2++;
                    printf("Show count2 value: %d\n", count2);
                    received++;
                    recvBUFF[0] = 0;
                }
                else
                {
                    close(listenSOCKET);
                    return 0;
                }
            }
            close(listenSOCKET);
        }
        else
        {
            printf("Client dropped connection\n");
        }
        return 0;
    }

    return 0;
}
*/

/*
*  char *message;
while((newsockfd = accept(listenSOCKET, (struct sockaddr *) &clientADDRESS,  &clientADDRESSLENGTH)))
{

    if (newsockfd < 0)
        error("ERROR on accept");
    puts("Connection accepted");
    //Reply to the client
    message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
    write(newsockfd , message , strlen(message));

    pthread_t sniffer_thread;
    new_sock = (int*)malloc(sizeof(int));
    *new_sock = newsockfd;
    if( pthread_create( &sniffer_thread , NULL , connection_handler , (void*) new_sock) < 0)
    {
        perror("could not create thread");
        return 1;
    }


}
close(newsockfd);*/
// close(listenSOCKET);




/*
 * This will handle connection for each client
 * */
//void *connection_handler(void *socket_desc)
//{
//    //Get the socket descriptor
//    int sock = *(int*)socket_desc;
//    int read_size;
//    char *message , client_message[2000];
//    char buffer[256];
//    int n;

//    //Send some messages to the client
//    message = "Greetings! I am your connection handler\n";
//    write(sock , message , strlen(message));

//    message = "Now type something and i shall repeat what you type \n";
//    write(sock , message , strlen(message));

//    //read function is used to read the buffer data or receive data
//    bzero(buffer,256);
//    n = read(sock,buffer,255);
//    if (n < 0) error("ERROR reading from socket");
//    printf("Here is the message: %s\n",buffer);

//    //write function is used to send the data.
//    n = write(sock,"I got your message",18);
//    if (n < 0) error("ERROR writing to socket");
//    //    //Receive a message from client
//    //    while( (read_size = recv(sock , client_message , 2000 , 0)) < 0 )
//    //    {
//    //        //Send the message back to client
//    //        write(sock , client_message , strlen(client_message));
//    //    }

//    //    if(read_size == 0)
//    //    {
//    //        puts("Client disconnected");
//    //        fflush(stdout);
//    //    }
//    //    else if(read_size == -1)
//    //    {
//    //        perror("recv failed");
//    //    }

//    //Free the socket pointer
//    free(socket_desc);

//    return 0;
//}
