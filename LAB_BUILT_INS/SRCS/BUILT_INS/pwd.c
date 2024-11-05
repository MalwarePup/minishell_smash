/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:12:03 by annabrag          #+#    #+#             */
/*   Updated: 2024/11/05 01:57:23 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

/*	PWD means Print Working Directory
	The $PWD environment variable is a dynamic variable
	that stores the path to the current working directory.
*/
int	my_pwd(void)
{
	char	cwd[MY_PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		err_msg("0: getcwd() failed", "No such file or directory", 0);
		return (errno);
	}
	printf("%s\n", cwd);
	// g->last_exit_status = 0;
	return (SUCCESS);
}
