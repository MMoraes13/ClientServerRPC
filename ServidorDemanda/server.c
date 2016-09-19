#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>


#define MAX_CONNECTIONS    (1000)
#define MAX_LINE           (1000)

int main()
{
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  struct sockaddr_in my_addr;
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  my_addr.sin_port = htons(4000);

  bind(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr));
  listen(sockfd, MAX_CONNECTIONS);
  long lSize;
  char * buffer;
  size_t result;
  pid_t pid, new;
  int counter = 0;
  while(1)
    {
      struct sockaddr_in client_addr;
      int client_len = sizeof(client_addr);

      int client_fd = accept(sockfd, (struct sockaddr *) &client_addr,  &client_len);


      if ((pid = fork()) == -1)
      {
          close(new);
            continue;
      }
      else if(pid > 0)
      {
          close(new);
          counter++;
          printf("here2\n");
          continue;
      }
      else if(pid == 0)
      {    
          FILE *fp = fopen("send", "r");
          if(fp == NULL) {
              printf("File send cannot be opened.\n");
              exit (1);
          }    
               // obtain file size:
          fseek (fp , 0 , SEEK_END);
          lSize = ftell (fp);
          rewind (fp);

          buffer = (char*) malloc (sizeof(char)*lSize);
          if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

          result = fread (buffer,1,lSize,fp);
          if (result != lSize) {fputs ("Reading error",stderr); exit (3);}      

          send(client_fd, buffer, strlen(buffer) + 1, 0);
          close(client_fd);
          fclose(fp);
          free (buffer);
      }
    }
}
