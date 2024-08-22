/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:51:24 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/22 23:55:36 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	launch_childs(t_pipex *data)
{
	if (!find_path(data, data->env, data->cmds[data->cmd_index]))
		return (stderr_file_error(data->cmds[data->cmd_index],
			"command not found...\n"), 0);



	return (1);
}
