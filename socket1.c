#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int s;

void abre_socket()
{
	s=socket(PF_INET,SOCK_STREAM,0);
	if (s<0)
		printf("Error en creacion de socket\n");
	else
	{
		printf("Socket creado correctamente: %d \n",s);
	}
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
	struct in_addr
	{
		unsigned long int s_addr;
	};

	struct sockaddr_in
	{
		int sin_family;
		unsigned short int sin_port;
		struct in_addr sin_addr;
	};

	int sockfd;

	struct sockaddr_in dir;

	dir.sin_family=PF_INET;//asignacion de la familia al objeto dir
	dir.sin_port=htons(80);// asignacion del puerto al objeto dir
	dir.sin_addr.s_addr=htonl(INADDR_ANY);//asignacion de las direcciones de escucha del objeto dir
	sockfd=socket(PF_INET,SOCK_STREAM,0); //apertura del socket
	int b;
	b=bind(sockfd, (struct sockaddr *)&dir,sizeof(struct sockaddr));//asignacion de puerto
	printf("Socket asignado: %d \n",b);
	int l;
	l=listen(sockfd,5);
	printf("Socket escuchando: %d \n",l);

	int sock_conectado, tam;
	tam=sizeof(struct sockaddr_in);

if ((sock_conectado=accept(sockfd, (struct
sockaddr *)&dir, &tam))<0)
{
printf("accept");
}


	/*sock_conectado=accept(sockfd,(struct sockaddr *)&dir,&tam);
	printf("Socket aceptando: %d \n",sock_conectado);
	*/
	inet_aton("127.0.0.1",&dir.sin_addr);
	int con;
	con=connect(sockfd, (struct sockaddr *)&dir, sizeof(struct sockaddr_in));
	printf("Socket conectado: %d \n",con);
}

main()
{
	abre_socket();
	asigna_puerto();
	cierra_socket();	
}
