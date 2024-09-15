/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:46:55 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/14 16:39:21 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * find_path - Locates the full executable path for a given command by 
 *			   searching the environment's PATH variable or directly checking
 *			   the command path.
 *
 * @data: A pointer to the t_pipex main struct.
 * @env: A pointer to the environment variables, provided by main.
 * @cmd: The command name or relative path to locate.
 *
 * How it works:
 * 1. The function first checks if the provided command (`cmd`) can be 
 *	  executed as-is using `access(cmd, X_OK)`.
 *    If it can, the command path is copied to `data->current_cmd_path` 
 *    using `ft_strlcpy()`.
 * 
 * 2. If the command is not directly executable, the function searches 
 *	  for the PATH environment variable by iterating through the 
 *	  `env` array and matching against "PATH=".
 * 
 * 3. Once the PATH is found, it extracts each directory in the 
 *	  PATH (separated by ':') and constructs a full path by concatenating 
 *	  the directory, a "/", and the command.
 *	  This is done using `ft_strlcpy()` and `ft_strlcat()`.
 * 
 * 4. For each constructed path, `access()` is called again to check if the
 *	  command can be executed from that path.
 * 
 * 5. If no valid path is found, or the PATH variable is missing, the
 *    function returns 0 and logs an error.
 * 
 * Return:
 * - 1 if a valid path is found.
 * - 0 if no valid path is found, or if the PATH variable is absent.
 */

int	find_path(t_pipex *data, char **env, char *cmd)
{
	char	*tmp;
	int		len_till_colon;

	if (access(cmd, X_OK) == 0)
		return (ft_strlcpy(data->current_cmd_path, cmd, 4096), 1);
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (debug(DBG("Error : Path not found ")), 0);
	tmp = *env + ft_strlen("PATH=");
	while (tmp)
	{
		len_till_colon = ft_strlen_till_char(tmp, ':');
		if (!len_till_colon)
			break;
		tmp[len_till_colon] = 0;
		ft_strlcpy(data->current_cmd_path, tmp, 4096);
		ft_strlcat(data->current_cmd_path, "/", 4096);
		ft_strlcat(data->current_cmd_path, cmd, 4096);
		if (access(data->current_cmd_path, X_OK) == 0)
			return (1);
		tmp += len_till_colon + 1;
	}
	return (debug(DBG("Full path not found in command")), 0);
}

// int	find_path(t_pipex *data, char **env, char *cmd)
// {
// 	char	*tmp;

// 	if (access(cmd, X_OK) == 0)
// 		return (ft_strlcpy(data->current_cmd_path, cmd, 4096), 1);
// 	while (*env && ft_strncmp(*env, "PATH=", 5))
// 		env++;
// 	if (!*env)
// 		return (debug(DBG("Error : Path not found ")), 0);
// 	tmp = *env + ft_strlen("PATH=");
// 	while (tmp)
// 	{
// 		ft_strlcpy(data->current_cmd_path, tmp, 
// 			 ft_strlen_till_char(tmp, ':') + 1);
// 		ft_strlcat(data->current_cmd_path, "/", 4096);
// 		ft_strlcat(data->current_cmd_path, cmd, 4096);
// 		if (access(data->current_cmd_path, X_OK) == 0)
// 			return (1);
// 		tmp = ft_strchr(tmp, ':') + 1;
// 		if ((uintptr_t) tmp == 1)
// 			return (debug(DBG("Full path not found in command")), 0);
// 	}
// 	return (0);
// }
