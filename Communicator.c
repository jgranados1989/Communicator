//Inclusion de codigo
#include "Communicator.h"
#include <stdio.h>
#include <string.h>
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
contacto contactos[MAX_CONTACTS]; //Arreglo de contactos de cantidad MAX_CONTACTS

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
	if(fp==NULL)
		printf(ANSI_COLOR_RED"Error: " ANSI_COLOR_RESET "No hay archivo de contactos\n");
	else
	{
		printf(ANSI_COLOR_GREEN "Archivo de contactos encontrado\n"ANSI_COLOR_RESET);
		cont=0;
		while ((read = getline(&line, &len, fp)) != -1)
		{
          char* nombre= strtok(line,",");
          char* IP = strtok(NULL,",");
          char* puerto = strtok(NULL,",");
          contacto actual;
		  actual=contactos[cont];
		  actual.ip=IP;
		  actual.nombre=nombre;
		  actual.puerto=*puerto;
		  printf("%s %s %d\n",actual.nombre,actual.ip,actual.puerto);
		}
	}
	//printf("%s",datos);
//	printf("%s \n",contactos[0].nombre);

}

int TotalContactos()//Retorna la cantidad de contactos que existen en el arreglo
{
	int cont=0,i=0;
	while(i<MAX_CONTACTS)
	{
		if(*(contactos[i]).ip)
			cont++;
		i++;
	}
	return cont;
}

void AgregarContactos(){

	char usuario[256];
	char ip[256];
	char puerto[256];

	printf("Escribe tu nombre de usuario\n");
	scanf("%s",usuario); //hago un scan y almaceno el valor en la variable usuario.

	printf("Escribe tu dirección IP\n");
	scanf("%s",ip); //hago un scan y almaceno el valor en la variable ip

	printf("Escribe tu dirección de puerto\n");
	scanf("%s",puerto); //hago un scan y almaceno el valor en la variable usuario.

	//Las siguientes 3 linea agregan el contacto al arreglo de contactos para un manejo mas eficiente
	*(contactos[TotalContactos()]).ip=*ip;//agrega la ip al nuevo contacto
//	contactos[TotalContactos()].nombre=usuario;//agrega el nombre al nuevo usuario
	contactos[TotalContactos()].puerto=*puerto;//agrega el puerto al nuevo usuario

	//Las siguientes 2 lineas agregan el contacto al archivo txt
	FILE *fp = fopen("contactos.txt", "a"); //creo un puntero del tipo File y cargo el archivo hola.txt, si el archivo no existe, lo crea y si existe escribe al final
	fprintf(fp, "%s, %s, %s \n", usuario, ip, puerto);//escribo la variable a en el archivo archivo.txt

}

main()
{
	//printf("%d \n",TotalContactos());
	//TotalContactos();
	//AgregarContactos();
	//AgregarContactos();
	//printf("%d \n",TotalContactos());
	CargaContactos();
}
