/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:44:47 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/08 17:04:18 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

static bool	__n_option_exist(char *arg)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	while (arg[i] != '\0' && arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (false);
	return (true);
}

int my_echo(char **args)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	if (args[i] != NULL && __n_option_exist(args[i]) == true)
	{
		flag = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}