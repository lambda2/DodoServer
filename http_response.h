/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_response.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 00:05:09 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/23 00:05:35 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_H
# define HTTP_RESPONSE_H

/*
** --- Example response header
** --- (from page 'http://en.wikipedia.org/wiki/Example.com')
**
** HTTP/1.1 200 OK
** Server: Apache
** X-Powered-By: PHP/5.3.10-1ubuntu3.9+wmf1
** X-Content-Type-Options: nosniff
** Content-language: en
** Vary: Accept-Encoding,Cookie
** X-Vary-Options: Accept-Encoding;list-contains=gzip,Cookie;string-contains=enwikiToken;string-contains=enwikiLoggedOut;string-contains=forceHTTPS;string-contains=enwikiSession;string-contains=centralauth_Token;string-contains=centralauth_Session;string-contains=centralauth_LoggedOut;string-contains=mf_useformat;string-contains=stopMobileRedirect
** Last-Modified: Wed, 19 Feb 2014 13:30:22 GMT
** Content-Encoding: gzip
** Content-Type: text/html; charset=UTF-8
** X-Varnish: 735124220, 2572106829 2570206777, 3877081932
** Via: 1.1 varnish, 1.1 varnish, 1.1 varnish
** Content-Length: 9291
** Accept-Ranges: bytes
** Date: Sun, 23 Feb 2014 00:37:31 GMT
** Age: 4831
** Connection: keep-alive
** X-Cache: cp1067 miss (0), amssq59 hit (7), amssq52 frontend miss (0)
** Cache-Control: private, s-maxage=0, max-age=0, must-revalidate
*/

# define		WRI_H(s, e)		write(s, e, ft_strlen(e))
# define		JN_H(a, b)		ft_strjoin(a, b)
# define		STAT_200			"OK BRO"
# define		STAT_OTH			"DODO DIED. YOUR FAULT. *CLAP CLAP*"
# define		H_SEP			" "
# define		H_EOL			"\n"
# define		H_EOF			"\n"

typedef struct				s_http_response
{
	int						status;
	int						content_l;
	char						*connexion;
	char						*protocol;
	char						*server;
	char						*x_pow_by;
	char						*content_lang;
	char						*vary;
	char						*accept_range;
	int						age;
	char						*content;
}							t_http_response;

void							send_response(t_http_head *h, int clisock);



#endif /* !HTTP_RESPONSE_H */
