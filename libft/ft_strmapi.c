/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:51:02 by sbrella           #+#    #+#             */
/*   Updated: 2021/11/25 19:43:49 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*a;
	unsigned int	c;
	unsigned int	c1;

	c1 = 0;
	c = (ft_strlen(s) + 1);
	a = (char *)malloc(sizeof(char) * c);
	if (!a)
		return (0);
	a[c - 1] = '\0';
	c--;
	while (c1 < c)
	{
		a[c1] = (*f)(c1, s[c1]);
		c1++;
	}
	return (a);
}
