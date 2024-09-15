/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_t_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:30:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/15 23:50:51 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

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
		data->infile_path =	NULL;
	}
	return (1);
}

static void	display_pipex_t_utils(t_pipex *data)
{
	int	i;

	ft_printf("\n\n==%d== ------ PIPEX STRUCTURE ------\n", getpid());
	ft_printf("==%d== data->has_here_doc: %d\n", getpid(), data->has_here_doc);
	ft_printf("==%d== data->limiter: %s\n", getpid(), data->limiter);
	ft_printf("==%d== data->old_read_fds: [", getpid());
	i = 0;
	while (i < data->cmd_count - 1)
		ft_printf("%d, ", data->old_read_fds[i++]);
	ft_printf("%d]\n", data->old_read_fds[i]);
	ft_printf("==%d== data->pipe_fds[0]: %d\n", getpid(), data->pipe_fds[0]);
	ft_printf("==%d== data->pipe_fds[1]: %d\n", getpid(), data->pipe_fds[1]);
	ft_printf("==%d== data->infile_path: %s\n", getpid(), data->infile_path);
	ft_printf("==%d== data->outfile_path: %s\n", getpid(), data->outfile_path);
	ft_printf("==%d== data->env: %s\n", getpid(), data->env[0]);
	ft_printf("==%d== data->pids: [", getpid());	
}

void	display_pipex_t(t_pipex *data)
{
	int	i;

	display_pipex_t_utils(data);
	i = 0;
	while (i < data->cmd_count - 1)
		ft_printf("%d, ", data->pids[i++]);
	ft_printf("%d]\n", data->pids[i]);
	ft_printf("==%d== data->cmds: [", getpid());
	i = 0;	
	while (i < data->cmd_count - 1)
		ft_printf("'%s',  ", data->cmds[i++]);
	ft_printf("'%s']\n", data->cmds[i]);
	ft_printf("==%d== data->cmd_count: %d\n", getpid(), data->cmd_count);
	ft_printf("==%d== data->cmd_index: %d\n", getpid(), data->cmd_index);
	ft_printf("==%d== data->current_cmd_path: %s\n", getpid(), \
		data->current_cmd_path);
	ft_printf("==%d== data->exit_code: %d\n", getpid(), data->exit_code);
	ft_printf("==%d== ------ PIPEX STRUCTURE ------\n\n", getpid());
}

void	make_t_pipex(t_pipex *data, int argc, char *argv[], char *env[])
{
	set_heredoc_status_or_infile(data, argv);
	ft_bzero(data->old_read_fds, sizeof(int) * 1024);
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
