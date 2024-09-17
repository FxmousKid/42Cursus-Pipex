/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:19:49 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/17 02:15:45 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/wait.h>

# define RED_TXT		"\e[0;31m"
# define GREEN_TXT		"\e[0;32m"
# define YELLOW_TXT		"\e[0;33m"
# define BLUE_TXT		"\e[0;34m"
# define PURPLE_TXT		"\e[0;35m"
# define CYAN_TXT		"\e[0;36m"
# define GREY_TXT		"\e[0;37m"
# define WHITE_TXT		"\e[0;39m"
# define BOLD_TXT		"\e[1m"
# define UNDERLINE_TXT	"\e[4m"
# define REVERSE_TXT	"\e[7m"
# define HIDDEN_TXT		"\e[8m"
# define END_TXT		"\e[0m"

# define CMD_NOT_FOUND "command not found...\n"
# define FILE_NOT_FOUND "No such file or directory\n"

# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_PERMISSION_ERROR 1

# define STRINGIFY(x) #x
# define TOSTRING(x) STRINGIFY(x)

# define DBG(reason) reason " at line " \
TOSTRING(__LINE__) " in file " __FILE__ "\n"

typedef struct s_pipex
{
	int		has_here_doc;
	char	*limiter;
	char	*outfile_path;
	char	*infile_path;
	int		old_read_fds[1024];
	int		pipe_fds[2];
	pid_t	pids[1024];
	int		exit_code;
	char	**cmds;
	int		cmd_count;
	int		cmd_index;
	char	current_cmd_path[4096];
	char	**env;
}			t_pipex;

// Error management
void	custom_name_error(char *file, char *text);
void	custom_name_perror(char *file);
void	print_correct_pipex_usage(void);
void	free_split(char **tab);
void	debug(char *str);

// Handling allocations
void	make_t_pipex(t_pipex *data, int argc, char *argv[], char *env[]);
void	free_split(char **tab);

// Launching childs and forks
int		launch_childs(t_pipex *data);
int		find_path(t_pipex *data, char **env, char *cmd);
int		exec_command(t_pipex *data, char **cmd_args);

// Handling here_doc
int		handle_heredoc_parsing(t_pipex *data);

// Handling files and file descriptors
int		open_infile(t_pipex *data);
int		open_correct_outfile(t_pipex *data);
int		close_old_read_fds(t_pipex *data);
int		close_pipe_ends(t_pipex *data);
int		dup_close_old_read_fds(t_pipex *data);

// Utils
void	display_pipex_t(t_pipex *data);

#endif
