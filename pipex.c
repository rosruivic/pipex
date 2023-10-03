/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:14:23 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/27 20:22:21 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief USE OF 'access' FUNCTion:
 * 	-	returns 0 if success; 
 * 	-	returns -1 if error (& the global vble errno is set
 * 													to indicate the error)
 * 	Checks the accessibility of the file named by the path argument
 *    for the access permissions indicated by the mode argument.
 *    The value of mode is either the bitwise-inclusive OR of the access
 *    permissions to be checked (R_OK for read permission, W_OK for write
 *    permission, and X_OK for execute/search permission),
 *    or the existence test (F_OK).
 * @param argv 
 */
static void	ft_check_infile(char *file1, t_pipex *d)
{
	if (access(file1, R_OK | F_OK) != 0)
		ft_errors(ERROR_INFILE, d);
}

static void	ft_check_outfile(char *file2, t_pipex *d)
{
	(void)file2;
	(void)d;
/* 	if (access(file2, W_OK) != 0)
		ft_errors(ERROR_OUTFILE, d); */
}

static void	ft_check_argmts(int argc, t_pipex *d)
{
	if (argc != 5)
		ft_errors(ERROR_ARGMTS, d);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	ft_check_argmts(argc, &data);
	ft_check_infile(argv[1], &data);
	ft_check_outfile(argv[5], &data);
	if (pipe(data.fd) == -1)
		ft_errors(ERROR_PIPE, &data);
	ft_init_data(&data, argv, envp);
	ft_forks(&data, envp);
	return (0);
}
