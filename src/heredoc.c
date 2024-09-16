/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:16:45 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/16 17:33:47 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_heredoc_parsing(t_pipex *data)
{
	char	*limiter;
	char	*line;
	int		write_qty;

	limiter = data->limiter;
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, limiter, ft_strlen(line) - 1) != 0)
	{
		write_qty = write(data->pipe_fds[1], line, ft_strlen(line));
		if (write_qty < 0)
			return (debug(DBG("Failed to write from here_doc")), 0);
		if ((size_t) write_qty != ft_strlen(line))
			return (debug(DBG("Partial write from here_doc")), 0);
		free(line);
		ft_printf("> ");
		line = get_next_line(STDOUT_FILENO);
	}
	free(line);
	if (close(data->pipe_fds[1]) < 0)
		return (debug(DBG("Failed to close pipe_fds[1]")), 0);
	return (1);
}
