/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:22:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/21 15:38:51 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*make_t_pipex(int argc, char *argv[], char *env[])
{
	t_pipex	*data;
	(void) argv;

	data = (t_pipex *) ft_calloc(sizeof(t_pipex), 1);
	if (!data)
		return (ft_error("Error : Failed to Allocate memory !\n"), NULL); 
	data->pids = (pid_t *) ft_calloc(sizeof(pid_t), argc - 2);
	if (data->pids == NULL)
		return (free_t_pipex(data), NULL);	
	(void) env;
	return (data);
}

int	pipex(int argc, char *argv[], char *env[])
{
	t_pipex	*data;

	data = make_t_pipex(argc, argv, env);
	if (!data)
		return (debug(DBG("Failed to make_t_pipex()")), 0);

	free_t_pipex_and_close(data);
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc != 5)
	{
		// Add invalid_arg_handler();
		printf_clr(RED_TXT, "Invalid arg count !\n");
		print_code_and_exit(1);
	}
	if (!pipex(argc, argv, env))
	{
		// Add error_handler();
		debug(DBG("Failed to run pipex() call"));
		print_code_and_exit(1);
	}
	print_code_and_exit(0);

}
