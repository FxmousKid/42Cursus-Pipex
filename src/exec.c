/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:11:43 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/11 20:06:35 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <unistd.h>

int	pipe_redirection_child(t_pipex *data)
{
	fprintf(stderr, "exec %s from child number %d\n", data->current_cmd_path, data->cmd_index);
	fflush(stderr);
	if (close(data->pipe_fds[0]) < 0)
		return (debug(DBG("Failed to close pipe_fds[0]")), 0);
	if (dup2(data->pipe_fds[1], STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);
	if (close(data->pipe_fds[1]) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);
	if (close(data->fd_out) < 0)
		return (debug(DBG("Failed to close fd_out")), 0);
	return (1);
}


int	last_redirection_child(t_pipex *data)
{
	fprintf(stderr, "exec %s from child number %d\n", data->current_cmd_path, data->cmd_index);
	fflush(stderr);
	if (close(data->pipe_fds[0]) < 0)
		return (debug(DBG("Failed to close pipe_fds[0]")), 0);
	if (close(data->pipe_fds[1]) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);
	if (dup2(data->fd_out, STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);
	if (close(data->fd_out) < 0)
		return (debug(DBG("Failed to close fd_out")), 0);
	return (1);
}


int	exec_command(t_pipex *data, char **cmd_args)
{
	if (data->cmd_index == data->cmd_count - 1)
	{
		if (!last_redirection_child(data))
			return (debug(DBG("Failed to last_redirection_child()")), 0);
	}
	else
	{
		if (!pipe_redirection_child(data))
			return (debug(DBG("Failed to pipe_redirection_child()")), 0);
	}
	execve(data->current_cmd_path, cmd_args, data->env);
	return (1);	
}
