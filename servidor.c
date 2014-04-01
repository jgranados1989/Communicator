//ejemplo sockets hecho a mano
#include <stdio.h> //Libreria de E/S estandar
#include <sys/types.h> //No se aun para que es
#include <sys/socket.h> //Libreria de sockets
#include <netinet/in.h>
#include "servidor.h"	
#include <string.h>

#include <stdlib.h>
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
/*#ifdef WIN32
#include <windows.h>
#define MIIP system("ipconfig")
#else
#include <unistd.h>
#define MIIP system("hostname -I")
#endif*/

#define BACKLOG 10 /* El número de conexiones permitidas */
#define MAXDATASIZE 100   
#define CONF "conf.txt" //Nombre del archivo de contactos

struct sockaddr_in servidor;
struct sockaddr_in cliente;
int puerto;
char *MIIP;
char nombrerecibido[256];
char datosrecibidos[2048]; 
char mensaje[256];
int fd2,sd;
fd_set read_fds;

void cierra_servidor()
{
	close(socket01);
}

void carga_conf()
{
	size_t len = 0;
	char *cadena;
	ssize_t linea;
	FILE *fp = fopen(CONF, "r");
	linea=getline(&cadena, &len, fp);
	char* puerto2= strtok(cadena,",");
	char* miip=strtok(NULL,",");
	puerto=atoi(puerto2);
	//printf("Mi puerto: %s\n",htons(puerto2));
	//printf("Mi IP: %s",miip);
	MIIP=miip;
	fclose(fp);
}


void asigna_servidors()
{
//	printf("%d",inet_ntoa(MIIP));
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons (puerto);// Número de puerto donde recibirá paquetes el programa
	servidor.sin_addr.s_addr = inet_addr (MIIP); // IP por la que recibirá paquetes el programa 
	bzero(&(servidor.sin_zero),8);
}

void escucha_acepta()
{
	listen(socket01,BACKLOG);
	int addrlen=sizeof(struct sockaddr);
	fd2=accept(socket01, (struct sockaddr *)&cliente, &addrlen);
}

int crea_socket()
{
	socket01=socket(AF_INET,SOCK_STREAM,0);
	return socket01;
}

int asigna_bind()
{
	bind01=bind(socket01,(struct sockaddr *) &servidor,sizeof(servidor));
	return bind01;
}

void abre_servidor()
{
	carga_conf();	
	if(crea_socket()!=0)
		printf("Error en creacion de socket");
	asigna_servidors();
	if(asigna_bind()!=0)
		printf("Error en asignacion de socket");
	escucha_acepta();
	printf("Cliente %d.%d.%d.%d\n",
		  (int)(cliente.sin_addr.s_addr&0xFF),
		  (int)((cliente.sin_addr.s_addr&0xFF00)>>8),
		  (int)((cliente.sin_addr.s_addr&0xFF0000)>>16),
		  (int)((cliente.sin_addr.s_addr&0xFF000000)>>24));
	printf("Puerto: %d\n",cliente.sin_port);
	while(1)
			{
			recvfrom(fd2,datosrecibidos,sizeof(datosrecibidos),0,(struct sockaddr*) &cliente,&sd);
			//recv(fd2,datosrecibidos, sizeof(datosrecibidos) ,0);
			if(strcmp(datosrecibidos,"Exit")==0){
				cierra_servidor();
				return;}
			else{
				printf("Mensaje entrante: ");
				printf(ANSI_COLOR_CYAN "%s\n" ANSI_COLOR_RESET,datosrecibidos);
	    		}	
			}
		cierra_servidor();
		return;
}
