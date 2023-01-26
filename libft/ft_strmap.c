/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 11:39:15 by tpaaso            #+#    #+#             */
/*   Updated: 2022/04/11 13:26:25 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ptr;
	char	*ptr2;
	char	*result;

	result = ft_memalloc((size_t)ft_strlen((char *)s) + 1);
	if (!s || !result)
		return (NULL);
	ptr = (char *)s;
	ptr2 = result;
	while (*ptr)
		*(ptr2++) = f(*ptr++);
	return (result);
}
