/* Author: Pete Broadwell
           Grinnell College

   This program uses streaming Internet sockets to simulate the readers-writers
   problem. This is the client/reader portion of the simulation.
*/

#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>     /* socket command libraries needed by some compilers */
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SIM_LENGTH 10 /* number of integers to be written and read */
#define PORT 1227 /* local port on which the server establishes connection */



// Returns hostname for the local computer
void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}
  
// Returns host information corresponding to host name
void checkHostEntry(struct hostent * hostentry)
{
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}
  
// Converts space-delimited IPv4 addresses
// to dotted-decimal format
void checkIPbuffer(char *IPbuffer)
{
    if (NULL == IPbuffer)
    {
        perror("inet_ntoa");
        exit(1);
    }
}


int main(void)
{ /* processing for client */
  int sock; /* socket file descriptor */
  struct sockaddr_in cli_name; /* socket address structure */
  int count;
  int value; /* variable for number read from socket */

 char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;
  
    // To retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);
  
    // To retrieve host information
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);
  
    // To convert an Internet network
    // address into ASCII string
    IPbuffer = inet_ntoa(*((struct in_addr*)
                           host_entry->h_addr_list[0]));
  
    printf("Hostname: %s\n", hostbuffer);
    printf("Host IP: %s", IPbuffer);
  

  printf("Client is alive and establishing socket connection.\n");
  
  /* set the socket descriptor */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
     
/* set the physical address (cli_name) of the socket descriptor */
  bzero(&cli_name, sizeof(cli_name)); /* initializes the address structure */
  cli_name.sin_family = AF_INET; /* socket family will be AF_INET (Internet) */
  cli_name.sin_addr.s_addr = inet_addr(IPbuffer); /* sets the Internet
						       Protocol (IP) address
						       of the server */
  cli_name.sin_port = htons(PORT); /* sets the port on which the server will
				      establish the socket connection */

  /* connect to the socket */
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }

  /* read integers from the socket */
  for (count = 1; count <= SIM_LENGTH; count++)
    { read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");

  close(sock); /* close connection to socket */
  exit(0); /* exit with no errors */ 

} /* end of main */ 
