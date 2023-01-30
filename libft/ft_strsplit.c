/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:46:43 by tpaaso            #+#    #+#             */
/*   Updated: 2022/04/11 13:23:08 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while ((s[i] != c) && (s[i] != '\0'))
		{
			if ((s[i + 1] == c || s[i + 1] == '\0'))
				count++;
			i++;
		}
	}
	return (count);
}

static size_t	ft_wordsize(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static void	ft_free_error(char **res, size_t nbr)
{
	while (nbr >= 0)
	{
		if (res[nbr] != NULL)
			free(res[nbr]);
		nbr--;
	}
	free(res);
}

char	**ft_strsplit(const char *s, char c)
{
	char		**mem;
	size_t		n;
	size_t		i;
	size_t		j;

	if (s == NULL)
		return (NULL);
	n = ft_wordcount(s, c);
	i = 0;
	j = 0;
	mem = (char **)malloc(sizeof(char *) * n + 1);
	if (mem == NULL)
		return (NULL);
	while (i < n)
	{
		while (s[j] == c)
			j++;
		mem[i] = ft_strsub(&s[j], 0, ft_wordsize(&s[j], c));
		if (mem[i] == NULL)
			ft_free_error(mem, i);
		j = j + ft_wordsize(&s[j], c);
		i++;
	}
	mem[i] = NULL;
	return (mem);
}
