/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 21:29:10 by sbrella           #+#    #+#             */
/*   Updated: 2021/12/04 17:08:37 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char delim)
{
	size_t	n;
	size_t	a;

	n = 0;
	a = 0;
	while (s[a])
	{
		if (s[a] != delim)
		{
			n++;
			while (s[a] != delim && s[a])
				a++;
		}
		while (s[a] == delim && s[a])
			a++;
	}
	return (n);
}

static size_t	ft_strcopy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && (size > 1))
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	if (size >= 1)
		dst[i] = '\0';
	return (i);
}

static size_t	getwlen(const char *s, char c)
{
	size_t	a;

	a = 0;
	while (*s != c && *s)
	{
		s++;
		a++;
	}
	return (a);
}

static void	*ft_free_masmas(size_t a, char **mas)
{
	while (a)
		free(mas[a--]);
	free(mas[0]);
	free(mas);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	size_t	a;
	char	**mas;

	a = 0;
	if (!(s))
		return (0);
	count = ft_count_words(s, c);
	mas = (char **)malloc(sizeof(char *) * (count + 1));
	if (!mas)
		return (0);
	while (a < count)
	{
		while (*s == c)
			s++;
		mas[a] = (char *)malloc(getwlen(s, c) + 1);
		if (!mas[a])
			return (ft_free_masmas(a, mas));
		ft_strcopy(mas[a++], s, (getwlen(s, c) + 1));
		s += getwlen(s, c);
	}
	mas[a] = 0;
	return (mas);
}
