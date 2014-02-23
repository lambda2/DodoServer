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
	pid_t			father;
	int				status;
	int				res;
	int				file_d;
	int				_pipe[2];

	res = 0;
	file_d = open("php.log", O_CREAT, 0777);
	father = fork();
	if (father > 0)
		wait(&status);
	else if (father == 0)
	{
		_pipe[1] = 0;
		_pipe[0] = file_d;
		printf("piping... -> %s\n", h->target);
		if (pipe(_pipe) < 0)
			perror("[pipe]");
		execve("php", &h->target, p->env);
		exit(0);
	}
	return (res);
}
