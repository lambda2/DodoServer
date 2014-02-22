/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 03:11:28 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/22 03:11:33 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dodo.h"

static void			handlers_init(void)
{
	signal(9, handlerExit);
	signal(SIGINT, handlerExit);
	signal(SIGKILL, handlerExit);
	signal(SIGTERM, handlerExit);
	signal(SIGCHLD, handlerGetOutSon);
}

void				dds_listen(t_ddp *p)
{
	int				binder;
	int				listener;

	binder = listener = 0;
	p->sock = socket(AF_INET,SOCK_STREAM,0);
	if (p->sock >= 0) /* On a reussi a creer la sock */
	{
		binder = bind(p->sock, (ska *)&p->sockaddr, sizeof(skad));
		if (binder >= 0) /* On a reussi a binder */
		{
			listener = listen(p->sock, 1);
			if (listener < 0)
				perror("DDS [listen]");
		}
		else
			perror("DDS [bind]");
	}
	else
		perror("DDS [socket]");
}

t_ddp				*get_ddp(void)
{
	static t_ddp*	p = NULL;

	if (p == NULL)
	{
		printf("Creating new ddp...\n");
		p = (t_ddp *)ft_memalloc(sizeof(t_ddp));
		p->sock = -1;
		p->in_loop = 1;
		memset(&p->sockaddr, 0, sizeof(p->sockaddr));
		p->sockaddr.sin_family = AF_INET;
		p->sockaddr.sin_port = ntohs(8080);
		p->sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		return (p);
	}
	else
	{
		return (p);
	}
}

int					dds_loop(t_ddp *p)
{
	int				sockfd;
	unsigned int	max_size;
	int				fork_pid;
	char			*buffer;

	printf("Ready to loop : %d\n", p->in_loop);
	while (p->in_loop)
	{
		printf("Loop starts.\n");
		max_size = sizeof(skad *);
		sockfd = accept(p->sock, (ska *)&p->sockaddr, &max_size);
		if (sockfd >= 0)
		{
			fork_pid = fork();
			if (fork_pid == 0)
			{
				buffer = ft_strnew(BUF_SIZE);
				if (read(sockfd, buffer, BUF_SIZE) < 0)
					perror("DDS [reading sock data]");
				printf("Received : %s\n", buffer);
				write(sockfd,
					  "<h1>Hello <small>fucking</small> world ! :D</h1>\n",
					  ft_strlen("<h1>Hello <small>fucking</small> world ! :D</h1>\n"));
				p->in_loop = 0;
				printf("Closing...\n");
				exit(0);
			}
			close(sockfd);
		}
		else
			perror("DDS [accept]");
	}
	close(p->sock);
	return (1);
}

int					launch_server(void)
{
	t_ddp	*p;

	p = get_ddp();
	handlers_init();
	dds_listen(p);
	dds_loop(p);
	printf("Bye.\n");
	return (0);
}
