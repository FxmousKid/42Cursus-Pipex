/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:51:24 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/24 21:56:24 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_and_exec(t_pipex *data, char **cmd_args)
{
	int	cmd_idx;
	// int	wstatus;


	cmd_idx = data->cmd_index;
	data->pids[cmd_idx] = fork();
	if (data->pids[cmd_idx] < 0)
		return (debug(DBG("Failed to fork()")), 0);
	
	if (data->pids[cmd_idx] == 0)
		exec_command(data, cmd_args);
	
	//if (data->pids[cmd_idx] > 0)
	//	waitpid(data->pids[cmd_idx], &wstatus, 0);
	return (1);
}

int	launch_childs(t_pipex *data)
{
	char	**cmd_args;
		
	while (data->cmd_index < data->cmd_count)
	{
		cmd_args = ft_split(data->cmds[data->cmd_index], ' ');
		if (!find_path(data, data->env, cmd_args[0]))
			return (stderr_file_error(cmd_args[0], "command not found...\n"),
				free_split(cmd_args), 0);
		if (!fork_and_exec(data, cmd_args))
			return (free_split(cmd_args),
				debug(DBG("Falied to fork_and_exec()")), 0);
		free_split(cmd_args);
		data->cmd_index++;
	}
	
	return (1);
}
