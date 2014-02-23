/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_head.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 00:05:09 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/23 00:05:35 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_HEAD_H
# define HTTP_HEAD_H

/*
** --- Simple HTTP request headers ---
** GET / HTTP/1.1
** Host: localhost:1234
** Connection: keep-alive
** Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,
		*//*;q=0.8
** User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_8_5) AppleWebKit/537.36
		(KHTML, like Gecko) Chrome/33.0.1750.117 Safari/537.36
** Accept-Encoding: gzip,deflate,sdch
** Accept-Language: en-US,en;q=0.8,fr;q=0.6
*/

# define		GET_				"GET "
# define		POST_			"POST "
# define		PUT_				"PUT "
# define		DELETE_			"DELETE "
# define		HOST_			"Host: "
# define		CONN_			"Connection: "
# define		ACC_				"Accept: "
# define		US_AG_			"User-Agent: "
# define		ACC_ENC_			"Accept-Encoding: "
# define		ACC_LANG_		"Accept-Language: "

# define		DDS_HSUB(L, R)	filter(ft_strsub(L, ft_strlen(R), ft_strlen(L) - ft_strlen(R)))

typedef enum					e_request
{
	GET,
	POST,
	PUT,
	DELETE,
	OPTIONS,
	HEAD,
	TRACE,
	CONNECT,
	PATCH,
	UNKNOWN
}							t_request;

typedef struct				s_http_head
{
	t_request				type;
	char						*target;
	char						*protocol;
	char						*host;
	char						*connexion;
	char						*accept;
	char						*user_agent;
	char						*accept_enc;
	char						*accept_lang;
}							t_http_head;

t_http_head			*parse_http_header(int fd);


#endif /* !HTTP_HEAD_H */
