/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_init_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:07:40 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/27 19:16:08 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_cmd_extract(char *cmd1, char *cmd2, t_pipex *d)
{
	d->cmd_1_argmts = NULL;
	d->cmd_2_argmts = NULL;
	d->cmd_1_argmts = ft_split(cmd1, ' ');
	if (d->cmd_1_argmts == NULL)
		ft_errors(ERROR_SPLIT_EXTRACTING_CMD, d);
	d->cmd_2_argmts = ft_split(cmd2, ' ');
	if (d->cmd_2_argmts == NULL)
		ft_errors(ERROR_SPLIT_EXTRACTING_CMD, d);
}

static void	ft_env_path(char **envp, t_pipex *d)
{
	int	i;

	i = -1;
	d->env_path = NULL;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			d->env_path = ft_strchr(envp[i], '/');
	}
}

static void	ft_obtain_cmd_path(t_pipex *d, char *cmd)
{
	char	**folder;
	char	*path;
	int		i;

	i = -1;
	folder = ft_split(d->env_path, ':');
	if (cmd == d->cmd_1)
	{
		while (folder[++i])
		{
			path = NULL;
			d->path_cmd_1 = NULL;
			path = ft_strjoin(folder[i], "/");
			d->path_cmd_1 = ft_strjoin(path, d->cmd_1);
			free(path);
			if (access(d->path_cmd_1, F_OK) == 0)
				break;
			else
			{
				free(d->path_cmd_1);
				d->path_cmd_1 = NULL;
			}
		}
	}
	else if (cmd == d->cmd_2)
	{
		while (folder[++i])
		{
			path = NULL;
			d->path_cmd_2 = NULL;
			path = ft_strjoin(folder[i], "/");
			d->path_cmd_2 = ft_strjoin(path, d->cmd_2);
			free(path);
			if (access(d->path_cmd_2, F_OK) == 0)
				break;
			else
			{
				free(d->path_cmd_2);
				d->path_cmd_2 = NULL;
			}
		}
	}
	ft_freedom(folder);
}

void	ft_init_data(t_pipex *d, char **argv, char **envp)
{
	d->error = NO_ERROR;
	ft_cmd_extract(argv[2], argv[3], d);
	d->cmd_1 = d->cmd_1_argmts[0];
	d->cmd_2 = d->cmd_2_argmts[0];
	ft_env_path(envp, d);
	ft_obtain_cmd_path(d, d->cmd_1);
	ft_obtain_cmd_path(d, d->cmd_2);
	d->fd_infile = open(argv[1], O_RDONLY);
	d->fd_outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (d->fd_infile < 0 || d->fd_outfile < 0)
		ft_errors(ERROR_FILES_FD, d);
}
