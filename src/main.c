/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:22:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/16 00:10:35 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char *argv[], char *env[])
{
	t_pipex	data;

	ft_bzero(&data, sizeof(t_pipex) * 1);
	make_t_pipex(&data, argc, argv, env);
	if (!launch_childs(&data))
		return (debug(DBG("Failed to launch_childs()")), data.exit_code);
	return (data.exit_code);
}

int	main(int argc, char *argv[], char *env[])
{
	int		exit_code;

	if (argc < 2)
	{
		print_correct_pipex_usage();
		return (1);
	}
	exit_code = pipex(argc, argv, env);
	if (exit_code)
	{
		debug(DBG("Failed to pipex()"));
		exit(exit_code);
	}
	return (0);
}
