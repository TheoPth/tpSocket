// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#define PORT 10000


int main(void) {

  int sock;
  struct sockaddr_in sin;

  /* Création de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);
 
  /* Configuration de la connexion */
  sin.sin_addr.s_addr = inet_addr("192.168.1.20"); /* On change ici l'adresse ip */
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
 
  /* Tentative de connexion au serveur */
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));


  
  /* Récupération de la saisi de l'utilisateur */
  char chaine[32];
  printf("Tapez une phrase : \n");
  fgets(chaine, sizeof chaine, stdin);

  /* Envoie du message au serveur */
  send(sock, strcat(chaine, "\r\n"), 32, 0); 
  

  /* Fermeture de la socket client */
  close(sock);
  return EXIT_SUCCESS;
}//main



