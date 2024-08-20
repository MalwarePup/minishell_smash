/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:41:26 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/20 20:22:07 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*	Recherche une variable d'environnement spécifique dans env (g->env),
	puis retourne la valeur associée si elle est trouvée
*/
static char	*__find_var_path(char *to_find, t_env *env)
{
	t_env	*head;
	char	*path;
	int		l_var_env;
	int		l_to_find;

	head = env;
	path = NULL;
	l_var_env = ft_strlen(env->content);
	l_to_find = ft_strlen(to_find);
	while (head != NULL)
	{
		if (ft_strncmp(head->content, to_find, l_to_find) == 0)
		{
			path = ft_substr(env->content, l_to_find, (l_var_env - l_to_find));
			return (path);
		}
		head = head->next;
	}
	return (NULL);
}

static int	__cd_to_env_var(t_global *g, char *var)
{
	char	*var_path;
	int		ret;

	var_path = __find_var_path(var, g->env);
	printf("%s %s\n", BOLD BLUE "PATH:" RESET, var_path);
	ret = chdir((const char *)var_path);
	printf("%s %d\n", BOLD YELLOW "1. RETURN de chdir:" RESET, ret);
	if (ret != 0)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, g->token->content);
		printf("%s: %s\n", g->token->next->content, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (var_path != NULL)
		free(var_path);
	return (ret);
}

// static void	__update_env_paths(void)
// {
// 	char	cwd[PATH_MAX];
// 	char	*old_pwd;

// 	// valeur actuelle de PWD
// 	old_pwd = getenv("PWD");
// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 	{
// 		printf("%s %s: ", BOLD RED "minishell:", RESET "getcwd"); 
// 		printf("%s\n", strerror(errno));
// 		return ;
// 	}
// 	// maj de OLDPWD
// 	// maj de PWD avec le nouveau working directory
// }

int	my_cd(t_global *g)
{
	int	ret;
	
	if (g->token->next == NULL)
		ret = __cd_to_env_var(g, "HOME=");
	else if (ft_strcmp((const char *)g->token->next->content, "-") == 0)
		ret = __cd_to_env_var(g, "OLDPWD=");
	else
	{
		ret = chdir((const char *)g->token->next->content);
		printf("%s %d\n", BOLD BLUE "2. RETURN de chdir:" RESET, ret);
	}
	if (ret != 0)
	{
		printf("%s %s: ", BOLD RED "minishell:" RESET, g->token->content);
		printf("%s: %s\n", g->token->next->content, strerror(errno));
		return (EXIT_FAILURE);
	}
	// __update_env_paths();
	return (EXIT_SUCCESS);
}
