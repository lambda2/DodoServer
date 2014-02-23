/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 03:11:28 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/22 03:11:33 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dodo.h"
#include "http_head.h"

int					treat_request(t_http_head *h, t_ddp *p, int clisock)
{
	int				status;
	int				res;
	int				file_d;
	int				_pipe[2];
	char				**e;

	res = 0;
	file_d = open("php.log", O_CREAT, 0777);

	pipe(_pipe);
	if (fork() == 0)
	{
		e = (char **)ft_memalloc(sizeof(char *) * 2);
		bzero(e, sizeof(char *) * 2);
		e[0] = h->target;
		close(_pipe[0]);    // close reading end in the child

		dup2(_pipe[1], 1);  // send stdout to the pipe
		dup2(file_d, 2);  // send stderr to the pipe

		close(_pipe[1]);    // this descriptor is no longer needed

		execl("/usr/bin/php", "/usr/bin/php", h->target, NULL);
		exit(0);
	}
	else
	{
		wait(&status);
		char *buffer = ft_strnew(1024);

		close(_pipe[1]);  // close the write end of the pipe in the parent

		while (get_next_line(_pipe[0], &buffer))
		{
			ft_putendl_fd(buffer, clisock);
		}
	}

	return (res);
}
