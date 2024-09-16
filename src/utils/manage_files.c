/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:18:21 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/16 18:19:36 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(t_pipex *data)
{
	int	fd;

	fd = open(data->infile_path, O_RDONLY);
	if (fd < 0)
	{
		custom_name_error(data->infile_path, FILE_NOT_FOUND);
		return (0);
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
