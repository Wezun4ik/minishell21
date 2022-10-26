/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:11:06 by ilya              #+#    #+#             */
/*   Updated: 2022/10/26 16:59:13 by mproveme         ###   ########.fr       */
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

int	built_in_env(char **env)
{
	int	count;

	count = 0;
	while (env[count])
	{
		printf("%s\n", env[count]);
		count++;
	}
	return (0);
}
