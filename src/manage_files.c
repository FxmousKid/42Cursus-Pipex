/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:18:21 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/15 23:35:35 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_pipe_ends(t_pipex *data)
{
	if (close(data->pipe_fds[1]) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);
	if (close(data->pipe_fds[0]) < 0)
		return (debug(DBG("Failed to close pipe_fds[0]")), 0);
	return (1);
}

int	close_old_read_fds(t_pipex *data)
{
	int	idx;
	
	idx = 0;
	if (data->old_read_fds[idx] != -1)
	{
		if (close(data->old_read_fds[idx]) < 0)
		{
			debug(DBG("Failed to close data->old_read_fds[idx]"));
			return (0);
		}
	}
	return (1);
}

int	open_infile(t_pipex *data)
{
	int	fd;

	fd = open(data->infile_path, O_RDONLY);
	if (fd < 0)
	{
		custom_name_error(data->infile_path, FILE_NOT_FOUND);
		fd = open("/dev/null", O_RDONLY);
		if (fd < 0)
		{
			custom_name_error("/dev/null", FILE_NOT_FOUND);
			return (0);
		}
		data->infile_path = NULL;
	}
	return (fd);	
}

int	open_correct_outfile(t_pipex *data)
{
	int	fd;

	if (data->has_here_doc)
		fd = open(data->outfile_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(data->outfile_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		custom_name_error(data->outfile_path, FILE_NOT_FOUND);
		return (0);
	}
	return (fd);
}
