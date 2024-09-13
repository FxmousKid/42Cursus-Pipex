/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:11:43 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/13 18:34:23 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_command_child(t_pipex *data)
{
	int	fd;

	fd = open_infile(data);
	if (fd < 0)
		return (debug(DBG("Failed to open_infile()")), 0);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdin")), 0);
	if (close(fd) < 0)
		return (debug(DBG("Failed to close infile")), 0);
	if (dup2(data->pipe_fds[1], STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);
	if (close(data->pipe_fds[1]) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);
	data->old_read_fd = data->pipe_fds[0];
	return (1);
}

int	middle_commands_child(t_pipex *data)
{ 	
	if (dup2(data->old_read_fd, STDIN_FILENO) < 0)
		return (perror(""), debug(DBG("Failed to dup2 stdin")), 0);
	if (close(data->old_read_fd) < 0)
		return (debug(DBG("Failed to close pipe_fds[0]")), 0);
	if (dup2(data->pipe_fds[1], STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);
	if (close(data->pipe_fds[1]) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);
	data->old_read_fd = data->pipe_fds[0];
	return (1);
}



int	last_command_child(t_pipex *data)
{
	int	fd;

	fd = open_correct_outfile(data);
	if (fd < 0)
		return (debug(DBG("Failed to open_correct_outfile()")), 0);
	if (dup2(data->old_read_fd, STDIN_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdin")), 0);
	if (close(data->old_read_fd) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);
	if (close(fd) < 0)
		return (debug(DBG("Failed to close fd_out")), 0);
	if (close(data->pipe_fds[1]) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);
	if (close(data->pipe_fds[0]) < 0)
		return (debug(DBG("Failed to close pipe_fds[0]")), 0);
	return (1);
}


int	exec_command(t_pipex *data, char **cmd_args)
{
	if (data->cmd_index == 0)
	{
		if (!first_command_child(data))
			return (debug(DBG("Failed to first_command_child()")), 0);
	}
	else if (data->cmd_index == data->cmd_count - 1)
	{
		if (!last_command_child(data))
			return (debug(DBG("Failed to last_command_child()")), 0);
	}
	else
	{
		if (!middle_commands_child(data))
			return (debug(DBG("Failed to middle_commands_child()")), 0);
	}
	execve(data->current_cmd_path, cmd_args, data->env);
	return (1);	
}
