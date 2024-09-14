/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:22:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/14 02:28:28 by inazaria         ###   ########.fr       */
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
	if (!launch_childs(&data))
		return (debug(DBG("Failed to launch_childs()")), 0);
	return (data.exit_code);
}

int	main(int argc, char *argv[], char *env[])
{
	int		exit_code;

	if (argc < 2)
	{
		print_correct_usage();
		return (1);
	}
	exit_code = pipex(argc, argv, env);
	if (!exit_code)
	{
		debug(DBG("Failed to pipex()"));
		return (1);
	}
	return (exit_code);
}
