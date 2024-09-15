/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:29:41 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/15 20:40:02 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	dup_close_old_read_fds(t_pipex *data)
{
	int	cmd_idx;

	cmd_idx = data->cmd_index;
	data->old_read_fds[cmd_idx + 1] = dup(data->pipe_fds[0]);
	if (data->old_read_fds[cmd_idx - 1] < 0)
		return (debug(DBG("Failed to dup(data->pipe_fds[0])")), 0);
	if (cmd_idx > 1)
	{
		if (close(data->old_read_fds[cmd_idx - 1]) < 0)
			return (debug(DBG("Failed to close old_read_fds[cmd_idx - 1]")), 0);
		data->old_read_fds[cmd_idx - 1] = -1;
	}
	return (1);
}
