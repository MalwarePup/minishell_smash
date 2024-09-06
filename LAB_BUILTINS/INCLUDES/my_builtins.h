/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:11:16 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/06 02:43:33 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_BUILTINS_H
# define MY_BUILTINS_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../../LIBFT/INCLUDES/libft.h"
# include "../../LIBFT/INCLUDES/ft_printf.h"
# include "../../LIBFT/INCLUDES/get_next_line_bonus.h"
# include "colors.h"

# define WELCOME_BANNER "\e[96m╔══════════════════════════════════════════════════════════════════════════════════╗\n║                                                                                  ║\n║  \e[35m___________   __________                    ___________\t\t           \e[96m║\n║  \e[35m\\__    ___/   \\______   \\  ____  ___  ___   \\__    ___/____  _____     _____    \e[96m║\n║    \e[35m|    | ______|       _/_/ __ \\ \\  \\/  /     |    | _/ __ \\ \\__  \\   /     \\   \e[96m║\n║    \e[35m|    |/_____/|    |   \\\\  ___/  >    <      |    | \\  ___/  / __ \\_|  Y Y  \\  \e[96m║\n║    \e[35m|____|       |____|_  / \\___  >/__/\\_ \\     |____|  \\___  >(____  /|__|_|  /  \e[96m║\n║\t\t         \e[35m\\/      \\/       \\/                 \\/      \\/       \\/   \e[96m║\n║                                                                                  ║\n╚══════════════════════════════════════════════════════════════════════════════════╝\n\n\n"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/******************************************************************************\
 * EXIT STATUS
\******************************************************************************/

# define SUCCESS 0
# define FAILURE 1
# define MISUSE_BUILTIN 2
# define CMD_CANNOT_EXEC 126
# define CMD_NOT_FOUND 127
# define CTRL_C_EXIT 130 // 128 + signal 2 (SIGINT)
# define KILL_EXIT 143 // 128 + signal 15 (SIGTERM)
# define OUT_OF_RANGE 255

# define ERR_PREFIX BOLD RED "minishell: " RESET
# define ERR_NEAR_PIPE "syntax error near unexpected token `|'"
# define ERR_MALLOC_LST "failed to allocate memory for a new node"

/******************************************************************************\
 * GLOBAL VARIABLE
\******************************************************************************/

extern int	g_sig_code;

/******************************************************************************\
 * STRUCTS
\******************************************************************************/

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}				t_token;

typedef struct s_global
{
	char		*prompt;
	char		*input;
	t_env		*env;
	t_env		*exp_env;
	t_token		*token;
	int			last_exit_status;
}				t_global;

/******************************************************************************\
 * FUNCTIONS
\******************************************************************************/

t_env		*env_new_var(char *content);
void		lstclear_env(t_env **env);
int			create_env_list(t_env **env, char **envp);
void		create_env(t_global *g, char **envp);

size_t		get_env_size(char **env);
t_env		*copy_toppest(char **envp);
t_env		*ascii_sort(char **envp, char *last_added);
int			create_exp_env_list(t_env **exp_env, char **envp, size_t envp_size,
size_t idx_exp_env);

t_token		*new_node(char *content);
t_token		*last_node(t_token *t);
void		add_back(t_token **t, t_token *new_node);
void		lstclear_tokens(t_token **t);
void		display_tokens(t_token *t);

void		exec_built_in(char **built_in, t_global *g);
int			my_pwd(void);
void		change_paths(t_env *env, t_env *exp_env);
int			my_cd(t_global *g);
int			my_env(t_env *env);
int			my_exit(t_global *g, char **args);
void		del_env_var(t_env **env, char *var_to_rm);
int			my_unset(t_global *g, char **args);

void		err_msg(char *detail, char *reason);
int			err_msg_cmd(char *cmd, char *detail, char *reason, int err_status);

void		free_tab(char **tab);
void    	free_global(t_global *g, bool clear_history);
void		clean_exit_shell(t_global *g, int err_status);

void		rainbow_txt(const char *str);
void		rainbow_txt_nonl(const char *str);
char		*rainbow_prompt(const char *str);

#endif