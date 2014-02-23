/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 00:00:10 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/23 00:00:25 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dodo.h"
#include "http_head.h"

static int			hmatch(char *line, char *field)
{
	return (ft_strnequ(line, field, ft_strlen(field)));
}

static void			parse_request(char *r, t_http_head *h)
{
	char				**spli;

	spli = ft_strsplit(r, ' ');
	if (spli)
	{
		if (hmatch(r, GET_))
			h->type = GET;
		else if (hmatch(r, POST_))
			h->type = POST;
		else if (hmatch(r, PUT_))
			h->type = PUT;
		else if (hmatch(r, DELETE_))
			h->type = DELETE;
		else
			h->type = UNKNOWN;
		if (spli[1])
			h->target = spli[1];
		if (spli[2])
			h->protocol = spli[2];
	}
}

static char			*filter(char *e)
{
	int				ct;

	ct = 0;
	while (ct < (int)ft_strlen(e))
	{
		if (e[ct] == '\n' || e[ct] == '\r')
		{
			e[ct] = '\0';
		}
		ct++;
	}
	return (e);
}

static void			compute_info(char *l, t_http_head *h)
{

	if (hmatch(l, GET_) || hmatch(l, POST_) || hmatch(l, PUT_)
			|| hmatch(l, DELETE_))
		parse_request(l, h);
	else if (hmatch(l, HOST_))
		h->host = DDS_HSUB(l, HOST_);
	else if (hmatch(l, CONN_))
		h->connexion = DDS_HSUB(l, CONN_);
	else if (hmatch(l, ACC_))
		h->accept = DDS_HSUB(l, ACC_);
	else if (hmatch(l, US_AG_))
		h->user_agent = DDS_HSUB(l, US_AG_);
	else if (hmatch(l, ACC_ENC_))
		h->accept_enc = DDS_HSUB(l, ACC_ENC_);
	else if (hmatch(l, ACC_LANG_))
		h->accept_lang = DDS_HSUB(l, ACC_LANG_);
}

t_http_head			*parse_http_header(int fd)
{
	t_http_head		*h;
	char				*line;
	int				out;

	h = NULL;
	out = 1;
	line = NULL;
	if (fd)
	{
		h = (t_http_head *)ft_memalloc(sizeof(t_http_head));
		if (h)
		{
			while (get_next_line(fd, &line) && out)
			{
				compute_info(line, h);
				printf("<<<\t\t[%s]\n", line);
				if (line && line[0] == '\r')
				{
					out = 0;
					break;
				}
			}
			printf("Header sucessfully parsed ! [request: %s]\n", h->target);
		}
	}
	return (h);
}
