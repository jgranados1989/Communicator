//Inclusion de codigo
#include "Communicator.h"
#include <stdio.h>
#include <string.h>
#include "servidor.c"
#include "cliente.c"

//Definicion de MACROS
#define MAX_CONTACTS 20
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
//Colores configurados para mostrar "error" y "advertencia" en otro color en los mensajes.
#define PERROR ANSI_COLOR_RED "Error: " ANSI_COLOR_RESET 
#define PWARNING ANSI_COLOR_YELLOW "Advertencia: " ANSI_COLOR_RESET
#define PINFO ANSI_COLOR_GREEN "Informacion: " ANSI_COLOR_RESET
#define GRACIAS printf("Gracias por utilizar Communicator!\n"); //imprimir un mensaje al final del programa
#define CONTACTO_ACTUAL "%s\t%s\t%s",actual.nombre,actual.ip,actual.puerto //para imprimir el contacto
contacto contactos[MAX_CONTACTS]; //Arreglo de contactos de cantidad MAX_CONTACTS
int total_contactos=0; 	//Variable que guarda el numero total de contactos

int CargaContactos() 	//funcion que carga los contactos del archivo contactos.txt
{
	char datos[256];
	char valor;
	char * line = NULL; //variables utilizadas en la lectura y gestion de las lineas de contactos.txt
    size_t len = 0;		//variables utilizadas en la lectura y gestion de las lineas de contactos.txt
    ssize_t read;		//variables utilizadas en la lectura y gestion de las lineas de contactos.txt
	int cont;			//variable contador
	FILE *archivo;		//variable de archivo "archivo"
	archivo = fopen(CONTACTOS, "r");	//apertura del archivo en modo lectura
	printf("Buscando archivo de contactos...\n");
	if(archivo==NULL)	//Imprime un mensaje de error si el archivo de contactos no existe
		{
			printf(PERROR "Archivo de contactos no encontrado\n");
			return 1; //Retorna 1 al main indicando que el archivo de contactos no fue encontrado
		}
	else
	{
		printf("Archivo de contactos encontrado\n");
		while ((read = getline(&line, &len, archivo)) != -1) //Comienza a leer linea por linea y a dividir cada linea de acuerdo a la estructura definida en el archivo contactos.txt
		{
		  //Separa cada linea del archivo por medio de la coma
          char* nombre= strtok(line,",");
		  char* ipdir = strtok(NULL,",");
          char* puerto = strtok(NULL,",");          
		  strcpy(contactos[total_contactos].nombre,nombre);//ingresa el nombre al struct contacto actual
		  strcpy(contactos[total_contactos].puerto,puerto);//ingresa el puerto al struct contacto actual
		  strcpy(contactos[total_contactos].ip,ipdir);//ingresa la ip al struct contacto actual
		  total_contactos++;
		}
		printf("Contactos importados:" ANSI_COLOR_GREEN " %d\n"  ANSI_COLOR_RESET, total_contactos);
	}
	return 0;
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
		printf("Contacto: %s - %s - %s\n",usuario,puerto,ip);
		strcpy(contactos[total_contactos].nombre,usuario);
		strcpy(contactos[total_contactos].puerto,puerto);
		strcpy(contactos[total_contactos].ip,ip);
		
		//Las siguientes 2 lineas agregan el contacto al archivo txt
		FILE *archivo = fopen(CONTACTOS, "a"); //creo un puntero del tipo File y cargo el archivo hola.txt, si el archivo no existe, lo crea y si existe escribe al final
		fprintf(archivo, "%s,%s,%s\n", usuario, ip, puerto);//escribo la variable a en el archivo archivo.txt
		close(archivo);
		printf(PINFO "Contacto agregado exitosamente!\n");
	}
	return;
}

void ImprimeContactos()
{
	int cont=0;
	printf(ANSI_COLOR_CYAN "NOMBRE\t    IP    \tPUERTO\n" ANSI_COLOR_RESET);//Cabecera de la impresion
	while(cont<=total_contactos)//Ciclo que imprime cada contacto con su info
	{
		contacto actual=contactos[cont];		
		printf(CONTACTO_ACTUAL);
		cont++;
	}
	printf(ANSI_COLOR_YELLOW "\n==========Fin de contactos==========\n" ANSI_COLOR_RESET);
}

contacto iniciaChat()
{
	int pid;
	int i;
	int estado;
	contacto actual;
	char nombre[256];
	ImprimeContactos();
	printf("Digita el nombre del contacto: ");
	scanf("%s",nombre);
	int cont=0;
	while(cont<total_contactos)//Ciclo que imprime cada contacto con su info
	{
		actual=contactos[cont];
		//printf("Nombre: %s\n",actual.nombre);		
		if(strcmp(actual.nombre,nombre)==0){
			printf(PINFO "Contacto encontrado\n");
			break;}
		else if(cont==total_contactos){
		printf(PERROR "Contacto no encontrado\n");
		return;}
		cont++;
	}
	pid=fork();
	switch(pid)
	{
		case -1: // Si pid es -1 quiere decir que ha habido un error
			perror("No se ha podido crear el proceso hijo\n");
			break;
		case 0: // Cuando pid es cero quiere decir que es el proceso hijo
			abre_cliente(actual.ip,actual.nombre);
			cierra_cliente();			
			break;			
		default: // Cuando es distinto de cero es el padre
			abre_servidor();
			wait(pid);
			cierra_servidor();
			break;
	} 
	cierra_servidor();
	cierra_cliente();
	return;
}

void menu()
{
	int i=1;
	while(i)
	{
		//system("clear");
	printf("\t\t"ANSI_COLOR_GREEN" *** "ANSI_COLOR_RESET"MENU PRINCIPAL COMMUNICATOR"ANSI_COLOR_GREEN" ***\n"ANSI_COLOR_RESET);
		int opcion;
		printf(ANSI_COLOR_YELLOW "1." ANSI_COLOR_RESET "Agregar contactos\n");
		printf(ANSI_COLOR_YELLOW "2." ANSI_COLOR_RESET "Imprimir contactos\n");
		printf(ANSI_COLOR_YELLOW "3." ANSI_COLOR_RESET "Iniciar chat\n");
		printf(ANSI_COLOR_YELLOW "0." ANSI_COLOR_RESET "Salir\n");
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
			switch(opcion)
			{
				case 1:
					AgregarContactos();
					break;
				case 2:
					ImprimeContactos();
					break;
				case 3:
					iniciaChat();
					break;
				default:
					i=0;
					GRACIAS
					break;
			}			
		}
	}
	return;
}

main()
{
	system("clear");
	printf("\t\t"ANSI_COLOR_GREEN" *** "ANSI_COLOR_RESET"BIENVENIDO A COMMUNICATOR"ANSI_COLOR_GREEN" ***\n"ANSI_COLOR_RESET);
	char opcion; 
	/************************************************************************
	 * Este bloque intenta cargar los contactos, en caso de no encontrarlo	*
	 * pregunta al usuario si desea continuar sin contactos, si el usuario	*
	 * responde 'N' o 'n' el programa se cierra								*
	 ************************************************************************/
	if(CargaContactos()==1)
	{
		printf(PWARNING "Archivo de contactos no encontrado\nDesea continuar? S/N: ");
		scanf("%c",&opcion);
		if(toupper(opcion)=='N')
		{
			GRACIAS
			return;
		}
	}
	menu();
}
