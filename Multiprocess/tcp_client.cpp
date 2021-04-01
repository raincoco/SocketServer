#include"tcp_socket.h"

CTcpClient::~CTcpClient()
{
	if (m_clientfd > 0) { close(m_clientfd); };
}

/* 连接服务器函数 */
bool CTcpClient::client_connect(int port)
{
	m_clientfd = socket(AF_INET, SOCK_STREAM, 0);

	if (m_clientfd < 0)
	{
		perror("socket");
		return false;
	}
	/*	struct hostent* h;
 *			if ((h = gethostbyname("172.27.0.17")) == 0)
 *					{
 *								perror("gethostname"); close(clientfd); return -1;
 *										}
 *											*/
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr("172.27.0.17");
	/*memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);*/

	if (connect(m_clientfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("connect");
		close(m_clientfd);
		return false;
	}

	return true;
}

/* 数据收发函数 */
void CTcpClient::m_recv(char* buffer)
{
	if (recv(m_clientfd, buffer, sizeof(buffer), 0) == -1)
	{
		perror("recv");
	}
}

void CTcpClient::m_send(char* buffer)
{
	if (send(m_clientfd, buffer, sizeof(buffer), 0) == -1)
	{
		perror("send");
	}
}
