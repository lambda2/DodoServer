/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 19:57:10 by aaubin            #+#    #+#             */
/*   Updated: 2013/12/06 08:02:00 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# include <fcntl.h>

/*
** The buffer size
*/
# define BUFF_SIZE 1

/*
** Will add [len] first characters of [courant] string to [line],
** and reallocate [line] if necessary.
*/
void	ft_add_line(char **line, char **buf, long len);

/*
** Will process the read (@see 'man 3 read') loop, wich will read to the
** buffer [courant] [BUFF_SIZE] characters, and add them to [line].
*/
void	ft_process_loop(int const *fd, char **line, char **buf, long *res);

/*
** Will return the next line on the given file descriptor.
*/
int	get_next_line(int const fd, char ** line);


#endif /* !GET_NEXT_LINE_H */
