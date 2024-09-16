/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_t_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/16 17:37:49 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	set_heredoc_status_or_infile(t_pipex *data, char *argv[])
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) != 0)
	{
		data->has_here_doc = 0;
		data->infile_path = argv[1];
	}
	else
	{
		data->has_here_doc = 1;
		data->limiter = argv[2];
		data->infile_path = NULL;
	}
	return (1);
}

void	make_t_pipex(t_pipex *data, int argc, char *argv[], char *env[])
{
	set_heredoc_status_or_infile(data, argv);
	ft_memset(data->old_read_fds, -1, sizeof(int) * 1024);
	ft_bzero(data->current_cmd_path, sizeof(char) * 4096);
	ft_bzero(data->pids, sizeof(pid_t) * 1024);
	ft_bzero(data->pipe_fds, sizeof(int) * 2);
	data->outfile_path = argv[argc - 1];
	data->env = env;
	data->cmds = argv + 2 + data->has_here_doc;
	data->cmds[argc - 3 - data->has_here_doc] = 0;
	data->cmd_count = argc - 3 - data->has_here_doc;
	data->cmd_index = 0;
	data->exit_code = 0;
}
