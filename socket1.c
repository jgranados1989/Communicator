#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int s;

void abre_socket()
{
//	int s;
	s=socket(PF_INET,SOCK_STREAM,0);
	if (s<0)
		printf("Error en creacion de socket\n");
	else
		printf("Socket creado correctamente: %d \n",s);
}

void cierra_socket()
{
	if(close(s)==0)
		printf("Socket cerrado correctamente\n");
	else
		printf("Error al cerrar socket\n");
}

void asigna_puerto()
{

}

main()
{
	abre_socket();
	cierra_socket();	
}
