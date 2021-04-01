#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include <signal.h>

class CTcpServer
{
private:
	int m_serverfd;
public:
	long m_clientfd; // 作为创建线程的传入参数时，会遇到类型转换问题，所以使用long型。

	/*CTcpServer();*/
	~CTcpServer();

	bool server_init();
	bool server_accept();

	int m_recv(char* buffer);
	int m_send(char* buffer);

	void close_clientfd();
	void close_listen();
};

class CTcpClient
{
private:
	int m_clientfd;
public:
	/*CTcpClient();*/
	~CTcpClient();

	bool client_connect(int port);

	void m_recv(char* buffer);
	void m_send(char* buffer);
};
