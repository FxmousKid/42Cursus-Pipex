/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_t_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/12 17:21:36 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <time.h>
#include <unistd.h>

int	set_heredoc_status(t_pipex *data, char *argv[])
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) != 0)
		data->has_here_doc = 0;
	else
		data->has_here_doc = 1;
	return (1);
}

void display_pipex_t(t_pipex *data)
{
	static int	i = 0;

	ft_printf("\n\n------ PIPEX STRUCTURE ------\n");
	ft_printf("data->has_here_doc: %d\n", data->has_here_doc);
	ft_printf("data->old_read_fd: %d\n", data->old_read_fd);
	ft_printf("data->pipe_fds[0]: %d\n", data->pipe_fds[0]);
	ft_printf("data->pipe_fds[1]: %d\n", data->pipe_fds[1]);
	ft_printf("data->infile_path: %s\n", data->infile_path);
	ft_printf("data->outfile_path: %s\n", data->outfile_path);
	ft_printf("data->env: %s\n", data->env[0]);
	ft_printf("data->pids: [");
	while (i < data->cmd_count - 1)
		ft_printf("%d, ", data->pids[i++]);
	ft_printf("%d]\n", data->pids[i]);
	ft_printf("data->cmds: [");
	i = 0;	
	while (i < data->cmd_count - 1)
		ft_printf("'%s',  ", data->cmds[i++]);
	ft_printf("'%s']\n", data->cmds[i]);
	ft_printf("data->cmd_count: %d\n", data->cmd_count);
	ft_printf("data->cmd_index: %d\n", data->cmd_index);
	ft_printf("data->current_cmd_path: %s\n", data->current_cmd_path);
	ft_printf("data->exit_code: %d\n", data->exit_code);
	ft_printf("------ PIPEX STRUCTURE ------\n\n");
}

void	make_t_pipex(t_pipex *data, int argc, char *argv[], char *env[])
{
	set_heredoc_status(data, argv);
	data->old_read_fd = -1;
	data->infile_path = argv[1];
	data->outfile_path = argv[argc - 1];
	data->env = env;
	data->cmds = argv + 2;
	data->cmds[argc - 3] = 0;
	data->cmd_count = argc - 3;
	data->cmd_index = 0;
	data->current_cmd_path = NULL;
	data->exit_code = 0;
}
