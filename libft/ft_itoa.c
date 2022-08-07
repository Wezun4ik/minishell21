/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:53:56 by sbrella           #+#    #+#             */
/*   Updated: 2021/11/25 19:28:47 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_countsim(int n)
{
	int	h;

	h = 0;
	if (n < 0)
		h++;
	n = (n / 10);
	while (n)
	{
		h++;
		n = (n / 10);
	}
	return (h + 2);
}

char	*ft_itoa(int n)
{
	char		*a;
	int			count;
	long int	c;

	c = (long int)n;
	count = ft_countsim(n);
	a = (char *)malloc(sizeof(char) * count);
	if (!a)
		return (0);
	if (n < 0)
	{
		a[0] = '-';
		c = -c;
	}
	a[count-- - 1] = '\0';
	while (c / 10)
	{
		a[count - 1] = ((char)(c % 10) + '0');
		c = c / 10;
		count--;
	}
	a[count - 1] = ((char)(c) + '0');
	return (a);
}
