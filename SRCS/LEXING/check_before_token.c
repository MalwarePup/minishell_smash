/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:56:00 by art3mis           #+#    #+#             */
/*   Updated: 2024/09/22 22:10:27 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__strldup_quote_split(t_token_parser *p)
{
	char    *tmp;

	tmp = NULL;
	if (p->i > p->start) // Assure qu'on ne capture pas plusieurs espaces
	{
		tmp = ft_strldup(p->main->content + p->start, p->i - p->start);
		if (tmp == NULL)
			(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
		(void)yama(ADD, tmp, 0);
		p->seg_elems[p->token_count++] = tmp;
	}
}

static void	__quote_parser(t_token_parser *p)
{
    p->closed_quotes[0] = true;
    p->closed_quotes[1] = true;
	p->i = 0;
	p->start = p->i;
	// printf("main->content: |%s|\n", p->main->content);
    while (p->main->content[p->i] != '\0')
	{
		if (p->main->content[p->i] == '\'')
		{
			p->closed_quotes[0] = switch_bool(p->closed_quotes[0]);
			if (p->closed_quotes[0] == true)
				__strldup_quote_split(p);
		}
		else if (p->main->content[p->i] == '"')
		{
			p->closed_quotes[1] = switch_bool(p->closed_quotes[1]);
			if (p->closed_quotes[1] == true)
				__strldup_quote_split(p);
		}
		else if (p->main->content[p->i] == ' ' && p->closed_quotes[0] == true && p->closed_quotes[1] == true)
		{
			__strldup_quote_split(p);
			while (ft_isspace(p->main->content[p->i]) == 1)
				p->i++;
			p->start = p->i; // Redéfinir le début pour le prochain token
		}
		else
			p->i++;
	}
	// Ajouter le dernier token s'il reste des caractères à traiter
	__strldup_quote_split(p);
}

static char	**__split_quoted_tokens(t_main_lst *main, t_token_parser *p)
{
	ft_bzero(p, sizeof(p));
	p->main = main;
	p->seg_elems = yama(CREATE_TAB, NULL,
	(sizeof(char *) * (ft_strlen(main->content) + 1)));
	if (p->seg_elems == NULL)
		(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
	while (p->main->content[p->i] != '\0')
		__quote_parser(p);
	p->seg_elems[p->token_count] = NULL;
	return (p->seg_elems);
}

char	**split_main_content(t_main_lst *main)
{
	t_token_parser	p;

	ft_bzero(&p, sizeof(p));
	p.main = main;
	if (p.main == NULL || p.main->content == NULL)
		return (NULL);
	if (ft_strchr(p.main->content, '\'') != NULL
		|| ft_strchr(p.main->content, '"') != NULL)
	{
		p.seg_elems = __split_quoted_tokens(p.main, &p);
		if (p.seg_elems == NULL)
			return (err_msg("malloc", ERR_QUOTES, 0), NULL);
	}
	else
	{
		p.seg_elems = ft_split(p.main->content, ' ');
		if (p.seg_elems == NULL)
			(err_msg("malloc", ERR_MALLOC, 0), clean_exit_shell(FAILURE));
		(void)yama(ADD, p.seg_elems, 0);
	}
	return (p.seg_elems);
}
