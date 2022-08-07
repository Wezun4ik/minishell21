/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:28:46 by sbrella           #+#    #+#             */
/*   Updated: 2021/11/30 16:15:50 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (!dstsize)
		return (len_src);
	if (len_src < dstsize)
		dstsize = len_src;
	else
		dstsize -= 1;
	ft_memcpy(dst, src, dstsize);
	dst[dstsize] = '\0';
	return (len_src);
}
