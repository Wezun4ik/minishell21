/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:53:17 by sbrella           #+#    #+#             */
/*   Updated: 2022/10/21 03:47:03 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		a;
	size_t		n;
	char		*str;

	a = 0;
	n = 0;
	if (!(s1) || !(s2))
		return (0);
	a = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (a + 1));
	if (!str)
		return (0);
	a = 0;
	while (s1[a])
		str[n++] = s1[a++];
	a = 0;
	while (s2[a])
		str[n++] = s2[a++];
	str[n] = '\0';
	return (str);
}
