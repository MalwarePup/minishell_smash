/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:35:38 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/20 17:30:55 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	lstclear_main(t_main_lst **main)
{
	t_main_lst	*tmp;
	
	if (main == NULL || (*main) == NULL)
		return ;
	while ((*main) != NULL)
	{
		tmp = (*main)->next;
		(*main)->next = NULL;
		free((*main)->content); 
		(*main)->next = NULL;
		free(*main);
		(*main) = tmp;
	}
}

void	lstclear_tokens(t_token_dblst **t)
{
	t_token_dblst	*tmp;
	
	if (t == NULL || (*t) == NULL)
		return ;
	while ((*t) != NULL)
	{
		tmp = (*t)->next;
		(*t)->next = NULL;
		free((*t)->content);
		(*t)->content = NULL;
		free(*t);
		(*t) = tmp;
	}
}

void	lstclear_env(t_env_lst **env)
{
	t_env_lst *tmp;

	if (env == NULL || (*env) == NULL)
		return ;
	while ((*env) != NULL)
	{
		tmp = (*env)->next;
		(*env)->next = NULL;
		free((*env)->content);
		(*env)->content = NULL;
		free(*env);
		(*env) = tmp;
	}
}

void	free_data(t_data *d, bool clear_history)
{
	if (d != NULL)
	{
		if (d->prompt != NULL)
			free(d->prompt);
		if (d->main != NULL)
			lstclear_main(&d->main);
		if (d->token != NULL)
			lstclear_tokens(&d->token);
		if (clear_history == true)
		{
			if (d->env != NULL)
				lstclear_env(&d->env);
			if (d->exp_env != NULL)
				lstclear_env(&d->exp_env);
			rl_clear_history();
		}
		free(d);
	}
}
