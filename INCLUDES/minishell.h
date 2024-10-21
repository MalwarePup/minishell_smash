/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/21 22:58:09 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries.h"

/******************************************************************************\
 * GLOBAL VARIABLE
\******************************************************************************/

/*	The global variable have to be used only to indicate a received signal.
	Consider the implications: this approach ensures that your signal handler
	will not access your main data structures.
*/
extern int		g_sig_code;

/******************************************************************************\
 * INIT
\******************************************************************************/

// prompt.c
char			*generate_prompt(t_prompt *pr);
void			update_prompt(t_data *d, t_prompt *pr);

// init_data.c
t_data			*data_struct(void);

/******************************************************************************\
 * LEXING
\******************************************************************************/

// check_input.c
void			parse_input(t_parser *p);

// create_main_lst.c
int				create_main_lst(t_data *d, char *user_input);

// check_main.c
void			parse_segment(t_token_parser *p);

// tokenization.c
void			lst_tokenization(t_token_dblst *t);

// create_token_lst.c
int				create_token_dblst(t_data *d);

/******************************************************************************\
 * PARSING
\******************************************************************************/

// check_sequence.c
int				check_redir_sequence(char *content, t_token_parser *p);

// quotes_utils.c
bool			switch_bool(bool closed);
int				find_closing_quote(char *str, char quote);
bool			unclosed_quotes_return(bool closed[]);
char			*del_empty_quotes(char *str, int quote_idx);
char			*del_quote_pair(char *str, int first, int second);

// handle_quotes.c
bool			unclosed_quotes(char *str);
char			*empty_quotes(char *str);
char			*other_quotes(char *str);

// redir_lst_utils.c
t_redir_lst		*redir_in_n_infile(t_data *d);
t_redir_lst		*redir_out_trunc_n_outfile(t_data *d);
t_redir_lst		*redir_out_append_n_outfile(t_data *d);
t_redir_lst		*heredoc_n_limiter(t_data *d);

// create_redir_lst.c
int				create_redir_lst(t_data *d, t_exec_lst *existing_task);

// exec_lst_utils.c
void			init_ptrs(t_ptrs *p);
char			*token_cleanup(char *content);
int				cmd_token_count(t_token_dblst *t);

// create_exec_lst.c
int				create_exec_lst(t_data *d);

/******************************************************************************\
 * ENVIRONMENT
\******************************************************************************/

// export_env_utils.c
t_env_lst		*copy_toppest(char **envp);
t_env_lst		*ascii_sort(char **envp, char *last_added);

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
 * EXPANSION
\******************************************************************************/

// expand_utils.c
size_t			len_to_equal(char *str);
char			*clean_translated_variable(char *str, char *var);
char			*take_var(char *str, char *var);
char			*search_var(char *to_find, t_env_lst *env);

// expand.c
char			*expand(t_data *d, char *str, bool in_heredoc);

/******************************************************************************\
 * BUILT-INS
\******************************************************************************/

// ft_exit.c
void			ft_exit(t_data *d, char **args);

// ft_env.c
int				ft_env(t_env_lst *env);

// ft_unset.c
int				ft_unset(t_data *d, char **args);

// ft_pwd.c
int				ft_pwd(void);

// cd_utils.c
void			change_paths(t_env_lst *env, t_env_lst *exp_env);

// ft_cd.c
int				ft_cd(t_data *d);

// ft_echo.c
int				ft_echo(char **args);

// built_ins.c
void			exec_built_in(char **built_in, t_data *d);

/******************************************************************************\
 * EXECUTION
\******************************************************************************/

// exec_utils.c
char			*search_bin(char *cmd, char **tab_path);
char			**search_path(char **tab_path, char **env);
int				check_bin_path(t_exec_lst *node, bool absolute_path);
int				handle_bin_path(t_exec_lst *node, char **env);

// exec.c
void			exec(char *path_bin, char **cmd_and_args, char **env);
void			go_exec(t_exec_lst *node, char **env);

// here_doc.c
void			handle_heredoc(t_data *d, t_exec_lst **e_lst);

// pathfinder.c
void			pathfinder(t_data *d, t_exec_lst *node, char **env);

// while_cmd.c
void			while_cmd(t_data *d, t_exec_lst **e_lst);

/******************************************************************************\
 * LISTS in TOOLS/
\******************************************************************************/

// main_lst.c
size_t			get_main_lst_size(t_main_lst **main);
void			main_lst_add_back(t_main_lst **main, t_main_lst *new_node);
t_main_lst		*main_lst_new_node(char *content);
void			del_unwanted_whitespaces(t_main_lst *main);

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
 * TOOLS
\******************************************************************************/

// err_msg.c
void			err_msg(char *detail, char *reason, int quotes);
int				err_msg_cmd(char *cmd, char *detail, char *reason,
					int err_status);

// lstclear.c
void			lstclear_main(t_main_lst **main);
void			lstclear_token(t_token_dblst **t);
void			lstclear_redir(t_redir_lst **r);
void			lstclear_exec(t_exec_lst **e);
void			lstclear_env(t_env_lst **env);

// garbage_collector_utils.c
int				remove_gc_node(t_gc_lst**yama, void *ptr);
void			add_gc_node(t_gc_lst **yama, t_gc_lst *node);
void			*new_gc_node(void *ptr, bool is_tab);

// garbage_collector.c
int				free_gc_tab(t_gc_lst **yama, char **ptr);
void			*yama(int flag, void *ptr, size_t size);

// cleanup.c
void			secure_malloc(void *to_secure, bool cleanup);
void			free_tab(char **tab);
void			clean_exit_shell(int err_status);

#endif