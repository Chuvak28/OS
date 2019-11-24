#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    //ACCEPTING ARGUMENTS FROM COMMAND LINE
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    //GET PORT NUMBER
    portno = atoi(argv[2]);
    //CREATING SOCKET CLIENT
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    //GET HOST NAME OR IP
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    //The bzero() function erases the data in the n bytes of the memory
    //starting at the location pointed to by s, by writing zeros (bytes
    //containing '\0') to that area.
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,   server->h_length);
    serv_addr.sin_port = htons(portno);
    //CLIENT CONNECTING ON PORT  TO COMMUNICATE WITH SERVER
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    printf("Please enter the message: ");
    //The bzero() function erases the data in the n bytes of the memory
    //starting at the location pointed to by s, by writing zeros (bytes
    //containing '\0') to that area.
    bzero(buffer,256);
    fgets(buffer,255,stdin);

    //write function is used to send the data.
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
         error("ERROR writing to socket");

    //read function is used to read the buffer data
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}
