/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:14:49 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/27 19:16:23 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/wait.h>
//# include <limits.h>

typedef enum e_error
{
	NO_ERROR,
	ERROR_ARGMTS,
	ERROR_INFILE,
	ERROR_OUTFILE,
	ERROR_FILES_FD,
	ERROR_PIPE,
	ERROR_PID_1,
	ERROR_PID_2,
	ERROR_CMD_1_NOT_EXISTS,
	ERROR_CMD_2_NOT_EXISTS,
	ERROR_SPLIT_EXTRACTING_CMD = 20, // be free!
}	t_error;

/**
 * @brief Esta estructura servirá para cuando tengamos
 * 				un número indefinido de comandos (varios pipes) * 
 */
/* typedef struct s_cmd
{
	char	*cmd;
	char	**cmd_and_argmts;
	char	*path_cmd;
	int		pid;
}				t_cmd; */

typedef struct s_pipex
{
	t_error	error;
	int		fd[2];
	char	*cmd_1;
	char	*cmd_2;
	char	**cmd_1_argmts;
	char	**cmd_2_argmts;
	char	*env_path;
	char	*path_cmd_1;
	char	*path_cmd_2;
	int		fd_infile;
	int		fd_outfile;
	int		pid_1;
	int		pid_2;
} 			t_pipex;


/* ***************************************************************** */
/* *********************      FUNCTIONS      *********************** */
/* ***************************************************************** */

void	ft_errors(int error, t_pipex *d);
void	ft_init_data(t_pipex *d, char **argv, char **envp);
int	ft_forks(t_pipex *d, char **envp);
void	ft_free_all(t_pipex *d);

#endif
