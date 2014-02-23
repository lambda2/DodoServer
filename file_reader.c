/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 01:58:09 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/23 01:58:15 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dodo.h"

int					file_exists(char *path)
{
	int				res;
	struct stat		*stat_l;

	res = 0;
	stat_l = (struct stat *)ft_memalloc(sizeof(struct stat));
	if (stat_l != NULL)
	{
		res = lstat(path, stat_l);
	}
	if (res != -1)
	{
		if (S_ISDIR(stat_l->st_mode) == 0)
		{
			return (stat_l->st_size);
		}
		return (0);
	}
	else
		return (0);
}

