// $Id$

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#define PORT 10000

int sort=0;

void terminer(){
     sort=1;
}

int main(void) {

  int sock;
  struct sockaddr_in sin;

  /* Création de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);
 
  /* Configuration de la connexion */
  sin.sin_addr.s_addr = inet_addr("127.0.0.1");
  //sin.sin_addr.s_addr = inet_addr("162.38.111.75");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
 
  /* Tentative de connexion au serveur */
  connect(sock, (struct sockaddr*)&sin, sizeof(sin));
  printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr),
         htons(sin.sin_port));
  char buf[32]="";

  /* Association du signal  pour sortir de la boucle */
  signal(SIGINT,terminer);

  while(sort==0){
    char *pos;
    printf("Entrez un message pour le serveur \n");
    /* récupération de la frappe de l'utilisateur */
    fgets(buf,32,stdin);

    /* On change le retour chariot pour que le serveur comprenne que c'est une fin de ligne */
    pos = strchr(buf,'\n');
    *pos='\0';

    /* Envoie du buffer via la socket ouverte précédemment */
    send(sock,buf,32,0);
  }

  close(sock);

  return EXIT_SUCCESS;

} //main

