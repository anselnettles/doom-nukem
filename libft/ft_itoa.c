/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:30:17 by tpaaso            #+#    #+#             */
/*   Updated: 2022/04/11 12:35:26 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(int nb)
{
	int		i;
	long	n;

	i = 1;
	n = nb;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (10 <= n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_absolute(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	len;

	len = (size_t)ft_count(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
		res[0] = '-';
	else if (n == 0)
		res[0] = '0';
	while (n != 0)
	{
		len--;
		res[len] = (char)ft_absolute(n % 10) + '0';
		n = n / 10;
	}
	return (res);
}
