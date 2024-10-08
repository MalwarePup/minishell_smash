/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/08 19:25:50 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *path_bin, char **cmd_and_args, char **env)
{
	if (execve(path_bin, cmd_and_args, env) == -1)
	{
		free(path_bin);
		path_bin = NULL;
		return ; // à changer
	}
}

void	go_exec(t_exec_lst *node, char **env)
{
	if (handle_bin_path(node, env) == 0)
		exec(node->bin_path, node->cmd, env);
	else
		return ;
}
// gerer le cas des redirections seules (aucune commande)