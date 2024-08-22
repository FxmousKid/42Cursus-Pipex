/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:22:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/22 23:06:24 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char *argv[], char *env[])
{
	t_pipex	*data;

	data = make_t_pipex(argc, argv, env);
	if (!data)
		return (debug(DBG("Failed to make_t_pipex()")), 0);	
	if (!launch_childs(data))
		return (debug(DBG("Failed to launch_childs()")),
			free_t_pipex_and_close(data), 0);


	free_t_pipex_and_close(data);
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc != 5)
	{
		printf_clr(RED_TXT, "Invalid arg count !\n");
		print_code_and_exit(1);
	}
	if (!pipex(argc, argv, env))
	{
		debug(DBG("Failed to run pipex() call"));
		print_code_and_exit(1);
	}
	print_code_and_exit(0);
}
