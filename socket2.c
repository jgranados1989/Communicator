/* Estos son los ficheros de cabecera usuales */
#include <stdio.h>          
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#define PORT 3550 /* El puerto que será abierto */
#define BACKLOG 2 /* El número de conexiones permitidas */

main()
{

   int fd, fd2; /* los ficheros descriptores */

   struct sockaddr_in server; 
   /* para la información de la dirección del servidor */

   struct sockaddr_in client; 
   /* para la información de la dirección del cliente */

   int sin_size;

   /* A continuación la llamada a socket() */
   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {  
      printf("error en socket()\n");
   }

   server.sin_family = AF_INET;         

   server.sin_port = htons(PORT); 
   /* ¿Recuerdas a htons() de la sección "Conversiones"? =) */

   server.sin_addr.s_addr = INADDR_ANY; 
   /* INADDR_ANY coloca nuestra dirección IP automáticamente */

   //bzero(&(server.sin_zero),8); 
   /* escribimos ceros en el resto de la estructura */


   /* A continuación la llamada a bind() */
   if(bind(fd,(struct sockaddr*)&server,
           sizeof(struct sockaddr))==-1) {
      printf("error en bind() \n");
		exit(0);
   }     

   if(listen(fd,BACKLOG) == -1) {  /* llamada a listen() */
      printf("error en listen()\n");
		exit(0);
   }

   while(1) {
      sin_size=sizeof(struct sockaddr_in);
      /* A continuación la llamada a accept() */
      if ((fd2 = accept(fd,(struct sockaddr *)&client,
                        &sin_size))==-1) {
         printf("error en accept()\n");
		exit(0);
      }
	char *some_addr;
	some_addr=inet_ntoa(client.sin_addr);
	printf( "Se obtuvo una conexión desde %s \n",some_addr);
      /* que mostrará la IP del cliente */

      send(fd2,"Bienvenido a mi servidor.\n",22,0); 
      /* que enviará el mensaje de bienvenida al cliente */

      close(fd2); /* cierra fd2 */
   }
}

