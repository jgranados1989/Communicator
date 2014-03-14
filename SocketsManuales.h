//Variables varias
int addrlen;
int estadoHijo; 
//Variables de sockets
int socket01,socket_cliente;
 //Variables que asignan nombres a los sockets
int bind01,bind_cliente;

//Protoripo Estructura para obtener IP
struct in_addr{
	unsigned long s_addr; // 4 bytes.
}; 

//Prototipo Estructura que obtiene las direcciones de la maquina para el Bind
struct sockdir{
	short int sin_family; // AF_INET
	unsigned short sin_port; // Numero de puerto.
	struct in_addr sin_addr; // Dirección IP.
	unsigned char sin_zero[8]; // Relleno.  
};

//Funcion liste para escuchar (Servidor)
int listen (int sockfd, int backlog);

//Funcion accept, para aceptar conexiones (Servidor)
//int accept (int sockfd, struct sockaddr *addr, int *addrlen) ;

//Funcion connect, para conectarser al servidor (CLiente)
//int connect (int sockfd, struct sockaddr *serv_addr, int addrlen) ;
