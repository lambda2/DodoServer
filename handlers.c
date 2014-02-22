/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 03:15:21 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/22 03:15:25 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dodo.h"

void		handlerExit(int sig)
{
	t_ddp	*p;

	p = get_ddp();
	// INTERRUPTION
	close(p->sock);
	exit(0);
}

void		handlerGetOutSon(int sig)
{
	wait(0);
}

int			existOrNot(char* filename)
{
	int		res;
	FILE*	pt_file;

	res = -1;
	if (pt_file = fopen(filename,"rw+"))
	{
		res = 0;
		fclose(pt_file);
	}
	else
	{
		res=1;
	}
	return (res);
}
