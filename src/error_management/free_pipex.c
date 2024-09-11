/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:58:22 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/11 16:23:28 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

void	free_split(char **tab)
{
	int	idx;

	idx = 0;
	while (tab[idx])
	{
		free(tab[idx]);
		idx++;
	}
	free(tab);
}

void	free_t_pipex(t_pipex *data)
{
	free(data->pids);
	free(data);
}

int	free_t_pipex_and_close(t_pipex *data)
{
	int	rstatus;

	rstatus = 1;
	if (data->fd_out > 0 && close(data->fd_out) < 0)
	{
		rstatus = 0;
		debug(DBG("Failed to close fd_out"));
	}
	free_t_pipex(data);
	return (rstatus);
}
