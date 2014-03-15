//ejemplo sockets hecho a mano
#include <stdio.h> //Libreria de E/S estandar
#include <sys/types.h> //No se aun para que es
#include <sys/socket.h> //Libreria de sockets
#include "SocketsManuales.h"	
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>

#define PUERTO 8080
#define IP "192.168.1.132"
#define BACKLOG 10 /* El número de conexiones permitidas */

struct sockaddr_in servidor;
struct sockaddr_in cliente;
int fd2;

void asigna_servidors()
{
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons (PUERTO);// Número de puerto donde recibirá paquetes el programa
	servidor.sin_addr.s_addr = inet_addr (IP); // IP por la que recibirá paquetes el programa 
}

void escucha_acepta()
{
	// Asignar valores a la estructura my_addr
	printf("1\n");
	bind(socket01, (struct sockaddr *)&servidor, sizeof(struct sockaddr)); 
	printf("2\n");
	listen(socket01,BACKLOG);
	printf("3\n");
	int addrlen=sizeof(struct sockaddr);
	printf("4\n");
	fd2=accept(socket01, (struct sockaddr *)&cliente, &addrlen);
	printf("6\n");

	//close(socket01);
}

int crea_socket()
{
	socket01=socket(AF_INET,SOCK_STREAM,0);
	return socket01;
}

int asigna_bind()
{
	bind01=bind(socket01,(struct sockaddr *) &servidor,sizeof(struct sockaddr));
	return bind01;
}

main()
{	
	printf("1\n");
	printf("Socket creando: %d\n",crea_socket());
	printf("2\n");
	asigna_servidors();
	printf("3\n");
	printf("Asignacion Socket: %d\n",asigna_bind());
	printf("4\n");
	escucha_acepta();
	printf("5\n");
	//printf("Cliente: %s\n",inet_ntoa(cliente.sin_addr));

	printf("%d.%d.%d.%d\n",(int)(cliente.sin_addr.s_addr&0xFF),(int)((cliente.sin_addr.s_addr&0xFF00)>>8),(int)((cliente.sin_addr.s_addr&0xFF0000)>>16),(int)((cliente.sin_addr.s_addr&0xFF000000)>>24));

	printf("Puerto; %d\n",ntohs(cliente.sin_port));

	send(fd2,"Bienvenido a mi servidor.\n",25,0);
	close(socket01);
	/*
	switch (fork())
	{
		case -1:
		    // Código de error
		    printf("Jodido");
		    break;
		case 0:
			socket_cliente=socket(AF_INET,SOCK_STREAM,0);
			cliente.sin_family = AF_INET;
			cliente.sin_port = htons (PUERTO);// Número de puerto donde recibirá paquetes el programa
			cliente.sin_addr.s_addr = inet_addr (IP); // IP por la que recibirá paquetes el programa 
			printf("Cliente\n");
			addrlen = sizeof (struct sockaddr );
			bind_cliente=bind(socket_cliente,(struct sockaddr *) &servidor, sizeof (servidor) );
			printf("Conexion: %d\n",connect(socket_cliente, (struct sockaddr*) &servidor, addrlen));
			char mens_clien[100]  = "Ejemplo";
			send(socket01, mens_clien, strlen(mens_clien)+1, 0);
			printf("Fin cliente\n");
		    // Código del proceso hijo
		    break;
		default:
		    printf("Socket creado: %d\n",crea_socket());
			asigna_servidors();
			printf("Asignacion Socket: %d\n",asigna_bind());
			escucha_acepta();
			char mens_serv[100];
			printf("Bytes recibidos: %d\n",recv(socket_cliente, mens_serv, 100, 0)); 
			wait(estadoHijo);

	} 	*/
}
