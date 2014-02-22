/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dodo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 03:14:00 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/22 03:14:26 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DODO_H
# define DODO_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>

# include "libft.h"

# define BUF_SIZE	8192 /* Ca devrait etre assez pour faire un header HTTP */

typedef struct sockaddr_in	skad;
typedef struct sockaddr		ska;

typedef struct		s_ddp
{
	int				sock;
	skad			sockaddr;
	int				in_loop;
}					t_ddp;

typedef struct		s_http
{
	char			request[32];
	char			target[64];
	char			protocol[16];
}					t_http;


t_ddp				*get_ddp(void);
int					launch_server(void);
int					dds_loop(t_ddp *p);
void				dds_listen(t_ddp *p);

void				handlerExit(int sig);
void				handlerGetOutSon(int sig);
int					existOrNot(char* filename);

#endif /* DODO_H */
