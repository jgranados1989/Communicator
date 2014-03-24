#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[])
{
         FILE * fp;
       char * line = NULL;
       size_t len = 0;
       ssize_t read;

       char usuario[100];

       fp = fopen("archivo.txt", "r");

       printf("Ingresa el nombre que deseas buscar...\n");
       scanf("%s",&usuario);

       while ((read = getline(&line, &len, fp)) != -1) {
          // printf("Retrieved line of length %zu :\n", read);
          char* nombre= strtok(line,",");
          char* IP = strtok(NULL,",");
          char* puerto = strtok(NULL,",");
          int result = strncmp(nombre,usuario,100);
          if(result==0){
            printf("El usuario si está en la lista\n");
            break;
          }
          else{
            printf("El usuario no existe :(\n");
          }

       }
       printf("\n");

  return 0;
}