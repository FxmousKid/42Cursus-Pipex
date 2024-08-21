/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:58:22 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/21 15:37:30 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_t_pipex(t_pipex *data)
{
	free(data->pids);	
	free(data);
}

int	free_t_pipex_and_close(t_pipex *data)
{
	if (close(data->fd_in) != 0)
		return (ft_error("Failed to close infile !\n"), 0);
	if (close(data->fd_out) != 0)
		return (ft_error("Failed to close outfile !\n"), 0);
	free_t_pipex(data);
	return (1);
}
