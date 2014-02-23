/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 01:31:53 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/23 01:32:01 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dodo.h"
#include "http_head.h"
#include "http_response.h"

t_http_response			*create_response(t_http_head *h)
{
	t_http_response		*r;

	r = (t_http_response *)ft_memalloc(sizeof(t_http_response));
	if (r && h)
	{
		r->age = 0;
		r->accept_range = "bytes";
		r->server = "Dodo";
		r->connexion = h->connexion;
		r->x_pow_by = "Da Amazing Dodo Server. By dodo, for dodo.";
		r->content_lang = "fr";
		r->protocol = h->protocol;
		r->status = 200;
		r->content = ft_strnew(1);
		r->content_l = 1;
	}
	return (r);
}

static void				add_data(char *data, t_http_response *r)
{
	int					n_size;

	n_size = ft_strlen(data) + ft_strlen(r->content);
	r->content = ft_realloc(r->content, ft_strlen(r->content), n_size);
	r->content = ft_strcat(r->content, data);
}

static void				add_line(char *label, char *value, t_http_response *r)
{
	add_data(ft_strjoin(label, H_SEP), r);
	add_data(ft_strjoin(value, H_EOL), r);
}

static void				p_response_headers(t_http_response *r, int s)
{
	add_data("HTTP/1.1 ", r);
	add_data(ft_strjoin(ft_itoa(r->status), H_SEP), r);
	if (r->status == 200)
		add_data(ft_strjoin(STAT_200, H_EOL), r);
	else
		add_data(ft_strjoin(STAT_OTH, H_EOL), r);

	add_line("Server:", r->server, r);
	add_line("X-Powered-By:", r->x_pow_by, r);
	add_line("Content-Type:", "text/html; charset=UTF-8", r);
	add_line("Connection:", r->connexion, r);
	add_line("Content-language:", r->content_lang, r);
	add_line("Accept-Ranges:", r->accept_range, r);
	//add_line("Content-Length:", ft_itoa(r->content_l), r);
	add_data(H_EOF, r);
	printf("\n\n%s", r->content);
	write(s, r->content, ft_strlen(r->content));
	bzero(r->content, ft_strlen(r->content));
}

void						send_response(t_http_head *h, int clisock)
{
	t_http_response		*r;
	int					file_fd;
	int					size;
	char					*buffer;

	r = create_response(h);
	size = file_exists(h->target);
	if (size)
	{
		r->content_l = size;
		file_fd = open(h->target, O_RDONLY);
		if (file_fd > 0)
		{
			p_response_headers(r, clisock);
			treat_request(h, clisock);
		}
		else
			perror("[open requested file]");
	}
	else
	{
		r->status = 404;
		p_response_headers(r, clisock);
		file_fd = open("templates/404.dodo", O_RDONLY);
		while (get_next_line(file_fd, &buffer))
			ft_putendl_fd(buffer, clisock);
	}

}
