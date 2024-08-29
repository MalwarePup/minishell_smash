/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/29 23:03:55 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

// UTILITAIRES D'AJOUTS / SUPPRESSIONS DE VARIABLES

t_env	*env_new_var(char *content)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (new_var == NULL)
		return (NULL);
	new_var->content = ft_strdup(content);
	new_var->next = NULL;
	return (new_var);
}

char	*var_to_remove(t_env *env, char *to_find)
{
	t_env	*head;
	int		len_to_find;
	
	head = env;
	len_to_find = ft_strlen(to_find);
	while (head != NULL)
	{
		if (ft_strncmp(head->content, to_find, len_to_find) == 0);
	}
}

void	del_env_var(t_env **env, t_env *var)
{
	t_env	*prev;
	t_env	*tmp;

	if (env == NULL || (*env) == NULL || var == NULL)
		return ;
	prev = NULL;
	tmp = *env;
	if (*env == var)
	{
		*env = var->next;
		free(var->content);
		free(var);
		return ;
	}
	while (tmp != NULL && tmp != var)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = var->next;
	free(var->content);
	free(var);
}