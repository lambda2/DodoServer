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
	//r->content_l = n_size;
}

static void				p_response_headers(t_http_response *r, int s)
{
	add_data("HTTP/1.1 ", r);
	add_data(ft_strjoin(ft_itoa(r->status), H_SEP), r);
	if (r->status == 200)
		add_data(ft_strjoin(STAT_200, H_EOL), r);
	else
		add_data(ft_strjoin(STAT_OTH, H_EOL), r);

	add_data(ft_strjoin("Server:", H_SEP), r);
	add_data(ft_strjoin(r->server, H_EOL), r);

	add_data(ft_strjoin("X-Powered-By:", H_SEP), r);
	add_data(ft_strjoin(r->x_pow_by, H_EOL), r);

	add_data(ft_strjoin("Content-Type: text/html; charset=UTF-8", H_EOL), r);

	add_data(ft_strjoin("Connection:", H_SEP), r);
	add_data(ft_strjoin(r->connexion, H_EOL), r);

	add_data(ft_strjoin("Content-language:", H_SEP), r);
	add_data(ft_strjoin(r->content_lang, H_EOL), r);

	add_data(ft_strjoin("Accept-Ranges:", H_SEP), r);
	add_data(ft_strjoin(r->accept_range, H_EOL), r);

	/*add_data(ft_strjoin("Content-Length:", H_SEP), r);
	add_data(ft_strjoin(ft_itoa(r->content_l + 500), H_EOL), r);*/

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

	buffer = NULL;
	r = create_response(h);
	size = file_exists(h->target);
	if (size)
	{
		r->content_l = size;


		p_response_headers(r, clisock);
		treat_request(h, get_ddp(), clisock);

/*
		file_fd = open(h->target, O_RDONLY);
		if (file_fd > 0)
		{
			p_response_headers(r, clisock);
			treat_request(h, get_ddp(), clisock);
			while (get_next_line(file_fd, &buffer))
			{

				printf(">>>\t\t%s\n", buffer);
				write(clisock, ft_strjoin(buffer, "\n"), ft_strlen(buffer) + 1);
			}
		}
		else
			perror("[open requested file]");
*/
	}
	else
	{
		r->status = 404;
		p_response_headers(r, clisock);
	}

}
