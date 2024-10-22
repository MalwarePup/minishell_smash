/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/22 23:49:58 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries.h"

/*	To be used only to indicate a received signal.
	The signal handler must not access our main data structures.
*/
extern int		g_sig_code;

/******************************************************************************\
 * ENVIRONMENT
\******************************************************************************/

// export_env_utils.c
int				cmp_to_equal(const char *s1, const char *s2);
t_env_lst		*copy_toppest(char **envp);
t_env_lst		*ascii_sort(char **envp, char *last_added);
char			*add_quotes_to_value(char *var);
t_env_lst		*exp_env_new_var(char *content);

// env_utils.c
size_t			get_envlst_size(t_env_lst **env);
size_t			get_envtab_size(char **env);
t_env_lst		*env_new_var(char *content);
void			del_env_var(t_env_lst **env, char *var_to_rm);
char			**recreate_env_tab(t_env_lst **env);

// create_env.c
int				create_exp_env_list(t_env_lst **exp_env, char **envp,
					size_t envp_size, size_t idx_exp_env);
int				create_env_list(t_env_lst **env, char **envp);
void			create_env(t_data *d, char **envp);

/******************************************************************************\
 * SIGNALS
\******************************************************************************/

// signals.c
void			handle_sigquit(void);
void			set_signals(void);

// signals_here_doc.c
void    		set_signals_in_heredoc(void);

/******************************************************************************\
 * INIT
\******************************************************************************/

// prompt.c
char			*generate_prompt(t_prompt *pr, t_data *d);
void			update_prompt(t_data *d, t_prompt *pr);

// init_data.c
t_data			*data_struct(void);

/******************************************************************************\
 * EXPANSION
\******************************************************************************/

// expand_utils.c
size_t			len_to_equal(char *str);
char			*clean_translated_variable(char *str, char *var);
char			*take_var(char *str, char *var);
char			*search_var(char *to_find, t_env_lst *env);

// expand.c
char			*expand(t_data *d, char *str, bool in_heredoc);

#endif