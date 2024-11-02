/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:30:48 by art3mis           #+#    #+#             */
/*   Updated: 2024/11/02 20:58:28 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	secure_malloc(void *to_secure, bool cleanup)
{
	if (to_secure == NULL)
	{
		err_msg("malloc", strerror(errno), 0);
		if (cleanup == true)
			clean_exit_shell(FAILURE);
	}
}

void	free_and_set_null(void **to_free)
{
	if (to_free != NULL && (*to_free) != NULL)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

void	get_closed_quotes(char c, bool closed_quotes[])
{
	if (c == '\'' && closed_quotes[1] == true)
		closed_quotes[0] = switch_bool(closed_quotes[0]);
	else if (c == '"' && closed_quotes[0] == true)
		closed_quotes[1] = switch_bool(closed_quotes[1]);
}
