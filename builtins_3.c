/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:11:06 by ilya              #+#    #+#             */
/*   Updated: 2022/10/26 03:15:02 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell minishell;

char	*my_getenv(char **env, char *key)
{
	char	*key_copy;
	char	*loc;
	int		count;

	key_copy = ft_strjoin(key, "=");
	count = 0;
	if (env == NULL || key == NULL)
		return (NULL);
	while (env[count])
	{
		loc = ft_strnstr(env[count], key_copy, ft_strlen(key_copy) + 1);
		if (loc)
		{
			free(key_copy);
			return (ft_strchr(env[count], '=') + 1);
		}
		count++;
	}
	free(key_copy);
	return (NULL);
}

int	built_in_exit(void)
{
	exit(0);
}

int	built_in_env(void)
{
	int	count;

	count = 0;
	while (minishell.env[count])
	{
		printf("%s\n", minishell.env[count]);
		count++;
	}
	return (0);
}
