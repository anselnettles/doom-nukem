/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:02:35 by tpaaso            #+#    #+#             */
/*   Updated: 2022/04/11 13:19:17 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hs, const char *ndl)
{
	int	len;
	int	count;

	len = 0;
	count = 0;
	if (ndl[0] == '\0')
		return ((char *)hs);
	while (hs[len] != '\0')
	{
		if (ndl[count] == '\0')
			return ((char *)hs + len);
		if (hs[len + count] == ndl[count])
			count++;
		else
		{
			count = 0;
			len++;
		}
	}
	return (NULL);
}
