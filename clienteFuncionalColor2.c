#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int cliente(char *direccion){
	int sock,bytesrecibidos;
 	struct sockaddr_in cliente;
 	char datosenviados[2048];
 	char datosrecibidos[2048];
 	char nombrerecibido[100];
 	char nombreenviado[100];
 	char datoColor[2048]="\x1b[36m";
 	struct hostent *hp;

 	printf("Digite su username: ");
	scanf("%s",nombreenviado);

 	sock = socket(AF_INET,SOCK_STREAM,0);
 	if(sock<0){
 		perror("No se creó el socket\n");
   		exit(1);
  	}
 	else{
  		printf("\t \t \x1b[32mBienvenido a Communicator\x1b[0m\n");
  		printf("\t \t \x1b[36mIngresa 'Exit' en cualquier momento para salir\x1b[0m\n");
  		printf("\n");
  		printf("\n");
    }

 	cliente.sin_family = AF_INET;         
 	cliente.sin_port = htons(9005);
 	cliente.sin_addr.s_addr = inet_addr(direccion); //Conexión compu-compu
 	bzero(&(cliente.sin_zero),8); 
 
 	if(connect(sock,(struct sockaddr *)&cliente,sizeof(cliente))<0){
  		perror("conexion fallida\n");
  		close(sock);
  		exit(1);
 	}

	else{
    		while(1){
    			send(sock,nombreenviado,sizeof(nombreenviado),0);
	    		char datoColor[2048]="\x1b[36m";
	    		printf("%s", nombreenviado);
	    		while( (ch=getchar())!='\n' )
            		strcat(datosenviados,ch);
     			}
				scanf("%s",datosenviados);
				if(strcmp(datosenviados,"Exit")==0){
					printf("Salida");
					close(sock);
					return;
				}
    			strcat(datoColor,datosenviados);
    			strcat(datoColor,"\x1b[0m");
				if(send(sock,datoColor,sizeof(datoColor),0)<0){
					perror("envio fallido\n");
					close(sock);
	    			exit(1);
				}
			}
		}
	
	return 0;
}
