//ejemplo sockets hecho a mano
#include <stdio.h> //Libreria de E/S estandar
#include <sys/types.h> //No se aun para que es
#include <sys/socket.h> //Libreria de sockets
#include "SocketsManuales.h"	
#include <string.h>
#define PUERTO 8080
#define IP "127.0.0.1"

struct sockdir dir,local_dir,remot_dir;
struct sockdir cliente;

void asigna_dirs()
{
	dir.sin_family = AF_INET;
	dir.sin_port = htons (PUERTO);// Número de puerto donde recibirá paquetes el programa
	dir.sin_addr.s_addr = inet_addr (IP); // IP por la que recibirá paquetes el programa 
}

void escucha_acepta()
{
	// Asignar valores a la estructura my_addr
	bind(socket01, (struct sockaddr *)&local_dir, sizeof(struct sockaddr)); 
	listen(socket01,5);
//	accept(socket01, (struct sockaddr *)&remot_dir, &addrlen);
}

int crea_socket()
{
	socket01=socket(AF_INET,SOCK_STREAM,0);
	return socket01;
}

int asigna_bind()
{
	bind01=bind(socket01,(struct sockaddr *) &dir, sizeof (dir) );
	return bind01;
}

main()
{
	
	
	switch (fork())
	{
		case -1:
		    /* Código de error */
		    printf("Jodido");
		    break;
		case 0:
			socket_cliente=socket(AF_INET,SOCK_STREAM,0);
			cliente.sin_family = AF_INET;
			cliente.sin_port = htons (PUERTO);// Número de puerto donde recibirá paquetes el programa
			cliente.sin_addr.s_addr = inet_addr (IP); // IP por la que recibirá paquetes el programa 
			printf("Cliente\n");
			addrlen = sizeof (struct sockaddr );
			bind_cliente=bind(socket_cliente,(struct sockaddr *) &dir, sizeof (dir) );
			printf("Conexion: %d\n",connect(socket_cliente, (struct sockaddr*) &dir, addrlen));
			char mens_clien[100]  = "Ejemplo";
			send(socket01, mens_clien, strlen(mens_clien)+1, 0);
			printf("Fin cliente\n");
		    /* Código del proceso hijo */
		    break;
		default:
		    printf("Socket creado: %d\n",crea_socket());
			asigna_dirs();
			printf("Asignacion Socket: %d\n",asigna_bind());
			escucha_acepta();
			char mens_serv[100];
			printf("Bytes recibidos: %d\n",recv(socket_cliente, mens_serv, 100, 0)); 
			wait(estadoHijo);

			/*...*/
			/**/
			/*send(sid, mens_clien, strlen(mens_clien)+1, 0);*/
			/*...*/
			/*recv(sid, mens_serv, 100, 0); */
		    /* Código del proceso original */
	} 	
}
