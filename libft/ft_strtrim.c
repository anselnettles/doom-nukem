/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:52:10 by tpaaso            #+#    #+#             */
/*   Updated: 2022/04/11 13:18:17 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ws_start(const char *s)
{
	size_t	res;

	res = 0;
	while ((*s == ' ' || *s == '\n' || *s == '\t') && *s)
	{
		res++;
		s++;
	}
	if (*s == '\0')
		return (-1);
	return (res);
}

size_t	ft_ws_end(const char *s)
{
	size_t	ans;

	ans = 0;
	while (*s)
		s++;
	s--;
	while ((*s == ' ' || *s == '\n' || *s == '\t') && *s)
	{
		ans++;
		s--;
	}
	return (ans);
}

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	if (!s)
		return (NULL);
	start = ft_ws_start(s);
	if (start < 0)
		return (NULL);
	end = ft_ws_end(s);
	str = ft_memalloc(ft_strlen(s) - start - end + 1);
	if (!str)
		return (NULL);
	while (s[i + start + end] != '\0')
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
