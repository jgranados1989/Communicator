#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

int servidor()
{

 int sock;
 char datosrecibidos[2048];    //arreglo para recibir los datos  
 char datosenviados[2048];
 char nombreenviado[15];
 char nombrerecibido[15];
 char datoColor[2048]="\x1b[34m";
 struct sockaddr_in servidor; //struct obligatorio   para puertos y almacenar direcciones
 int var1,misock;

 printf("digite su username: ");
 gets(nombreenviado);
 strcat(nombreenviado,":");

 sock = socket(AF_INET, SOCK_STREAM, 0);  
 int id;     
 if(sock ==-1)
  {
   perror("no se creo el socket");
   exit(1);
  }
 else{

 	//printf("\t \t \x1b[32mBienvenido a Communicator\x1b[0m\n");
  	//printf("\t \t \x1b[36mIngresa 'Exit' en cualquier momento para salir\x1b[0m\n");
  	//printf("\n");
  	printf("Servidor escuchando...\n");
    }

 servidor.sin_family = AF_INET;         
 servidor.sin_port = htons(9005);     
 servidor.sin_addr.s_addr = INADDR_ANY;
 bzero(&(servidor.sin_zero),8);

 if (bind(sock,(struct sockaddr *)&servidor,sizeof(servidor)))
 {
  perror("fallo el bind");
  exit(1);
 }

 listen(sock,5);
 //id=fork();
  misock = accept(sock, (struct sockaddr *)0,0);
  if (misock == -1)
   {perror("error al aceptar");
   }
  else
  {
	  if(fork()){
		  recv(misock,nombrerecibido,sizeof(nombrerecibido),0);
		  while(1){
			  if(strcmp(datosrecibidos,"Exit")==0)
					{
				printf("Salida");
				close(sock);
				return;}

			recv(misock,datosrecibidos,sizeof(datosrecibidos),0);
            printf("%s",nombrerecibido);                 
			printf("%s\n",datosrecibidos);

          		 }//
	  }
	  else{   send(misock,nombreenviado,sizeof(nombreenviado),0);
		  while(1){		
		  	char datoColor[2048]="\x1b[31m";
			scanf("%s",datosenviados);
			if(strcmp(datosenviados,"Exit")==0)
			{
				printf("Salida");
				close(misock);
				close(sock);
				exit(1);
				return;}
			strcat(datoColor,datosenviados);
        	strcat(datoColor,"\x1b[0m");
			if(send(misock,datoColor,sizeof(datoColor),0)<0){
			perror("envio fallido\n");
			close(misock);
			return;
			  }
			  //printf("enviado con exito \n");
 
		  }
	  }  
}
 



return 0;  
}

