/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:02:53 by sbrella           #+#    #+#             */
/*   Updated: 2021/12/02 19:08:12 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;
	void	*cont;
	size_t	size;

	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->next = NULL;
	if (content == 0)
		lst->content = 0;
	else
	{
		size = ft_strlen(content) + 1;
		cont = malloc(size);
		if (!cont)
		{
			free(lst);
			return (NULL);
		}
		lst->content = ft_memcpy(cont, content, size);
	}
	return (lst);
}
