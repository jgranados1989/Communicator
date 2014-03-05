#include<stdio.h>

void escribirArchivo(){

	char usuario[256];
	char ip[256];
	char puerto[256];

	printf("Escribe tu nombre de usuario\n");
	scanf("%s",usuario); //hago un scan y almaceno el valor en la variable usuario.

	printf("Escribe tu dirección IP\n");
	scanf("%s",ip); //hago un scan y almaceno el valor en la variable ip

	printf("Escribe tu dirección de puerto\n");
	scanf("%s",puerto); //hago un scan y almaceno el valor en la variable usuario.


	FILE *fp = fopen("archivo.txt", "w"); //creo un puntero del tipo File y cargo el archivo hola.txt, si el archivo no existe, lo crea

	fprintf(fp, "%s, %s, %s", usuario, ip, puerto);//escribo la variable a en el archivo archivo.txt

}



int main(int argc, char const *argv[])
{
	escribirArchivo(); //implemento la función.

	
	return 0;
}
