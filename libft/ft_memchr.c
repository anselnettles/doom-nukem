/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:32:13 by tpaaso            #+#    #+#             */
/*   Updated: 2022/04/11 13:03:58 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s2;

	s2 = (char *)s;
	while (n--)
	{
		if (*s2 == (char)c)
			return ((void *)s2);
		s2++;
	}
	return (NULL);
}
