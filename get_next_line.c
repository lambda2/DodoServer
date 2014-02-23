/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 19:57:05 by aaubin            #+#    #+#             */
/*   Updated: 2013/12/27 04:16:12 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			ft_add_line(char **line, char **buf, long len)
{
	char		*tmp;
	long		o_len;

	if ( line == NULL )
		line = (char **)ft_memalloc (sizeof(char **));
	o_len = ft_strlen (*line);
	*line = (char *)ft_realloc(*line, o_len,  o_len + len + 1);
	if ( *line )
	{
		(*line)[o_len + len] = '\0';
		ft_strncat (*line, *buf, len);
		tmp = ft_strnew ( sizeof(char*) * BUFF_SIZE );
		if ( tmp )
		{
			ft_strncat(tmp, (*buf) + len + 1, BUFF_SIZE - len - 1);
			free(*buf);
			*buf = tmp;
		}
	}
}

void			ft_loop(int const *fd, char **line, char **buf, long *res)
{
	int			stop;

	stop = 0;
	if ( *buf == NULL )
	{
		*buf = ft_strnew ( sizeof(char*) * BUFF_SIZE );
		*res = read( *fd, *buf, BUFF_SIZE );
	}
	*line = ft_strnew ( sizeof(char*) * BUFF_SIZE );
	while ( *line != NULL && *res == BUFF_SIZE && !stop )
	{
		if ( ft_strchr (*buf, '\n') != 0 )
		{
			ft_add_line (line, buf, ft_strpos(*buf, "\n"));
			stop = 1;
		}
		else
		{
			ft_add_line (line, buf, BUFF_SIZE);
			*res = read( *fd, *buf, BUFF_SIZE );
		}
	}
}

int				get_next_line(int const fd, char ** line)
{
	long		res;
	static char	*courant;
	int			stop;

	if (fd < 0 || line == NULL)
		return (-1);
	stop = 0;
	res = BUFF_SIZE;
	ft_loop (&fd, line, &courant, &res);
	if ( res != BUFF_SIZE && res > 0 )
		ft_add_line (line, &courant, res - 1);
	if ( res <= 0 )
	{
		free(*line);
		free(courant);
		courant = NULL;
		return (res);
	}
	return (1);
}
