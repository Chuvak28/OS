#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int fileSEND(char *server, int PORT, char *lfile, char *rfile)
{
    int socketDESC;
    struct sockaddr_in serverADDRESS;
    struct hostent *hostINFO;
    FILE *file_to_send;
    int ch;
    char toSEND[1];
    char remoteFILE[4096];
    int count1=1, count2=1, percent;

    hostINFO = gethostbyname(server);
    if(hostINFO==NULL)
    {
        printf("Problem interpreting host\n");
        return 1;
    }

    socketDESC = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDESC<0)
    {
        printf("Cannot create socket\n");
        return 1;
    }

    serverADDRESS.sin_family = hostINFO->h_addrtype;
    memcpy((char *) &serverADDRESS.sin_addr.s_addr, hostINFO->h_addr_list[0],hostINFO->h_length);
    serverADDRESS.sin_port = htons(PORT);

    if(connect(socketDESC,(struct sockaddr *)&serverADDRESS,sizeof(serverADDRESS))<0)
    {
        printf("Cannot connect\n");
        return 1;
    }

    file_to_send = fopen(lfile, "r");
    if(!file_to_send)
    {
        printf("Error opening file\n");
        close(socketDESC);
        return 0;
    }
    else
    {
        long fileSIZE;
        fseek(file_to_send,0,SEEK_END);
        fileSIZE=ftell(file_to_send);
        rewind(file_to_send);

        sprintf(remoteFILE,"FBEGIN:%s:%ld\r\n",rfile,fileSIZE);
        send(socketDESC,remoteFILE,sizeof(remoteFILE),0);
        percent = fileSIZE/100;
        while((ch=getc(file_to_send))!=EOF)
        {
            toSEND[0]=ch;
            send(socketDESC,toSEND,1,0);
            if(count1==count2)
            {
                printf("33[0;0H");
                printf("\33[2J");
                printf("Filename: %s\n",lfile);
                printf("Filesize: %ld Kb\n", fileSIZE/1024);
                printf("Percent: %d%% (%d Kb)\n", count1/percent,count1/1024);
                count1+=percent;
            }
            count2++;
        }
    }
    fclose(file_to_send);
    close(socketDESC);
    return 0;
}

int main()
{
    fileSEND("localhost", 4547, "1.jpg", "received.jpeg");
    return 0;
}


/*
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in servAddress;
    struct hostent *hostInfo;
    FILE *file_to_send;
    char buffer[256];
    char remoteFile[4096];
    int count1=1, count2=1, percent;
    int ch;
    char toSEND[1];

    //ACCEPTING ARGUMENTS FROM COMMAND LINE
    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    //GET PORT NUMBER
    portno = atoi(argv[2]);

    //CREATING SOCKET CLIENT
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
        printf("Cannot create socket\n");
        return 1;
    }

    //GET HOST NAME OR IP
    hostInfo = gethostbyname(argv[1]);
    if (hostInfo == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    //The bzero() function erases the data in the n bytes of the memory
    //starting at the location pointed to by s, by writing zeros (bytes
    //containing '\0') to that area.
    bzero((char *) &servAddress, sizeof(servAddress));
    servAddress.sin_family = AF_INET;
    bcopy((char *)hostInfo->h_addr, (char *)&servAddress.sin_addr.s_addr,   hostInfo->h_length);
    servAddress.sin_port = htons(portno);

    //CLIENT CONNECTING ON PORT  TO COMMUNICATE WITH SERVER
    if (connect(sockfd,(struct sockaddr *) &servAddress,sizeof(servAddress)) < 0)
    {
        printf("Cannot connect\n");
        return 1;
    }

    //open file
    file_to_send = fopen("1.jpg", "r");
    if(!file_to_send)
    {
        printf("Error opening file\n");
        close(sockfd);
        return 0;
    }
    else
    {
    long fileSIZE;
    fseek(file_to_send,0,SEEK_END);
    fileSIZE=ftell(file_to_send);
    rewind(file_to_send);

    sprintf("received.jpeg","FBEGIN:%s:%ld\r\n","1.jpg",fileSIZE);
    send(sockfd,"received.jpeg",sizeof("received.jpeg"),0);
    percent = fileSIZE/100;
    while((ch=getc(file_to_send))!=EOF)
    {
    toSEND[0]=ch;
    send(sockfd,toSEND,1,0);
    if(count1==count2)
    {
    printf("33[0;0H");
    printf("\33[2J");
    printf("Filename: %s\n","1.jpg");
    printf("Filesize: %ld Kb\n", fileSIZE/1024);
    printf("Percent: %d%% (%d Kb)\n", count1/percent,count1/1024);
    count1+=percent;
    }
    count2++;
    }
    }
    fclose(file_to_send);
    close(sockfd);
    return 0;
//    printf("Please enter the message: ");
//    //The bzero() function erases the data in the n bytes of the memory
//    //starting at the location pointed to by s, by writing zeros (bytes
//    //containing '\0') to that area.
//    bzero(buffer,256);
//    fgets(buffer,255,stdin);

//    //write function is used to send the data.
//    n = write(sockfd,buffer,strlen(buffer));
//    if (n < 0)
//        error("ERROR writing to socket");

//    //read function is used to read the buffer data
//    bzero(buffer,256);
//    n = read(sockfd,buffer,255);
//    if (n < 0)
//        error("ERROR reading from socket");
//    printf("%s\n",buffer);
//    close(sockfd);

//    return 0;

}
*/
