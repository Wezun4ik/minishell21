/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:31:23 by sbrella           #+#    #+#             */
/*   Updated: 2021/11/23 19:34:46 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		a;
	char	*b;

	a = ft_strlen(s1) + 1;
	b = (char *)malloc(a);
	if (!b)
		return (0);
	b[a--] = '\0';
	while (a >= 0)
	{
		b[a] = s1[a];
		a--;
	}
	return (b);
}
