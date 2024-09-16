/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_childs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:51:24 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/16 18:20:41 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_fork(t_pipex *data, char **cmd_args)
{
	int	cmd_idx;

	cmd_idx = data->cmd_index;
	if (data->pids[cmd_idx] < 0)
		return (debug(DBG("Failed to fork()")), 0);
	else if (data->pids[cmd_idx] == 0)
	{
		if (!exec_command(data, cmd_args))
			return (debug(DBG("Failed to exec_command()")), 0);
	}
	else if (data->pids[cmd_idx] > 0)
	{
		if (cmd_idx == 0 && data->has_here_doc)
			waitpid(data->pids[cmd_idx], NULL, 0);
		if (!close_pipe_ends(data))
			return (debug(DBG("Failed to close_pipe_ends()")), 0);
	}
	return (1);
}

int	fork_and_exec(t_pipex *data, char **cmd_args)
{
	int	cmd_idx;

	if (pipe(data->pipe_fds) < 0)
		return (debug(DBG("Failed to pipe()")), 0);
	cmd_idx = data->cmd_index;
	if (!dup_close_old_read_fds(data))
		return (debug(DBG("Failed to dup_close_old_read_fds()")), 0);
	data->pids[cmd_idx] = fork();
	if (!handle_fork(data, cmd_args))
		return (debug(DBG("Failed to handle_fork()")), 0);
	return (1);
}

/* loop_on_commands() - Loops on all the comands, and executes each one of them
 *
 * @data: the pointer to the main t_pipex structure
 *
 * How it works :
 *
 * 1. Loop on all the commands
 *
 * 2. split the string : turns "wc -l --uniq" into {"wc", "-l" "uniq"} and
 *	  pass the result to fork_and_exec() to execute
 *
 * 3. We free the allocated arrays, and increment the command count.
 * */

int	loop_on_commands(t_pipex *data)
{
	char	**cmd_args;

	while (data->cmd_index < data->cmd_count)
	{
		cmd_args = ft_split(data->cmds[data->cmd_index], ' ');
		if (!cmd_args)
			return (debug(DBG("Failed to split command")), 0);
		if (!fork_and_exec(data, cmd_args))
			return (debug(DBG("Failed to fork_and_exec()")),
				free_split(cmd_args), 0);
		free_split(cmd_args);
		data->cmd_index++;
	}
	return (1);
}

int	waitpid_loop(t_pipex *data)
{
	int	pid_index;
	int	status;

	pid_index = 0;
	while (pid_index < data->cmd_count)
	{
		waitpid(data->pids[pid_index], &status, 0);
		if (WIFEXITED(status) && data->cmd_index == data->cmd_count)
			data->exit_code = WEXITSTATUS(status);
		else
		{
			debug(DBG("Failed to WIFEXITED(status)"));
			return (0);
		}
		pid_index++;
	}
	return (1);
}

/* launch_childs() - Loops on all commands and executes them in a child, then 
 *					 waitpid() on the commands individually to retrieve the
 *					 first non-zero exit code
 *
 * @data: A pointer to the t_pipex main struct
 *  
 * How it works :
 * 1. Calls the loop_on_commands() function and verify it's return value
 * 
 * 2. Loops on the commands and waitpid() them individually, then checks the
 *	  return of WIFEXITED(status) to see if the program exited normally, and if
 *	  if did, then we check the exit code with WEXITSTATUS(status)
 */

int	launch_childs(t_pipex *data)
{
	if (!loop_on_commands(data))
	{
		debug(DBG("Failed to loop_on_commands()"));
		if (!close_old_read_fds(data))
			debug(DBG("Failed to close_old_read_fds()"));
		exit(data->exit_code);
	}
	if (!waitpid_loop(data))
		return (debug(DBG("Failed to waitpid_loop()")), 0);
	if (!close_old_read_fds(data))
		return (debug(DBG("Failed to close_old_read_fds()")), 0);
	return (1);
}
