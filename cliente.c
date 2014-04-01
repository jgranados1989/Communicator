#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>    
#include <stdlib.h>
/* netbd.h es necesitada por la estructura hostent ;-) */

#define PORT 8080    
/* El Puerto Abierto del nodo remoto */

#define MAXDATASIZE 100   
#define ANSI_COLOR_RESET   "\x1b[0m"
/* El número máximo de datos en bytes */
int fd;
char datosenviados[256];

void cierra_cliente()
{
   close(fd);   /* cerramos fd =) */
}

int abre_cliente(char *argv,char *nombre)
{
   int numbytes;       
   /* ficheros descriptores */

   char buf[MAXDATASIZE];  
   /* en donde es almacenará el texto recibido */

   struct hostent *he;         
   /* estructura que recibirá información sobre el nodo remoto */

   struct sockaddr_in server;  
   /* información sobre la dirección del servidor */
	
   if ((he=gethostbyname(argv))==NULL){       
      /* llamada a gethostbyname() */
      printf("gethostbyname() error\n");
      exit(-1);
   }

   if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){  
      /* llamada a socket() */
      printf("socket() error\n");
      exit(-1);
   }

   server.sin_family = AF_INET;
   server.sin_port = htons(PORT); 
   /* htons() es necesaria nuevamente ;-o */
   //server.sin_addr = *((struct in_addr *)he->h_addr);  
	server.sin_addr.s_addr=inet_addr(argv);
   /*he->h_addr pasa la información de ``*he'' a "h_addr" */
   //bzero(&(server.sin_zero),8);

   if(connect(fd, (struct sockaddr *)&server,
      sizeof(struct sockaddr))!=-1){ 
      /* llamada a connect() */
      printf("connect() error\n");
      return(1);
   }
	else
		printf("Conexion exitosa\n");
	while(1){
				int i;
				char ch;
	    		for(i=0; i<2048||datosenviados[i]!='\0'; i++)
				{
	    			datosenviados[i] = '\0';
	    		}
	    		i = 0;
	    		while( (ch=getchar())!='\n' )
				{
            		datosenviados[i]=ch;
            		i++;
     			}
				
				if(send(fd,datosenviados,sizeof(datosenviados),0)<0){
					perror("envio fallido\n");
					cierra_cliente();
	    			exit(1);
				}
				else if(strcmp(datosenviados,"Exit")==0){
					printf("Salida");
					cierra_cliente();
					return;
				}	
	}
}
