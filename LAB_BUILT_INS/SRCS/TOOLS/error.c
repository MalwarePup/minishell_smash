/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:42:30 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/09 20:59:20 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

static char	*__append_strs(char *s1, char *s2)
{
	char	*tmp;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (ft_strdup(s2));
	tmp = s1;
	s1 = ft_strjoin(tmp, s2);
	if (s1 == NULL)
		return (NULL);
	free(tmp);
	return (s1);
}

void	err_msg(char *detail, char *reason, int quotes)
{
	char	*msg;

	msg = NULL;
	if (detail != NULL)
	{
		if (quotes == 1)
		{
			msg = __append_strs(__append_strs(NULL, ERR_PREFIX), "‘");
			msg = __append_strs(msg, detail);
			msg = __append_strs(msg, "’");
		}
		else
			msg = __append_strs(__append_strs(NULL, ERR_PREFIX), detail);
		msg = __append_strs(msg, ": ");
		msg = __append_strs(msg, reason);
	}
	else
		msg = __append_strs(__append_strs(NULL, ERR_PREFIX), reason);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
}

int	err_msg_cmd(char *cmd, char *detail, char *reason, int err_status)
{
	char	*msg;

	msg = NULL;
	if (cmd != NULL)
	{
		msg = __append_strs(__append_strs(NULL, ERR_PREFIX), cmd);
		msg = __append_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (ft_strncmp(cmd, "unset", 6) == 0)
			msg = __append_strs(msg, "`");
		msg = __append_strs(msg, detail);
		if (ft_strncmp(cmd, "unset", 6) == 0)
			msg = __append_strs(msg, "'");
		msg = __append_strs(msg, ": ");
	}
	msg = __append_strs(msg, reason);
	ft_putendl_fd(msg, STDERR_FILENO);
	free(msg);
	return (err_status);
}