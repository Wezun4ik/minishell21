/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:54:54 by mproveme          #+#    #+#             */
/*   Updated: 2022/10/26 15:33:40 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*fill_words(char **env)
{
	t_word	*list;
	t_word	*tmp;
	int		i;

	list = NULL;
	i = 0;
	while (env[i])
	{
		tmp = init_word(env[i]);
		add_back_word(&list, tmp);
	}
	return (list);
}

t_word	*find_min(t_word *list)
{
	t_word	*min;
	t_word	*prev;
	t_word	*curr;

	prev = list;
	curr = list->next;
	min = prev;
	while (curr)
	{
		if (ft_strncmp(curr->word, prev->word, ft_strlen(prev->word) + 1) < 0)
			min = curr;
		prev = curr;
		curr = curr->next;
	}
	return (min);
}

void	del_one_word(t_word **list, t_word *to_del)
{
	t_word	*curr;
	t_word	*prev;

	if (*list == to_del)
	{
		curr = *list;
		*list = (*list)->next;
		free_word(curr);
	}
	prev = *list;
	curr = (*list)->next;
	while (curr && curr != to_del)
	{
		prev = curr;
		curr = curr->next;
	}
	prev->next = curr->next;
	free_word(curr);
}

int	find_cnt_words(t_word *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	**sort_env(char **arr)
{
	char	**new_arr;
	t_word	*list;
	t_word	*tmp;
	int		i;

	if (!arr)
		return (NULL);
	list = fill_words(arr);
	i = find_cnt_words(list);
	new_arr = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (list)
	{
		tmp = find_min(list);
		new_arr[i++] = ft_strdup(tmp->word);
		del_one_word(&list, tmp);
	}
	new_arr[i] = NULL;
	return (new_arr);
}

// void	print_sorted_env()