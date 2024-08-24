/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:46:55 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/23 15:47:01 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_path(t_pipex *data, char **env, char *cmd)
{ 
	char	path[4096];
	char	*tmp;

	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (debug(DBG("Error : Path not found ")), 0);
	tmp = *env + ft_strlen("PATH=");
	while (tmp)
	{
		if (access(cmd, X_OK) == 0)
			return (data->current_cmd_path = ft_strdup(cmd), 1);
		bzero(path, sizeof(char) * 4096);
		ft_strlcpy(path, tmp, (uintptr_t)ft_strchr(tmp, ':') + 1 - (uintptr_t) tmp);
		ft_strlcat(path, "/", 4096);
		ft_strlcat(path, cmd, 4096);
		if (access(path, X_OK) == 0)
			return (data->current_cmd_path = ft_strdup(path), 1);
		tmp = ft_strchr(tmp, ':') + 1;
		if ((uintptr_t) tmp == 1)
			return (debug(DBG("Full path not found in command")), 0);
	}
	return (0);
}
