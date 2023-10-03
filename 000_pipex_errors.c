/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_pipex_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:09:18 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/26 20:34:46 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_less_20(int error, t_pipex *d)
{
	(void)d;
	
	if (error == ERROR_ARGMTS)
		perror("Error\n   --- Format expected: ./pipex file1 cmd1 cmd2 file2\n");
	if (error == ERROR_INFILE)
		perror("Error\n   --- Source file can't be open or read\n");
	if (error == ERROR_OUTFILE)
		perror("Error\n   --- Destiny file can't be written\n");
	if (error == ERROR_FILES_FD)
		perror("Error\n   --- File descriptor (infile / outfile) failure");
	if (error == ERROR_PIPE)
		perror("Error\n   --- Pipe failure\n");
	if (error == ERROR_PID_1)
		perror("Error\n   --- PID 1 failure\n");
	if (error == ERROR_PID_2)
		perror("Error\n   --- PID 2 failure\n");
	if (error == ERROR_CMD_1_NOT_EXISTS)
		perror("Error\n   --- Command 1 not exists\n");
	if (error == ERROR_CMD_2_NOT_EXISTS)
		perror("Error\n   --- Command 2 not exists\n");	
}

static void	ft_errors_with_free_needs(int error, t_pipex *d)
{
	if (error == ERROR_SPLIT_EXTRACTING_CMD)
	{
		perror("Error\n   --- Command 2 not exists\n");
		ft_free_all(d);
	}
}

void	ft_errors(int error, t_pipex *d)
{
	if (error < 20)
		ft_less_20(error, d);
	else if (error < 30)
		ft_errors_with_free_needs(error, d);
	exit(EXIT_FAILURE);
}
