/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:51:48 by sbrella           #+#    #+#             */
/*   Updated: 2021/11/24 19:17:53 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nxt;
	t_list	*save;

	if (!(lst) || !(*lst) || !(del))
		return ;
	nxt = *lst;
	while (nxt)
	{
		del(nxt->content);
		save = nxt->next;
		free(nxt);
		nxt = save;
	}
	*lst = NULL;
}
