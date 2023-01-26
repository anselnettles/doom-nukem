/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:02:35 by tpaaso            #+#    #+#             */
/*   Updated: 2019/10/30 11:44:12 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *ndl, size_t len)
{
	size_t	needle_len;

	if (ndl[0] == '\0')
		return ((char *)hs);
	needle_len = ft_strlen(ndl);
	while (*hs && len >= needle_len)
	{
		if (*hs == ndl[0])
		{
			if (ft_strncmp(ndl, hs, needle_len) == 0)
				return ((char *)hs);
		}
		len--;
		hs++;
	}
	return (NULL);
}
