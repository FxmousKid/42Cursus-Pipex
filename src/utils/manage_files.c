/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:18:21 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/17 02:20:16 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(t_pipex *data)
{
	int	fd;

	if (access(data->infile_path, R_OK) < 0)
	{
		custom_name_perror(data->infile_path);
		debug(DBG("Failed to access"));
		return (-1);
	}
	fd = open(data->infile_path, O_RDONLY);
	if (fd < 0)
	{
		custom_name_perror(data->infile_path);
		debug(DBG("Failed to open"));
		return (-1);
	}
	return (fd);
}

int	open_correct_outfile(t_pipex *data)
{
	int	fd;

	if (access(data->outfile_path, W_OK) < 0)
	{
		if (access(".", W_OK) < 0)
		{
			custom_name_perror(data->outfile_path);
			data->exit_code = EXIT_PERMISSION_ERROR;
			return (debug(DBG("Failed to access directory")), -1);
		}
	}
	if (data->has_here_doc)
		fd = open(data->outfile_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(data->outfile_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		custom_name_perror(data->outfile_path);
		data->exit_code = EXIT_PERMISSION_ERROR;
		return (debug(DBG("Failed to open")), -1);
	}
	return (fd);
}
