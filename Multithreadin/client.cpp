#include"tcp_socket.h"

int main()
{
	CTcpClient tcpclient;
	if (tcpclient.client_connect(8081) == false)
	{
		printf("Connect to the server failed.\n");
	}
	printf("Connect to the server sccessed.\n");

	char buffer[1024];

	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "hello");
	tcpclient.m_send(buffer);
	printf("send:%s\n", buffer);
	
	memset(buffer, 0, sizeof(buffer));
	tcpclient.m_recv(buffer);
	printf("recv:%s\n", buffer);

	tcpclient.~CTcpClient();
}
