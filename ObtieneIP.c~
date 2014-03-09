#include <stdio.h>

//El siguiente bloque obtiene el valor de la ip actual dependiendo de la plataforma actual (Windows o Unix-like), que es guardado en la macro IP
#ifdef WIN32
#include <windows.h>
#define IP system("ipconfig")
#else
#include <unistd.h>
#define IP system("hostname -I")
#endif

//Imprime la direccion IP actual
//Entradas: none
//Salidas: none
void imprime_ip()
{
	printf("Mi ip es:\n");
	printf("%i",IP);
}

main()
{
	imprime_ip();	
}
