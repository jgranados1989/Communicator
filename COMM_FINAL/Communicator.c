//Inclusion de codigo
#include "Communicator.h"
#include <stdio.h>
#include <string.h>
#include "servidor.c"
#include "cliente.c"

//Definicion de MACROS
#define MAX_CONTACTS 10
#define CONTACTOS "contactos.txt" //Nombre del archivo de contactos
//Colores para impresion en consola
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//Fin colores
#define PERROR ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET 
#define CONTACTO_ACTUAL "%s\t%s\t%s",actual.nombre,actual.ip,actual.puerto //para imprimir el contacto
contacto contactos[MAX_CONTACTS]; //Arreglo de contactos de cantidad MAX_CONTACTS
int total_contactos=0; //Variable que guarda el numero total de contactos

void CargaContactos()
{
	char datos[256];
	char valor;
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	int cont;
	FILE *fp;
	fp = fopen(CONTACTOS, "r");
	printf("Buscando archivo de contactos...\n");
	if(fp==NULL)//Imprime un mensaje de error si el archivo de contactos no existe
		printf(PERROR "No hay archivo de contactos\n");
	else
	{
		printf("Archivo de contactos encontrado\n");
		while ((read = getline(&line, &len, fp)) != -1)
		{
		  //Separa cada linea del archivo por medio de la coma
          char* nombre= strtok(line,",");
		  char* ipdir = strtok(NULL,",");
          char* puerto = strtok(NULL,",");          
		  strcpy(contactos[total_contactos].nombre,nombre);
		  strcpy(contactos[total_contactos].puerto,puerto);
		  strcpy(contactos[total_contactos].ip,ipdir);
		  total_contactos++;
		}
		printf("Contactos importados:" ANSI_COLOR_GREEN " %d\n"  ANSI_COLOR_RESET, total_contactos);
	}
	return;
}

void AgregarContactos(){
	if (total_contactos==MAX_CONTACTS)
		printf(PERROR "Maximo numero de contactos alcanzado\n");
	else
	{
		char usuario[256];
		char ip[256];
		char puerto[256];

		printf("Escribe tu nombre de usuario\n");
		scanf("%s",usuario); //hago un scan y almaceno el valor en la variable usuario.

		printf("Escribe tu dirección IP\n");
		scanf("%s",ip); //hago un scan y almaceno el valor en la variable ip

		printf("Escribe tu dirección de puerto\n");
		scanf("%s",puerto); //hago un scan y almaceno el valor en la variable usuario.
		strcpy(contactos[total_contactos].nombre,usuario);
		strcpy(contactos[total_contactos].puerto,puerto);
		strcpy(contactos[total_contactos].ip,ip);
		
		//Las siguientes 2 lineas agregan el contacto al archivo txt
		FILE *fp = fopen(CONTACTOS, "a"); //creo un puntero del tipo File y cargo el archivo hola.txt, si el archivo no existe, lo crea y si existe escribe al final
		fprintf(fp, "%s, %s, %s \n", usuario, ip, puerto);//escribo la variable a en el archivo archivo.txt
	}
	return;
}
void ImprimeContactos()
{
	int cont=0;
	printf(ANSI_COLOR_CYAN "NOMBRE\t    IP    \tPUERTO\n" ANSI_COLOR_RESET);//Cabecera de la impresion
	while(cont<total_contactos)//Ciclo que imprime cada contacto con su info
	{
		contacto actual=contactos[cont];		
		printf(CONTACTO_ACTUAL);
		cont++;
	}
	printf(ANSI_COLOR_YELLOW "==========Fin de contactos==========\n" ANSI_COLOR_RESET);
	return;
}

contacto iniciaChat()
{
	int pid;
	int i;
	int estado;
 
	char nombre[256];
	ImprimeContactos();
	printf("Digita el nombre del contacto: ");
	scanf("%s",nombre);
	int cont=0;
	contacto actual;
	while(cont<total_contactos)//Ciclo que imprime cada contacto con su info
	{
		actual=contactos[cont];		
		if(strcmp(actual.nombre,nombre)==0){
			printf("Contacto encontrado\n");
			break;}
		cont++;
	}

	//pid = fork();
	//abre_servidor();
	//printf("Servidor cerrado\n");
	//cierra_servidor();
	//abre_cliente(actual.ip,actual.nombre);
	//cierra_cliente();	
	//cierra_servidor();
	pid=fork();
	switch(pid)
	{
		case -1: // Si pid es -1 quiere decir que ha habido un error
			perror("No se ha podido crear el proceso hijo\n");
			break;
		case 0: // Cuando pid es cero quiere decir que es el proceso hijo
			printf("%s",actual.ip);
			abre_cliente(actual.ip,actual.nombre);
			cierra_cliente();			
			break;
		default: // Cuando es distinto de cero es el padre
			abre_servidor();
			wait(pid);
			cierra_servidor();
			printf("Fin de servidor\n");
			cierra_servidor();
			break;
	} 
	return;
}

void menu()
{
	int i=1;
	system("clear");
	while(i)
	{
		int opcion;
		printf(ANSI_COLOR_YELLOW "1." ANSI_COLOR_RESET "Agregar contactos\n");
		printf(ANSI_COLOR_YELLOW "2." ANSI_COLOR_RESET "Imprimir contactos\n");
		printf(ANSI_COLOR_YELLOW "3." ANSI_COLOR_RESET "Iniciar chat\n");
		printf("Opcion: ");
		scanf("%d",&opcion);
		if(opcion<0 || opcion>9)
		{
			printf(PERROR "Valor invalido\n");
			i=0;
			break;
			return;
		}
		else
		{
			if(opcion==1)
				AgregarContactos();
			if(opcion==2)
				ImprimeContactos();
			if(opcion==3)
				iniciaChat();
			else{
				i=0;
				return;}
		}
	}
	return;
}
main()
{
	CargaContactos();
	menu();
}
