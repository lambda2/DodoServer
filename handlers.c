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
	(void)sig;
	close(p->sock);
	exit(0);
}

void		handlerGetOutSon(int sig)
{
	(void)sig;
	wait(0);
}
