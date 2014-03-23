#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char str[100], *s = str, *t = NULL;

    strcpy(str, "Esteban,127.0.0.1,8080");

 // while ((t = strtok(s, " ")) != NULL) {
 // 	s = NULL;
 // 	printf(":%s:\n", t);
 // }

  char* nombre= strtok(str,",");
  char* IP = strtok(NULL,",");
  char* puerto = strtok(NULL,",");

  printf("el contacto: %s \ntiene la IP: %s \ny el puerto: %s \n", nombre, IP,puerto);
  return 0;




}