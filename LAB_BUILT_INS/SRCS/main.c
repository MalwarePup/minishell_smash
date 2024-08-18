/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:13:47 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/16 18:01:55 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

t_global	g;

static void    init_global(t_global *g)
{
	g->input = NULL;
	g->env = NULL;
	g->export_env = NULL;
}

static char	*get_user_name(void)
{
	const char		*name;
	char			*bracket;
	char			*full_name;
	
	name = getenv("USER");
	bracket = "[";
	full_name = ft_strjoin(bracket, name);
	return (full_name);
}

int	main(int argc, char **argv, char **envp)
{
	char		*user;
	char		*prompt;

	if (argc > 1)
		exit(EXIT_FAILURE);
	(void)argv;
	init_global(&g);
	create_env(&g, envp);
	user = get_user_name();
	prompt = ft_strjoin(user, "@42] $> ");
	while (1)
	{
		g.input = readline(prompt);
		if (*g.input)
		{
			exec_built_in(*g.input);
			add_history(g.input);
		}
		// free(g.input);
	}
	printf("%s%s%s", PURPLE, "Bye le sang\n", RESET);
	free(user);
	free(prompt);
	return (0);
}
