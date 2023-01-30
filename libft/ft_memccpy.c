/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:30:01 by tpaaso            #+#    #+#             */
/*   Updated: 2019/10/29 16:34:37 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	*a;
	size_t			i;

	i = 0;
	s = (unsigned char *)dst;
	a = (unsigned char *)src;
	while (i < n)
	{
		s[i] = a[i];
		if (s[i] == (unsigned char)c)
			return ((void *)(s + i + 1));
		i++;
	}
	return (NULL);
}
