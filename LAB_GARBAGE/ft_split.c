/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:20:32 by pmateo            #+#    #+#             */
/*   Updated: 2023/06/20 22:20:32 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static char	*ft_substr(const char *src, unsigned int start, size_t len)
{
	char	*sub;

	if (!src)
		return (NULL);
	if ((size_t)start > ft_strlen(src))
		start = ft_strlen(src);
	if (len > (ft_strlen(src) - start))
		len = ft_strlen(src) - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, src + start, len);
	sub[len] = 0;
	return (sub);
}

static void	freeall(char **tab)
{
	char	**tmp;

	tmp = tab;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(tab);
}

static int	count_substr(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
		{
			j++;
			i++;
		}
		else
			i++;
	}
	return (j);
}

static void	extract_and_fill(char **tab, char const *s, char c)
{
	char		**ptab;
	char const	*tmp;

	ptab = tab;
	tmp = s;
	while (*tmp)
	{
		while (*tmp == c)
			tmp++;
		s = tmp;
		while (*s != '\0' && *s != c)
			s++;
		if (s > tmp || *s == c)
		{
			*ptab = ft_substr(tmp, 0, s - tmp);
			if (!*ptab)
				freeall(tab);
			tmp = s;
			ptab++;
		}
	}
	*ptab = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	size;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	size = count_substr(s, c);
	tab = malloc((size + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	extract_and_fill(tab, s, c);
	return (tab);
}

// int	main(void)
// {
// 	char *s = "un beau matin tout ça ne vaudra plus rien";
// 	char c = ' ';
// 	char **tab = ft_split(s, c);
// 	int i = 0;
// 	if (!*tab)
// 		printf("NULL\n");
// 	while (*tab)
// 	{
// 		printf("%s\n", *tab);
// 		tab++;
// 	}
// 	while(tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }
