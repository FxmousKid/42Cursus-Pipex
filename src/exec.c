/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:11:43 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/16 00:09:20 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_finding_path(t_pipex *data, char **cmd_args)
{
	if (!find_path(data, data->env, cmd_args[0]) && data->infile_path)	
	{
		custom_name_error(cmd_args[0], CMD_NOT_FOUND);
		if (data->cmd_index == data->cmd_count - 1)
			data->exit_code = EXIT_COMMAND_NOT_FOUND;
		return (0);
	}
	return (1);
}

int	first_command_child(t_pipex *data, char **cmd_args)
{
	int	fd;

	if (data->has_here_doc && !handle_heredoc_parsing(data))
		return (debug(DBG("Failed to handle_heredoc_parsing()")), 0);
	else if (!data->has_here_doc)
	{
		fd = open_infile(data);
		if (fd < 0)
			return (debug(DBG("Failed to open_infile()")), 0);
		if (dup2(fd, STDIN_FILENO) < 0)
			return (debug(DBG("Failed to dup2 stdin")), 0);
		if (close(fd) < 0)
			return (debug(DBG("Failed to close infile")), 0);
	}
	if (!handle_finding_path(data, cmd_args))
		return (debug(DBG("Failed to handle_finding_path()")), 0);
	if (dup2(data->pipe_fds[1], STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);
	if (close(data->pipe_fds[1]) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);
	if (close(data->pipe_fds[0]) < 0)
		return (debug(DBG("Failed to close pipe_fds[0]")), 0);
	return (1);
}


int	middle_commands_child(t_pipex *data, char **cmd_args)
{ 	
	if (!handle_finding_path(data, cmd_args))
		return (debug(DBG("Failed to handle_finding_path()")), 0);
	if (dup2(data->old_read_fds[data->cmd_index], STDIN_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdin")), 0);
	if (close(data->old_read_fds[data->cmd_index]) < 0)
		return (debug(DBG("Failed to close pipe_fds[0]")), 0);
	if (dup2(data->pipe_fds[1], STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdout")), 0);
	if (close(data->pipe_fds[1]) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);


	return (1);
}

int	last_command_child(t_pipex *data, char **cmd_args)
{
	int	fd;

	fd = open_correct_outfile(data);
	if (fd < 0)
		return (debug(DBG("Failed to open_correct_outfile()")), 0);
	if (!handle_finding_path(data, cmd_args))
		return (debug(DBG("Failed to handle_finding_path()")), 0);
	if (dup2(data->old_read_fds[data->cmd_index], STDIN_FILENO) < 0)
		return (debug(DBG("Failed to dup2 stdin")), 0);
	if (close(data->old_read_fds[data->cmd_index]) < 0)
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
		if (!first_command_child(data, cmd_args))
			return (debug(DBG("Failed to first_command_child()")), 0);
	}
	else if (data->cmd_index == data->cmd_count - 1)
	{
		if (!last_command_child(data, cmd_args))
			return (debug(DBG("Failed to last_command_child()")), 0);
	}
	else
	{
		if (!middle_commands_child(data, cmd_args))
			return (debug(DBG("Failed to middle_commands_child()")), 0);
	}
	execve(data->current_cmd_path, cmd_args, data->env);
	return (0);	
}
