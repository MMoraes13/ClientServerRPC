#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define BUF_SIZE 	(50000)

int main(int narg, char *varg[])
{
    int socketfd;
    struct sockaddr_in server_addr;
    int port = atoi(varg[2]); //convert a string to an integer
    int recv_len, sent_len;
    char buf[BUF_SIZE];

    printf("Connecting to %s:%d\n", varg[1], port);

    // create the socket if possible
    if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("unable to create socket");
        return -1;
    }

    // configure the server address for the socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(varg[1]);

    // connect to the server via the socket created above
    if (connect(socketfd,
                   (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("unable to connect");
        return -1;
    }

    // receive data from server
    recv_len = recv(socketfd, buf, BUF_SIZE, 0);
    if (recv_len == 0) {
        printf("server disconnected!\n");
        close(socketfd);
        return 0;
    }
    if (recv_len < 0) {
        perror("error receiving data from server");
        return -1;
    }
    FILE *fp = fopen("received", "w+");
    if(fp == NULL) {
        printf("File send cannot be opened.\n");
        exit (1);
    }    

    fprintf(fp, "%s", buf);
    printf ("received from server %d bytes", recv_len);
    close(socketfd);
    fclose (fp);
    return 0;
}
