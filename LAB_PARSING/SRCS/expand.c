/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:42:03 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 19:49:38 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mini_parsing.h"
// EXEMPLE : BLANC"$ROUGE"BLEU = BLANC""BLEU
// IDX[0] = debut str ; IDX[1] = CHAR AVANT $ ; IDX[2] = CHAR APRES VAR
static char	*__del_var(char *str, char *var, size_t var_size)
{ 
	int	idx[3];
	char *new_str;

	idx[0] = 0;
	idx[1] = (var - str);
	idx[2] = (var - str) + 1;
	new_str = malloc((ft_strlen(str) - var_size + 1) * (sizeof(char)));
	while ((str[idx[2]] >= 'A' && str[idx[2]] <= 'Z') || (str[idx[2]] >= '0' && str[idx[2]] <= '9') || (str[idx[2]] == '_'))
		idx[2]++;
	while (idx[0] != idx[1])
	{
		new_str[idx[0]] = str[idx[0]];
		idx[0]++;
	}
	while (str[idx[2]])
	{
		new_str[idx[0]] = str[idx[2]];
		idx[0]++;
		idx[2]++;	
	}
	new_str[idx[0]] = '\0';
	free(str);
	return (new_str);
}
//EXEMPLE : gg"$USER"wp = gg"pmateo"wp
// static char	*__add_var_value(char *str, char *var, char *var_value, size_t vv_size)
// {
// 	int idx[3];
// 	char *new_str;

// 	idx[0] = 0;
// 	idx[1] = (var - str);
// 	idx[2] = (var - str) + 1;
// 	new_str = malloc((ft_strlen(str) + vv_size + 1) * (sizeof(char)));
// 	while ((str[idx[2]] >= 'A' && str[idx[2]] <= 'Z') 
// 				|| (str[idx[2]] >= '0' && str[idx[2]] <= '9') 
// 				|| str[idx[2]] == '_')
// 		idx[2]++;
// 	while (idx[0] != idx[1])
// 	{
// 		new_str[idx[0]] = str[idx[0]];
// 		idx[0]++;
// 	}
// 	while (*var_value != '\0')
// 	{
// 		new_str[idx[0]] = *var_value;
// 		idx[0]++;
// 		var_value++;
// 	}
// 	while (str[idx[2]])
// 	{
// 		new_str[idx[0]] = str[idx[2]];
// 		idx[0]++;
// 		idx[2]++;
// 	}
// 	new_str[idx[0]] = '\0';
// 	free(str);
// 	return (new_str);
// }

static char	*__add_var_value(char *str, char *var, char *var_value, size_t vv_size)
{
	char	*new_str;
	char	*start_str;
	size_t	i;
	size_t	var_len;

	start_str = str;
	var_len = 0;
	while ((var[var_len] >= 'A' && var[var_len] <= 'Z')
			|| (var[var_len] >= '0' && var[var_len] <= '9')
			|| var[var_len] == '_')
		var_len++;
	new_str = malloc(ft_strlen(str) + (vv_size - var_len + 1) * (sizeof(char)));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str != var)
		new_str[i++] = *str++;
	while (*var_value)
		new_str[i++] = *var_value++;
	str += var_len;
	while (*str)
		new_str[i++] = *str++;
	new_str[i] = '\0';
	free(start_str);
	return (new_str);
}

static char	*__expand(char *str, char *var, char **envp)
{
	char 	*to_find;
	char	*var_value;

	to_find = take_var(str, var);
	var_value = search_var(to_find, envp);
	if (var_value == NULL)
		str = del_var(str, var, ft_strlen(to_find) + 1);
	else
		str = add_var_value(str, var, var_value, ft_strlen(var_value));
	return (str);
}

//EXEMPLE : "'$USER'" = "'pmateo'" | '"$USER"' = '"$USER"'
char *handle_expand(char *str, char **envp)
{
	int		i;
	bool 	closed[2];

	i = 0;
	closed[0] = true;
	closed[1] = true;
	while (str[i] != '\0')
	{
		if (str[i] == '"' && closed[1] != false)
			closed[0] = switch_bool(closed[0]);
		if (str[i] == '\'' && closed[0] != false)
			closed[1] = switch_bool(closed[1]);
		if (str[i] == '$' && closed[1] != false)
			str = expand(str, &str[i], envp);
		i++;
	}
	str = empty_quotes(str);
	return (str);
}
