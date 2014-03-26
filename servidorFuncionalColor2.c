#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

void servidor(){
  	int sock;
  	char datosrecibidos[2048];    //arreglo para recibir los datos  
  	char datosenviados[2048];
  	//char nombreenviado[15];
  	char nombrerecibido[15];
  	char datoColor[2048]="\x1b[34m";
  	struct sockaddr_in servidor; //struct obligatorio   para puertos y almacenar direcciones
  	int var1,misock;

  	sock = socket(AF_INET, SOCK_STREAM, 0);  
  	int id;     
  	if(sock ==-1){
    	perror("no se creo el socket");
   		exit(1);
  	}
 	else{
  		printf("Servidor escuchando...\n");
    }

 	servidor.sin_family = AF_INET;         
 	servidor.sin_port = htons(9005);     
 	servidor.sin_addr.s_addr = INADDR_ANY;
 	bzero(&(servidor.sin_zero),8);

 	if (bind(sock,(struct sockaddr *)&servidor,sizeof(servidor))){
  		perror("Fallo el bind");
  		exit(1);
 	}

 	listen(sock,5);
  	misock = accept(sock, (struct sockaddr *)0,0);
  	if (misock == -1){
  		perror("Error al aceptar");
   	}
  	else{
		while(1){
		  	recv(misock,nombrerecibido,sizeof(nombrerecibido),0);
			if(strcmp(datosenviados,"Exit")==0){
				printf("Salida");
				close(sock);
				return;
			}
			recv(misock,datosrecibidos,sizeof(datosrecibidos),0);
			if (strcmp(datosrecibidos,NULL)==0){
				return
			}
            printf("%s",nombrerecibido);                 
			printf("%s\n",datosrecibidos);

        }
	} 
}
