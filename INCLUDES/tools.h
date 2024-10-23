/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:59:30 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 15:05:20 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "libraries.h"

/******************************************************************************\
 * TOOLS
\******************************************************************************/

// err_msg.c
void			err_msg(char *detail, char *reason, int quotes);
int				err_msg_cmd(char *cmd, char *detail, char *reason,
					int err_status);

// secure.c
void    		free_and_set_null(void *to_free);
void			secure_malloc(void *to_secure, bool cleanup);

// lstclear.c
void			lstclear_redir(t_redir_lst **r);
void			lstclear_exec(t_exec_lst **e);
void			lstclear_token(t_token_dblst **t);
void			lstclear_main(t_main_lst **main);
void			lstclear_env(t_env_lst **env);

// garbage_collector_lst_utils.c
int				remove_gc_node(t_gc_lst**yama, void *ptr);
void			add_gc_node(t_gc_lst **yama, t_gc_lst *node);
void			*new_gc_node(void *ptr, bool is_tab);

// garbage_collector_utils.c
void			*search_ptr(t_gc_lst **yama, void *ptr);
int				handle_remove(t_gc_lst **yama, void *ptr);


// garbage_collector.c
void			*yama(int flag, void *ptr, size_t size);

// cleanup.c
void			clean_after_execution(t_data *d, char *user_input);
void			free_tab(char **tab);
int				free_gc_tab(t_gc_lst **yama, char **ptr);
void			clean_exit_shell(int err_status);

/******************************************************************************\
 * MINISHELL_LISTS
\******************************************************************************/

// main_lst.c
void			del_unwanted_whitespaces(t_main_lst *main);
size_t			get_main_lst_size(t_main_lst **main);
void			main_lst_add_back(t_main_lst **main, t_main_lst *new_node);
t_main_lst		*main_lst_new_node(char *content);

// token_dblst.c
void			del_current_token(t_token_dblst **t, t_token_dblst *to_delete);
size_t			get_token_dblst_size(t_token_dblst **t);
void			token_dblst_add_back(t_token_dblst **t,
					t_token_dblst *new_node);
t_token_dblst	*token_dblst_new_node(char *content, t_token_type type);

// redir_lst.c
bool			is_redir(char *str);
size_t			get_redir_lst_size(t_redir_lst **r);
void			redir_lst_add_back(t_redir_lst **r, t_redir_lst *new_node);
t_redir_lst		*redir_lst_new_node(t_token_type type);

// exec_lst.c
size_t			get_exec_lst_size(t_exec_lst **e);
void			exec_lst_add_back(t_exec_lst **e, t_exec_lst *new_node);
t_exec_lst		*exec_lst_new_node(void);

/******************************************************************************\
 * FEATURES
\******************************************************************************/

// display_2.c
void			display_exec_lst(t_exec_lst **e);
void			print_cmd(char **cmd);
void			print_tab(char **tab);
void			print_tab2(char **tab);
void			display_shell_info(void);

// display.c
void			display_main_lst(t_main_lst **main);
void			display_token_dblst(t_token_dblst **t);
void			display_redir_lst(t_redir_lst **r);

// rainbow_txt.c
char			*rainbow_prompt(const char *str);

#endif