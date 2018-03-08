// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <complex.h>
#define PORT 10000


void * fils(void *t){
  int csock = *(int*)t;
  int nb;
  char buf[32]="";
  nb=1;

  /* on recoit les messages tant que l'utilisateur est connecté */
  while(nb !=0){
    nb = recv(csock,buf,32,0);
    printf("%s \n",buf);
  }

  close(csock); 
}

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

  while(1){
    /* Attente d'une connexion client */
    csock = accept(sock, (struct sockaddr*)&csin, &crecsize);

    /* Création du thread qui va gérer les echanges avec le client */
    pthread_t thread;

    /* Lors de la création du thread, on lui indique qu'elle fonction il va devoir exécuter */
    pthread_create(&thread, NULL, fils, (void *)&csock);

    /* le thread est non bloquant */
    pthread_detach(thread);
}
  close(sock);

  return EXIT_SUCCESS;

}//main
