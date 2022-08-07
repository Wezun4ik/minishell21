/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:47:36 by sbrella           #+#    #+#             */
/*   Updated: 2021/12/02 19:57:41 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char ch, char const *set)
{
	size_t	len;

	len = 0;
	while (set[len])
	{
		if (set[len] == ch)
			return (1);
		len++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	begin_len;
	size_t	end_len;
	size_t	src_len;

	if (!s || !set)
		return (NULL);
	begin_len = 0;
	end_len = 0;
	src_len = ft_strlen(s);
	while (in_set(s[begin_len], set))
		begin_len++;
	if (begin_len == src_len)
		return (ft_strjoin("", ""));
	while (src_len - end_len > 0 && in_set(s[src_len - end_len - 1], set))
		end_len++;
	return (ft_substr(s, begin_len, src_len - begin_len - end_len));
}
