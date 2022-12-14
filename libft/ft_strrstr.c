/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:47:25 by sbrella           #+#    #+#             */
/*   Updated: 2021/11/23 19:08:39 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *s, int c)
{
	int			a;
	const char	*str;

	a = 0;
	str = 0;
	while (s[a])
	{
		if (s[a] == (char)c)
			str = &s[a];
		a++;
	}
	if ((char)c == '\0')
		return ((char *)&s[a]);
	return ((char *)str);
}
