/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:17:24 by tpaaso            #+#    #+#             */
/*   Updated: 2022/04/11 13:25:51 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	char	*ptr2;
	char	*result;
	size_t	i;

	i = 0;
	result = ft_memalloc((size_t)ft_strlen((char *)s) + 1);
	if (!s || !result)
		return (NULL);
	ptr = (char *)s;
	ptr2 = result;
	while (*ptr)
	{
		*(ptr2++) = f(i, *ptr++);
		i++;
	}
	return (result);
}
