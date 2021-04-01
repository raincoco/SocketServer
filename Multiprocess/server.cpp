#include"tcp_socket.h"

CTcpServer tcpserver;

void EXIT(int signal);

int main()
{
	/* signal忽略子进程信号 */
	signal(SIGCHLD,SIG_IGN);

	signal(SIGINT, EXIT);
	signal(SIGTERM, EXIT);

	/* 服务器初始化 */
	if (tcpserver.server_init() == false)
	{
		printf("Server initialization failed.\n");
		exit(-1);
	}
	printf("init server successed.\n");

	/* 客户端连接 */
	while (1)
	{
		/* 接受客户端连接 */
		printf("\nwaiting client connect......\n");
		if (tcpserver.server_accept() == false)
		{
			printf("Client request denied.\n");
			exit(-1);
		}
		printf("client connection successed.\n");

		/* 创建连接与客户端通信的子进程，父进程继续监听 */
		if (fork() > 0)
		{
			tcpserver.close_clientfd();
			continue;
		}

		/* 与客户端通信的子进程 */
		/* 关闭监听 */
		tcpserver.close_listen();

		/* 数据缓存区 */
		char buffer[1024];

		/* 数据交换 */
		while (1)
		{
			memset(buffer, 0, sizeof(buffer));
			if (tcpserver.m_recv(buffer) < 0) break;
			printf("recv:%s\n", buffer);
			sleep(10);
			memset(buffer, 0, sizeof(buffer));
			strcpy(buffer, "ok");
			if (tcpserver.m_send(buffer) < 0) break;
			printf("send:%s\n", buffer);
		}
		printf("\nOne client is disconnected\n");
		tcpserver.~CTcpServer();
		return 0;
	}
	
	/* 关闭连接 */
	printf("End of communication, disconnect.\n");
	tcpserver.~CTcpServer();
}

void EXIT(int signal)
{
	printf("signal=%d\n", signal);

	tcpserver.~CTcpServer();

	exit(0);
}
