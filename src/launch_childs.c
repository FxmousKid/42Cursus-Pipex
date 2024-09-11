/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:51:24 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/12 01:44:59 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <unistd.h>

int	handle_heredoc_parsing(t_pipex *data)
{
	data->has_here_doc = 0;
	return (1);
}

int	fork_and_exec(t_pipex *data, char **cmd_args)
{
	int	cmd_idx;

	if (pipe(data->pipe_fds) < 0)
		return (debug(DBG("Failed to pipe()")), 0);
	cmd_idx = data->cmd_index;
	if (data->has_here_doc && !handle_heredoc_parsing(data))
		return (debug(DBG("Failed to handle_heredoc_parsing()")), 0);
	data->pids[cmd_idx] = fork();
	if (data->pids[cmd_idx] < 0)
		return (debug(DBG("Failed to fork()")), 0);	
	else if (data->pids[cmd_idx] == 0)
		exec_command(data, cmd_args);
	return (1);
}

int	loop_on_commands(t_pipex *data)
{
	char	**cmd_args;

	while (data->cmd_index < data->cmd_count)
	{
		cmd_args = ft_split(data->cmds[data->cmd_index], ' ');
		if (!cmd_args)
			return (debug(DBG("Failed to split command")), 0);
		if (!find_path(data, data->env, cmd_args[0]))	
			return (stderr_file_error(cmd_args[0], "command not found...\n"),
				free_split(cmd_args), 0);
		if (!fork_and_exec(data, cmd_args))
			return (debug(DBG("Failed to fork_and_exec()")), 
				free_split(cmd_args), 0);
		free_split(cmd_args);
		free(data->current_cmd_path);
		data->cmd_index++;
	}
	return (1);
}

int	launch_childs(t_pipex *data)
{
	int		pid_index;
		
	if (!loop_on_commands(data))
		return (debug(DBG("Failed to loop_on_commands()")), 0);
	pid_index = 0;
	while (pid_index < data->cmd_count)
	{
		if (data->exit_code == 0)
			waitpid(data->pids[pid_index++], &data->exit_code, 0);
		else
			waitpid(data->pids[pid_index++], NULL, 0);	
	}
	return (1);
}
