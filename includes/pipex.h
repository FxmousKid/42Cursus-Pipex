/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:19:49 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/12 15:41:01 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
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

# define STRINGIFY(x) #x
# define TOSTRING(x) STRINGIFY(x)

# define DBG(reason) reason " at line " \
TOSTRING(__LINE__) " in file " __FILE__ "\n"

typedef struct s_pipex
{
	char *	outfile_path;
	char *	infile_path;
	int		has_here_doc;
	pid_t	*pids;
	int		exit_code;
	char	**cmds;
	int		cmd_count;
	int		cmd_index;
	char	*current_cmd_path;
	char	**env;
	int		pipe_fds[2];
	int		old_read_fd;
}			t_pipex;


// Error management
void	stderr_file_error(char *file, char *text);
void	ft_error(char *str);
void	debug(char *str);
void	free_split(char **tab);
void	print_correct_usage(void);

// Handling allocations
void	make_t_pipex(t_pipex *data, int argc, char *argv[], char *env[]);
void	free_split(char **tab);

// Launching childs and forks
int		launch_childs(t_pipex *data);
int		find_path(t_pipex *data, char **env, char *cmd);
int		exec_command(t_pipex *data, char **cmd_args);

// Handling here_doc
int		handle_heredoc_parsing(t_pipex *data);

// Handling files
int		open_infile(t_pipex *data);
int		open_correct_outfile(t_pipex *data);

// Utils
void	display_pipex_t(t_pipex *data);

#endif
