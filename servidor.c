//ejemplo sockets hecho a mano
#include <stdio.h> //Libreria de E/S estandar
#include <sys/types.h> //No se aun para que es
#include <sys/socket.h> //Libreria de sockets
#include <netinet/in.h>
#include "servidor.h"	
#include <string.h>

#include <stdlib.h>

/*#ifdef WIN32
#include <windows.h>
#define MIIP system("ipconfig")
#else
#include <unistd.h>
#define MIIP system("hostname -I")
#endif*/

#define BACKLOG 2 /* El número de conexiones permitidas */
#define MAXDATASIZE 100   
#define CONF "conf.txt" //Nombre del archivo de contactos

struct sockaddr_in servidor;
struct sockaddr_in cliente;
int puerto;
char *MIIP;

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
	printf("Mi puerto: %s\n",puerto2);
	printf("Mi IP: %s",miip);
	MIIP=miip;
	fclose(fp);
}

int fd2;
void asigna_servidors()
{
//	printf("%d",inet_ntoa(MIIP));
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons (puerto);// Número de puerto donde recibirá paquetes el programa
	servidor.sin_addr.s_addr = inet_addr (MIIP); // IP por la que recibirá paquetes el programa 
}

void escucha_acepta()
{
	// Asignar valores a la estructura my_addr
	bind(socket01, (struct sockaddr *)&servidor, sizeof(struct sockaddr)); 
	listen(socket01,BACKLOG);
	int addrlen=sizeof(struct sockaddr);
	fd2=accept(socket01, (struct sockaddr *)&cliente, &addrlen);
//	close(socket01);
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

void cierra_servidor()
{
	close(socket01);
}
void abre_servidor()
{
	carga_conf();	
	printf("Socket creado: %d\n",crea_socket());
	asigna_servidors();
	printf("Asignacion Socket: %d\n",asigna_bind());
	escucha_acepta();
	printf("Cliente: %d\n",inet_ntoa(cliente.sin_addr));
	printf("Puerto; %d\n",ntohs(cliente.sin_port));
	char *mensaje;
	int estado=0;
	while(estado==0){

		scanf("%s",mensaje);
		if(strcmp(mensaje,"Exit")==0){
			send(fd2,mensaje,25,0);
			estado=1;}
		else{
			printf("mensaje enviado -%s-\n",mensaje);
			send(fd2,mensaje,25,0);		
			}
	  }
	return;
}
