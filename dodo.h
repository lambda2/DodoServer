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
# include <sys/stat.h>
# include <sys/wait.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>

# include "libft/includes/libft.h"
# include "get_next_line.h"
# include "http_head.h"

# define BUF_SIZE	8192 /* Ca devrait etre assez pour faire un header HTTP */

typedef struct sockaddr_in	skad;
typedef struct sockaddr		ska;

typedef struct		s_ddp
{
	int				sock;
	skad				sockaddr;
	int				in_loop;
	char				**av;
	char				**env;
	int				ac;
}					t_ddp;


t_ddp				*get_ddp(void);
int					launch_server(int ac, char **av, char **env);
int					dds_loop(t_ddp *p);
void					dds_listen(t_ddp *p);

void					handlerExit(int sig);
void					handlerGetOutSon(int sig);

/*
** Reader related functions
*/
int					file_exists(char *path);

/*
** parser
*/
int					treat_request(t_http_head *h, t_ddp *p, int clisock);

#endif /* DODO_H */
