/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/09 16:54:51 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//Memset (memory set) copies the argument 'len' amount of argument value 'c'
//to a newly created char string 's' pointed by the argument '*b'.
//Returns the argument 'b'.

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;

	s = (char *)b;
	while (len > 0)
	{
		s[len - 1] = (char )c;
		len--;
	}
	return (b);
}

/*
**	'Memalloc()' (memory allocation) allocates a section of memory the size
**	of argument 'size' with the 'string.h' function 'malloc()' and uses the
**	library function 'memset()' to set its area to '0'. 
**	The first process is a failsafe. If allocation fails, returns NULL.
*/

void	*ft_memalloc(size_t size)
{
	void	*area;

	area = malloc(size);
	if (area == NULL)
		return (NULL);
	ft_memset(area, 0, size);
	return (area);
}

//'Bzero()' (byte zero) writes an amount of 'n' zeroed bytes to the string 's'.

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

//'Ft_StrLen()' (String length) measures the length of the applied string '*s'.

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
