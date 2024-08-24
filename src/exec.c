/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:11:43 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/24 21:48:22 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

int	handle_first_redirection(t_pipex *data)
{
	if (dup2(data->fd_in, STDIN_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdin")), 0);
	if (dup2(data->new_pipe[1], STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);	
	data->old_pipe[0] = data->new_pipe[0];
	data->old_pipe[1] = data->new_pipe[1];
	return (1);
}

int	handle_pipe_redirection(t_pipex *data)
{
	if (close(data->old_pipe[1]) < 0)
		return (debug(DBG("Failed to close old_pipe[1]")), 0);
	if (dup2(data->old_pipe[0], STDIN_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdin")), 0);
	if (pipe(data->new_pipe) < 0)
		return (debug(DBG("Failed to pipe new_pipe")), 0);
	if (dup2(data->new_pipe[1], STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);
	data->old_pipe[0] = data->new_pipe[0];
	data->old_pipe[1] = data->new_pipe[1];

	
	return (1);
}

int	handle_last_redirection(t_pipex *data)
{
	if (close(data->old_pipe[1]) < 0)
		return (debug(DBG("Failed to close old_pipe[1]")), 0);
	if (dup2(data->old_pipe[0], STDIN_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdin")), 0);
	if (dup2(data->fd_out, STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);
	return (1);
}


int	exec_command(t_pipex *data, char **cmd_args)
{
	if (data->cmd_index == 0)
	{
		if (!handle_first_redirection(data))
			return (debug(DBG("Failed to handle_first_redirection()")), 0);
	}
	else if (data->cmd_index == data->cmd_count - 1)
	{
		if (!handle_last_redirection(data))
			return (debug(DBG("Failed to handle_last_redirection()")), 0);
	}
	else
	{
		if (!handle_pipe_redirection(data))
			return (debug(DBG("Failed to handle_pipe_redirection()")), 0);
	}
	execve(data->current_cmd_path, cmd_args, data->env);
	return (1);	
}
