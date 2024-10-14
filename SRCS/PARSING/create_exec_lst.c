/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exec_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:44:18 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/14 22:56:30 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__init_exec(t_token_dblst *t, t_ptrs *p)
{
	p->new_task = exec_lst_new_node();
	secure_malloc(p->new_task);
	p->size = (sizeof(char *) * (cmd_token_count(t) + 1));
	p->new_task->cmd = yama(CREATE_TAB, NULL, p->size);
	secure_malloc(p->new_task->cmd);
}

static void	__command_case(t_token_dblst *t, t_ptrs *p)
{
	char	*cleaned_token;

	cleaned_token = token_cleanup(t->content);
	p->new_task->cmd[p->i] = cleaned_token;
	if (ft_strchr(cleaned_token, '/') != NULL)
	{
		p->new_task->absolute_path = true;
		p->new_task->bin_path = cleaned_token;
	}
	p->i++;
}

static void	__word_case(t_token_dblst *t, t_ptrs *p)
{
	char	*cleaned_token;

	if (p->new_task != NULL)
	{
		cleaned_token = token_cleanup(t->content);
		p->new_task->cmd[p->i] = cleaned_token;
	}
	p->i++;
}

static void	__add_new_task(t_data *d, t_ptrs *p)
{
	if (p->new_task != NULL)
	{
		p->new_task->cmd[p->i] = NULL;
		exec_lst_add_back(&(d->exec), p->new_task);
	}
}

int	create_exec_lst(t_data *d)
{
	t_token_dblst	*head;
	t_ptrs			p;

	head = d->token;
	init_ptrs(&p);
	while (d->token != NULL)
	{
		if (p.new_task == NULL)
			__init_exec(d->token, &p);
		if (d->token->type == COMMAND)
			__command_case(d->token, &p);
		else if (d->token->type == WORD)
			__word_case(d->token, &p);
		else if (p.new_task != NULL && d->token->type == HERE_DOC)
			p.new_task->heredoc_nb++;
		d->token = d->token->next;
	}
	__add_new_task(d, &p);
	d->token = head;
	if (create_redir_lst(d, p.new_task) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
