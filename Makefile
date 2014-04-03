#makefile para el programa Communicator
COMMU=Communicator.c
compilacion:
		@echo Creando el archivo Communicator.out
		gcc $(COMMU) -o Communicator.out
		@echo Compilacion finalizada
