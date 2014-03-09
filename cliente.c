#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

main()
{
	struct in_addr
	{
		unsigned long int s_addr;
	};

	struct sockaddr_in
	{
		int sin_family;
		unsigned short int sin_port;
		struct in_addr sin_addr;
	};

	int s;
	struct sockaddr_in dir;

	dir.sin_family=PF_INET;
	dir.sin_port=htons(80);

	s=socket(PF_INET,SOCK_STREAM,0);
	inet_aton("127.0.0.1",&dir.sin_addr);
	int con;
	con=connect(s, (struct sockaddr *)&dir, sizeof(struct sockaddr_in));
	//if (con==ECONNREFUSED)
	printf("Conexion: %d",con);
}
