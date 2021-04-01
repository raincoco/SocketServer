#include"tcp_socket.h"

CTcpServer::~CTcpServer()
{
	if (m_serverfd > 0) { close(m_serverfd); };
	if (m_clientfd > 0) { close(m_clientfd); };
}

/* 服务端初始化函数 */
bool CTcpServer::server_init()
{
	printf("server creat socket......\n");
	m_serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_serverfd < 0)
	{
		perror("socket");
		return false;
	}
	printf("creat socket success.\n");

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8081);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	printf("start bind......\n");
	if (bind(m_serverfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{
		perror("bind");
		close(m_serverfd);
		return false;
	}
	printf("bind completed.\n");

	printf("strat listening port.\n");
	if (listen(m_serverfd, 5) == -1)
	{
		perror("listen");
		close(m_serverfd);
		return false;
	}

	return true;
}
/* 服务端accept函数 */
bool CTcpServer::server_accept()
{
	m_clientfd = accept(m_serverfd, 0, 0);
	if (m_clientfd == -1)
	{
		perror("accept");
		close(m_serverfd);
		return false;
	}
	return true;
}

/* 数据收发函数 */
int CTcpServer::m_recv(char* buffer)
{
	if (recv(m_clientfd, buffer, sizeof(buffer), 0) <= 0) // 接收数据失败返回-1，远端关闭返回0
	{
		printf("Failed to recv data, or the client has closed the socket.\n");
		return -1;
	}
	return 0;
}

int CTcpServer::m_send(char* buffer)
{
	if (send(m_clientfd, buffer, sizeof(buffer), 0) <= 0) // 发送数据失败返回-1，远端关闭返回0
	{
		printf("Failed to send data, or the client has closed the socket.\n");
		return -1;
	}
	return 0;
}

/* 关闭clientfd */
void CTcpServer::close_clientfd()
{
	if (m_clientfd > 0)
	{
		close(m_clientfd);
		m_clientfd = 0;
	}
}

/* 关闭listen监听 */
void CTcpServer::close_listen()
{
	if (m_serverfd > 0)
	{
		close(m_serverfd);
		m_serverfd = 0;
	}
}

