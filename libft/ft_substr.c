/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 20:32:20 by sbrella           #+#    #+#             */
/*   Updated: 2021/12/04 17:39:45 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*ret;

	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strjoin("", ""));
	if (start + len > str_len)
		len -= start + len - str_len;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	ft_memcpy(ret, &s[start], len);
	return (ret);
}
