/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:22:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/12 19:28:37 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

int	pipex(int argc, char *argv[], char *env[])
{
	t_pipex	data;
	pid_t	pids[1024];

	ft_bzero(&data, sizeof(t_pipex) * 1);
	ft_bzero(&pids, sizeof(pid_t) * 1024);
	data.pids = pids;
	make_t_pipex(&data, argc, argv, env);
	display_pipex_t(&data);
	ft_printf("\n\n\n");
	if (!launch_childs(&data))
		return (debug(DBG("Failed to launch_childs()")), 0);
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc < 2)
	{
		print_correct_usage();
		return (1);
	}
	if (!pipex(argc, argv, env))
	{
		debug(DBG("Failed to pipex()"));
		return (1);
	}
	return (0);
}
