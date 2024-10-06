/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:37:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/20 14:54:04 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Readline should not count escape sequences as visible characters.
	This is achieved by encapsulating the non-visible parts (escape
	sequences) of the prompt between special sequences :
	
	-	\001 (start of non-visible sequence)
	-	\002 (end of non-visible sequence)
	
	This enables readline to manage the length of the prompt correctly.
*/
static char	*__generate_prompt(void)
{
	char	*username;
	char	*rb_username;
	char	*header;
	char	*part1;
	char	*prompt;
	
	username = getenv("USER");
	if (username == NULL)
		username = "unknown";
	rb_username = rainbow_prompt(username);
	header = ft_strjoin("\001" BOLD PROMPT_BAR "\002", "\001" BOLD "[" "\002");
	secure_malloc(header);
	part1 = ft_strjoin(header, rb_username);
	secure_malloc(part1);
	(free(header), free(rb_username));
	prompt = ft_strjoin(part1, "\001" BOLD "\002" "@42]\001" R "\002 $> ");
	secure_malloc(prompt);
	(void)yama(ADD, prompt, 0);
	free(part1);
	return (prompt);
}

// static char	*__generate_prompt(void)
// {
// 	char	*username;
// 	char	*rb_bar;
// 	char	*header;
// 	char	*part1;
// 	char	*prompt;
	
// 	username = getenv("USER");
// 	if (username == NULL)
// 		username = "unknown";
// 	rb_bar = rainbow_prompt("\001" BOLD PROMPT_BAR "\002");
// 	header = ft_strjoin(rb_bar, "\001" BOLD "[" "\002");
// 	secure_malloc(header);
// 	part1 = ft_strjoin(header, username);
// 	secure_malloc(part1);
// 	(free(header), free(username));
// 	prompt = ft_strjoin(part1, "\001" BOLD "\002" "@42]\001" R "\002 $> ");
// 	secure_malloc(prompt);
// 	(void)yama(ADD, prompt, 0);
// 	free(part1);
// 	return (prompt);
// }

// singleton version
t_data	*data_struct(void)
{
	static t_data	*instance = NULL;

	if (instance == NULL)
	{
		instance = yama(CREATE, NULL, sizeof(t_data));
		secure_malloc(instance);
		instance->prompt = __generate_prompt();
		if (instance->prompt == NULL)
			clean_exit_shell(FAILURE);
		instance->main = NULL;
		instance->token = NULL;
		instance->exec = NULL;
		instance->env = NULL;
		instance->exp_env = NULL;
		instance->last_exit_status = 0;
	}
	return (instance);
}
