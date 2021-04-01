#include"tcp_socket.h"
#include<pthread.h>

CTcpServer tcpserver;

void EXIT(int signal);
void *pthmain(void *arg);

int main()
{
	/* 信号处理 */
	/* signal忽略子进程信号 */
	for (int i = 0; i < 50; i++)
	{
		signal(i, SIG_IGN);
	}

	signal(SIGINT, EXIT);
	signal(SIGTERM, EXIT);

	/* 服务器初始化 */
	if (tcpserver.server_init() == false)
	{
		printf("Server initialization failed.\n");
		exit(-1);
	}
	printf("init server successed.\n");

	pthread_t pthid;

	/* 客户端连接 */
	while (1)
	{
		/* 接受客户端连接 */
		printf("\nServer waiting client connect......\n");
		if (tcpserver.server_accept() == false)
		{
			printf("Client request denied.\n");
			exit(-1);
		}
		printf("\nOnce client connection successed.\n");

		/* 创建线程，父进程返回继续监听 */
		printf("\nCreate a service terminal process to communicate with the client.\n");
	
		pthread_create(&pthid, NULL, pthmain, (void*)tcpserver.m_clientfd);
	}
	
	/* 关闭连接 */
	printf("End of communication, disconnect.\n");
	tcpserver.~CTcpServer();
}

void EXIT(int signal)
{
	printf("SIGNAL = %d\n", signal);

	tcpserver.~CTcpServer();

	exit(0);
}

void *pthmain(void *arg)
{
	int clientfd =(long)arg;
	/* 数据缓存区 */
	char buffer[1024];

	/* 数据交换 */
	while (1)
	{
		memset(buffer, 0, sizeof(buffer));
		if (recv(clientfd, buffer, sizeof(buffer), 0) <= 0) break;
		printf("recv:%s\n", buffer);
	
		sleep(10);		
	
		memset(buffer, 0, sizeof(buffer));
		strcpy(buffer, "ok");
		if (send(clientfd, buffer, sizeof(buffer), 0) <= 0) break;
		printf("send:%s\n", buffer);
	}
	close(clientfd);
	printf("\nOne client is disconnected\n");
	return((void *)0);
}
