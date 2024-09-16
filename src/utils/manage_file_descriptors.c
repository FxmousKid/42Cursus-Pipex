/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file_descriptors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:29:41 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/16 17:37:00 by inazaria         ###   ########.fr       */
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
	while (idx <= data->cmd_count)
	{
		if (data->old_read_fds[idx] > 0)
		{
			if (close(data->old_read_fds[idx]) < 0)
			{
				debug(DBG("Failed to close data->old_read_fds[idx]"));
				return (0);
			}
			data->old_read_fds[idx] = -3;
		}
		idx++;
	}
	return (1);
}

int	dup_close_old_read_fds(t_pipex *data)
{
	int	cmd_idx;

	cmd_idx = data->cmd_index;
	data->old_read_fds[cmd_idx + 1] = dup(data->pipe_fds[0]);
	if (data->old_read_fds[cmd_idx + 1] < 0)
		return (debug(DBG("Failed to dup(data->pipe_fds[0])")), 0);
	if (cmd_idx > 1)
	{
		if (close(data->old_read_fds[cmd_idx - 1]) < 0)
			return (debug(DBG("Failed to close old_read_fds[cmd_idx - 1]")), 0);
		data->old_read_fds[cmd_idx - 1] = -2;
	}
	return (1);
}
