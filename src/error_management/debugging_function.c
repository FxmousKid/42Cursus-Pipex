/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:22:11 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/16 17:35:48 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Function used to debug errors flow, will only trigger when building 
 * project with 'make debug'*/
#ifdef DEBUG

void	debug(char *str)
{
	write(2, RED_TXT, 7);
	write(2, str, ft_strlen(str));
	write(2, END_TXT, 4);
}

#else

void	debug(char *str)
{
	(void) str;
}
#endif

static void	display_pipex_t_utils(t_pipex *data)
{
	int	i;

	ft_printf("\n\n==%d== ------ PIPEX STRUCTURE ------\n", getpid());
	ft_printf("==%d== data->has_here_doc: %d\n", getpid(), data->has_here_doc);
	ft_printf("==%d== data->limiter: %s\n", getpid(), data->limiter);
	ft_printf("==%d== data->old_read_fds: [", getpid());
	i = 0;
	while (i < data->cmd_count)
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
