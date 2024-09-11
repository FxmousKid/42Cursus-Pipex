/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:18:21 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/11 23:19:39 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_correct_outfile(t_pipex *data)
{
	int	fd;

	if (data->has_here_doc)
		fd = open(data->outfile_path, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(data->outfile_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(2, data->outfile_path, ft_strlen(data->outfile_path));
		write(2, ": ", 2);
		write(2, "\e[0;31m", 7);
		perror("");
		write(2, "\e[0m", 4);
		return (0);
	}
	return (fd);

}

int	open_infile(t_pipex *data)
{
	int	fd;

	fd = open(data->infile_path, O_RDONLY);
	if (fd < 0)
	{
		write(2, data->infile_path, ft_strlen(data->infile_path));
		write(2, ": ", 2);
		write(2, "\e[0;31m", 7);
		perror("");
		write(2, "\e[0m", 4);
		return (0);
	}
	return (fd);	
}
