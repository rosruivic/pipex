/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:28:04 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/27 19:18:42 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_cmd1_exec(t_pipex *d, char **envp)
{
	d->pid_1 = fork();
	if (d->pid_1 == -1)
		ft_errors(ERROR_PID_1, d);
	if (d->pid_1 == 0)
	{
		dup2(d->fd_infile, STDIN_FILENO);
		dup2(d->fd[1], STDOUT_FILENO);
		close(d->fd[0]);
		close(d->fd[1]);
		execve(d->path_cmd_1, d->cmd_1_argmts, envp);
		ft_errors(ERROR_CMD_1_NOT_EXISTS, d);
	}
	free(d->path_cmd_1);
	d->path_cmd_1 = NULL;
	ft_freedom(d->cmd_1_argmts);
	d->cmd_1_argmts = NULL;
}

static void	ft_cmd2_exec(t_pipex *d, char **envp)
{
	d->pid_2 = fork();
	if (d->pid_2 == -1)
		ft_errors(ERROR_PID_2, d);
	if (d->pid_2 == 0)
	{
		dup2(d->fd[0], STDIN_FILENO);
		dup2(d->fd_outfile, STDOUT_FILENO);
		close(d->fd[0]);
		close(d->fd[1]);
		execve(d->path_cmd_2, d->cmd_2_argmts, envp);
		ft_errors(ERROR_CMD_2_NOT_EXISTS, d);
	}
	free(d->path_cmd_2);
	d->path_cmd_2 = NULL;
	ft_freedom(d->cmd_2_argmts);
	d->cmd_2_argmts = NULL;
}

int	ft_forks(t_pipex *d, char **envp)
{
	int			exit_code;

	ft_cmd1_exec(d, envp);
	ft_cmd2_exec(d, envp);
	close(d->fd[0]);
	close(d->fd[1]);
	waitpid(d->pid_1, NULL, 0);
	waitpid(d->pid_2, &exit_code, 0);
	return (WEXITSTATUS(exit_code));
}
