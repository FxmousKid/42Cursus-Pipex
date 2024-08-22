/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:19:49 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/22 23:11:19 by inazaria         ###   ########.fr       */
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
	int		fd_in;
	int		fd_out;
	pid_t	*pids;
	char	**cmds;
	int		cmd_count;
	int		cmd_index;
	char	*current_cmd_path;
	char	**env;
}			t_pipex;


// Error management
void	stderr_file_error(char *file, char *text);
void	print_code_and_exit(int code);
void	ft_error(char *str);
void	debug(char *str);

// Handling allocations
t_pipex	*make_t_pipex(int argc, char *argv[], char *env[]);
int		free_t_pipex_and_close(t_pipex *data);
void	free_t_pipex(t_pipex *data);

// Launching childs and forks
int		launch_childs(t_pipex *data);
int		find_path(t_pipex *data, char **env, char *cmd);


#endif
