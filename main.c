/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 03:11:28 by aaubin            #+#    #+#             */
/*   Updated: 2014/02/22 03:11:33 by aaubin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dodo.h"

int main(int ac, char **av, char **env)
{
	/*
	return (launch_server(ac, av, env));
	*/
	pid_t			father;
	int				status;
	int				res;
	char				*exe = "index.dodo";
	int				file_d;
	int				_pipe[2];

	res = 0;
	file_d = open("php.log", O_CREAT, 0777);
	/*father = fork();
	if (father > 0)
		wait(&status);
	else if (father == 0)
	{

		dup2(file_d, 1);   // make stdout go to file
		dup2(file_d, 2);   // make stderr go to file - you may choose to not do this
		// or perhaps send stderr to another file

		close(file_d);     // fd no longer needed - the dup'ed handles are sufficient

//		_pipe[1] = 1;
//		_pipe[0] = file_d;
//		printf("piping... -> %s\n", exe);
//		if (pipe(_pipe) < 0)
//			perror("[pipe]");
		execve("/usr/bin/php", av, env);
		exit(0);
	}
*/
	pipe(_pipe);
	if (fork() == 0)
	{
		close(_pipe[0]);    // close reading end in the child

		dup2(_pipe[1], 1);  // send stdout to the pipe
		dup2(_pipe[1], 2);  // send stderr to the pipe

		close(_pipe[1]);    // this descriptor is no longer needed

		execve("/usr/bin/php", av, env);
		exit(0);
	}
	else
	{
		// parent

		wait(&status);
		char *buffer = ft_strnew(1024);

		close(_pipe[1]);  // close the write end of the pipe in the parent

		while (get_next_line(_pipe[0], &buffer))
		{
			write(1, "<><>\t\t", 6);
			ft_putendl(buffer);
		}
	}

	return (res);

}
