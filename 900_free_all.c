/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_free_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:33:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/26 20:39:17 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(t_pipex *d)
{
	if (d->cmd_1 != NULL)
		free(d->cmd_1);
	if (d->cmd_2 != NULL)
		free(d->cmd_2);
	if (d->env_path != NULL)
		free(d->env_path);
	if (d->path_cmd_1 != NULL)
		free(d->path_cmd_1);
	if (d->path_cmd_2 != NULL)
		free(d->path_cmd_2);
	if (d->cmd_1_argmts != NULL)
		ft_freedom(d->cmd_1_argmts);
	if (d->cmd_2_argmts != NULL)
		ft_freedom(d->cmd_2_argmts);
}
