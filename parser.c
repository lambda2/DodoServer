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

int					treat_request(t_http_head *h, int clisock)
{
	int				status;
	int				file_d;
	int				_pipe[2];
	char				*buffer;

	file_d = open("php.log", O_CREAT, 0777);
	pipe(_pipe);
	if (fork() == 0)
	{
		close(_pipe[0]);
		dup2(_pipe[1], 1);
		dup2(file_d, 2);
		close(file_d);
		close(_pipe[1]);
		execl("/usr/bin/php", "/usr/bin/php", h->target, NULL);
		exit(0);
	}
	else
	{
		wait(&status);
		close(_pipe[1]);
		while (get_next_line(_pipe[0], &buffer))
			ft_putendl_fd(buffer, clisock);
	}
	return (1);
}
