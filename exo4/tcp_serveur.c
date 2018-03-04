// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#define PORT 10000

int main(void) {

  /* Socket et contexte d'adressage du serveur */
  struct sockaddr_in sin;
  int sock;
  socklen_t recsize = sizeof(sin);
    
  /* Socket et contexte d'adressage du client */
  struct sockaddr_in csin;
  int csock;
  socklen_t crecsize = sizeof(csin);
 
  /* Création d'une socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  /* Configuration */
  sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
  sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
  sin.sin_port = htons(PORT);               /* Listage du port */
  bind(sock, (struct sockaddr*)&sin, recsize);

  /* Démarrage du listage (mode server) */
  listen(sock, 5);
  

  /* Attente d'une connexion client */
  while (1) {
   
    csock = accept(sock, (struct sockaddr*)&csin, &crecsize);
    printf("Un client se connecte avec la socket %d de %s:%d\n",
         csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));

    /* Création d'un nouveau processus pour gérer la connexion avec le client */
    pid_t pid;
    pid = fork(); // Création du processus fils
    
    if (pid == 0) {
      /* Reception du message du client */
      char bufferMrc[32] = "";
      recv(csock, bufferMrc, 32, 0);
      printf("%s \n", bufferMrc);

      /* Lorque le client a envoyé son message, on ferme le processus fils */
      return EXIT_SUCCESS;
    } else {
      /* Le père attends que le fils se termine */
      wait(NULL);
    }
  }
  

  /* Fermeture de la socket client et de la socket serveur */
  close(csock);
  close(sock);

  return EXIT_SUCCESS;

}//main
