//Inclusion de codigo
#include "Communicator.h"
#include <stdio.h>
#include <string.h>
//Definicion de MACROS
#define MAX_CONTACTS 10

contacto contactos[MAX_CONTACTS]; //Arreglo de contactos

void CargaContactos()
{
	char datos[256];
	char valor;
	FILE *fp;
	fp = fopen("contactos.txt", "r");
	if(fp==NULL)
		printf("No hay archivo de contactos\n");
	else
	{
		valor=fgetc(fp);
		int cont=0;
		while (!feof(fp))
	    {
			if(valor=='\n')
				{
					char *subs;
					subs = strtok (datos,",");
					while (subs != NULL)
					  {
						//printf ("%s\n",subs);     // Aqui deberias guardar tu dato en el array!
						*(contactos[TotalContactos()]).nombre=*subs;
						subs = strtok (NULL, ",");  // Aca tambien iria solo la coma.!!
					  }
				}
			datos[cont]=valor;
			valor=fgetc(fp);			
			cont++;
	    }
	}
	//printf("%s",datos);
	printf("%s \n",contactos[0].nombre);

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
