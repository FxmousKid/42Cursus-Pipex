/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_t_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/27 17:18:41 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

int	open_correct_outfile(int has_heredoc, char *path)
{
	int	fd;

	if (has_heredoc)
	{
		fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
		return (fd);
	}
	else
	{
		fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
		return (fd);
	}
}

int	open_files(t_pipex *data, int argc, char *argv[])
{
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in < 0)
	{
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": ", 2);
		write(2, "\e[0;31m", 7);
		perror("");
		write(2, "\e[0m", 4);
		return (0);
	} 
	data->fd_out = open_correct_outfile(data->has_here_doc, argv[argc - 1]);
	if (data->fd_out < 0)
	{
		write(2, argv[argc - 1], ft_strlen(argv[argc - 1]));
		write(2, ": ", 2);
		write(2, "\e[0;31m", 7);
		perror("");
		write(2, "\e[0m", 4);
		if (close (data->fd_in) != 0)
			return (debug(DBG("Failed to emergency close infile")), 0);
		return (0);
	}
	return (1);
}

int	set_heredoc_status_or_open_infile(t_pipex *data, int argc, char *argv[])
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) != 0)
	{
		if (!open_files(data, argc, argv))
			return (debug(DBG("Failed to open_files()")), 0);
		data->has_here_doc = 0;
	}
	else
		data->has_here_doc = 1;
	
	return (1);
}

t_pipex	*make_t_pipex(int argc, char *argv[], char *env[])
{
	t_pipex	*data;

	data = (t_pipex *) ft_calloc(sizeof(t_pipex), 1);
	if (!data)
		return (ft_error("Error : Failed to Allocate memory !\n"), NULL); 
	data->pids = (pid_t *) ft_calloc(sizeof(pid_t), argc - 3);
	if (data->pids == NULL)
		return (free_t_pipex(data), 
			debug(DBG("Failed to calloc() data->pids")), NULL);	
	if (!set_heredoc_status_or_open_infile(data, argc, argv))
		return (free_t_pipex(data),
			debug(DBG("Failed to set_heredoc_status_or_open_infile()")), NULL);
	data->env = env;
	data->cmds = argv + 2;
	data->cmds[argc - 3] = 0;
	data->cmd_count = argc - 3;
	data->cmd_index = 0;
	data->current_cmd_path = NULL;
	data->exit_code = 0;
	return (data);
}
